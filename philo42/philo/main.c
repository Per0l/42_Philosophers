/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:21:32 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 18:27:54 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_memory(t_program *program, t_philo **philos)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&program->print);
	pthread_mutex_destroy(&program->end);
	while (++i < program->n_philos)
	{
		pthread_mutex_destroy(&philos[i]->fork);
		free(philos[i]);
	}
	free(philos);
}

static void	create_threads(t_philo **philos, t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->n_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			exit(1);
		philos[i]->id = i + 1;
		philos[i]->program = program;
		philos[i]->timestamp_ate = program->timebase;
		philos[i]->times_eaten = 0;
		pthread_mutex_init(&philos[i]->fork, NULL);
	}
	i = -1;
	while (++i < program->n_philos - 1)
		philos[i]->next = philos[i + 1];
	philos[i]->next = philos[0];
}

int	init_philos(t_program *program)
{
	int		i;
	t_philo	**philos;

	program->timebase = get_time_ms();
	philos = malloc(sizeof(t_philo *) * program->n_philos);
	if (!philos)
		exit(1);
	create_threads(philos, program);
	i = -1;
	while (++i < program->n_philos)
		pthread_create(&philos[i]->thread, NULL, philo_thread, philos[i]);
	check_death(program, philos);
	i = -1;
	while (++i < program->n_philos)
		pthread_join(philos[i]->thread, NULL);
	clean_memory(program, philos);
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
		program.finished = 0;
		pthread_mutex_init(&program.print, NULL);
		pthread_mutex_init(&program.end, NULL);
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
