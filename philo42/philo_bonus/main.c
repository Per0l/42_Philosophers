/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:21:32 by aperol-h          #+#    #+#             */
/*   Updated: 2022/04/18 21:53:27 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "time_utils.h"
#include "structs.h"
#include "philo.h"
#include "parser.h"

void	clean_memory(t_program *program)
{
	sem_close(program->eaten_sem);
	sem_close(program->forks_sem);
	sem_close(program->finish_sem);
	sem_close(program->print_sem);
	free(program->philos);
	free(program->pids);
}

int	init_sems(t_program *program)
{
	sem_unlink(EATEN_N);
	program->eaten_sem = sem_open(EATEN_N, O_CREAT | O_EXCL, 0644, 0);
	if (program->eaten_sem == SEM_FAILED)
		exit(-1);
	sem_unlink(FORKS_N);
	program->forks_sem = sem_open(FORKS_N, O_CREAT | O_EXCL, 0644,
			program->n_philos);
	if (program->forks_sem == SEM_FAILED)
		exit(-1);
	sem_unlink(FINISH_N);
	program->finish_sem = sem_open(FINISH_N, O_CREAT | O_EXCL, 0644,
			0);
	if (program->finish_sem == SEM_FAILED)
		exit(-1);
	sem_unlink(PRINT_N);
	program->print_sem = sem_open(PRINT_N, O_CREAT | O_EXCL, 0644,
			1);
	if (program->print_sem == SEM_FAILED)
		exit(-1);
	return (0);
}

int	create_processes(t_program *program)
{
	int	i;

	i = -1;
	init_sems(program);
	while (i++ < program->n_philos - 1)
	{
		program->philos[i].id = i + 1;
		program->philos[i].program = program;
		program->philos[i].timestamp_ate = 0;
		program->philos[i].times_eaten = 0;
		if (program->pids[i] != 0)
			program->pids[i] = fork();
		if (program->pids[i] == 0)
		{
			philo_process(program, i);
			clean_memory(program);
			return (0);
		}
	}
	return (1);
}

int	init_philos(t_program *program)
{
	int	i;

	program->philos = (t_philo *)malloc(program->n_philos * sizeof(t_philo));
	if (!program->philos)
		return (0);
	program->pids = (pid_t *)malloc((program->n_philos) * sizeof(pid_t));
	if (!program->pids)
		return (0);
	i = -1;
	while (i++ < program->n_philos - 1)
		program->pids[i] = -1;
	if (!create_processes(program))
		return (0);
	check_finished(program);
	while (waitpid(-1, NULL, 0))
	{
		if (errno == ECHILD)
			break ;
	}
	clean_memory(program);
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc == 5 || argc == 6)
	{
		program.n_philos = ft_parseint(argv[1]);
		program.time_to_die = ft_parseint(argv[2]);
		program.time_to_eat = ft_parseint(argv[3]);
		program.time_to_sleep = ft_parseint(argv[4]);
		program.n_times_to_eat = -2;
		if (argc == 6)
			program.n_times_to_eat = ft_parseint(argv[5]);
		if (!valid_args(program) || !init_philos(&program))
			return (1);
	}
	else
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
	return (0);
}
