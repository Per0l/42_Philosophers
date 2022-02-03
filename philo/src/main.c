/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:21:32 by aperol-h          #+#    #+#             */
/*   Updated: 2022/02/03 16:35:00 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "parser.h"
#include "logger.h"
#include "time_utils.h"
#include "philo.h"

void	clean_memory(t_program *program)
{
	int	i;

	pthread_mutex_destroy(&(program->eaten_m));
	i = -1;
	while (i++ < program->n_philos - 1)
		pthread_mutex_destroy(&(program->forks[i]));
	free(program->forks);
	free(program->philos);
}

int	create_threads(t_program *program)
{
	int	i;

	pthread_mutex_init(&(program->eaten_m), NULL);
	i = -1;
	while (i++ < program->n_philos - 1)
	{
		program->philos[i].id = i + 1;
		program->philos[i].program = program;
		program->philos[i].is_alive = 1;
		program->philos[i].timestamp_ate = 0;
		program->philos[i].times_eaten = 0;
		pthread_mutex_init(&(program->forks[i]), NULL);
		if (pthread_create(&program->philos[i].thread, NULL,
				philo_thread, &program->philos[i]))
			return (0);
	}
	return (1);
}

int	init_philos(t_program *program)
{
	int	i;

	program->philos = (t_philo *)malloc(program->n_philos * sizeof(t_philo));
	if (!program->philos)
		return (0);
	program->forks = malloc(program->n_philos * sizeof(pthread_mutex_t));
	if (!program->forks)
		return (0);
	if (!create_threads(program))
		return (0);
	i = -1;
	while (i++ < program->n_philos - 1)
		pthread_join(program->philos[i].thread, NULL);
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
		program.n_philos_ate = 0;
		program.finished = 0;
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
