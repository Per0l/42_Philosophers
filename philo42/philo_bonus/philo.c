/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:44:21 by aperol-h          #+#    #+#             */
/*   Updated: 2022/04/18 21:35:12 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	*check_eaten(void *p)
{
	t_program	*program;
	int			i;

	program = p;
	if (program->n_times_to_eat > 0)
	{
		i = program->n_philos;
		while (i--)
			sem_wait(program->eaten_sem);
		sem_post(program->finish_sem);
	}
	return (NULL);
}

void	check_finished(t_program *program)
{
	int			i;
	pthread_t	check_eaten_thread;

	if (pthread_create(&check_eaten_thread, 0, check_eaten, program))
		exit(1);
	sem_wait(program->finish_sem);
	i = -1;
	while (i++ < program->n_philos - 1)
		if (program->pids[i] > 0)
			kill(program->pids[i], SIGKILL);
	pthread_join(check_eaten_thread, 0);
}

void	*check_death(void *self)
{
	t_philo			*philo;

	philo = self;
	while (1)
	{
		if (philo->times_eaten == philo->program->n_times_to_eat)
		{
			philo->times_eaten++;
			sem_post(philo->program->eaten_sem);
		}
		if ((get_timestamp() - philo->timestamp_ate)
			>= philo->program->time_to_die)
		{
			print_state(philo, DIED);
			sem_post(philo->program->finish_sem);
			return (NULL);
		}
		usleep(1000);
	}
}

void	lock_forks(t_philo *philo)
{
	sem_wait(philo->program->forks_sem);
	print_state(philo, TAKING);
	if (philo->program->n_philos == 1)
	{
		msleep(philo->program->time_to_die + 20);
		return ;
	}
	sem_wait(philo->program->forks_sem);
	print_state(philo, TAKING);
}

void	*philo_process(t_program *program, int id)
{
	t_philo			*philo;
	pthread_t		cth;

	philo = &program->philos[id];
	if (pthread_create(&cth, NULL, check_death, philo))
		return (0);
	pthread_detach(cth);
	while (1)
	{
		lock_forks(philo);
		print_state(philo, EATING);
		msleep(philo->program->time_to_eat);
		sem_post(program->forks_sem);
		sem_post(program->forks_sem);
		print_state(philo, SLEEPING);
		msleep(philo->program->time_to_sleep);
		print_state(philo, THINKING);
		usleep(500);
	}
	return (0);
}
