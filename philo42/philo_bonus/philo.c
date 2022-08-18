/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:44:21 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 20:25:58 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	*check_death(void *self)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *) self;
	i = -1;
	while (1)
	{
		if ((get_time_ms() - philo->timestamp_ate)
			> philo->program->time_to_die)
		{
			print_state(philo, DIED);
			sem_post(philo->program->finish_sem);
			i = philo->program->n_philos;
			while (--i >= 0)
				sem_post(philo->program->eaten_sem);
			return (NULL);
		}
		if (philo->program->n_times_to_eat > 0
			&& philo->times_eaten == philo->program->n_times_to_eat)
		{
			philo->times_eaten++;
			sem_post(philo->program->eaten_sem);
		}
		usleep(100);
	}
}

void	check_finished(t_program *program)
{
	int			i;

	i = program->n_philos;
	if (program->n_times_to_eat > 0)
	{
		while (--i >= 0)
			sem_wait(program->eaten_sem);
		sem_post(program->finish_sem);
	}
	sem_wait(program->finish_sem);
	i = -1;
	while (++i < program->n_philos)
		if (program->pids[i] > 0)
			kill(program->pids[i], SIGKILL);
}

void	lock_forks(t_philo *philo)
{
	sem_wait(philo->program->forks_sem);
	print_state(philo, TAKING);
	if (philo->program->n_philos == 1)
	{
		print_state(philo, DIED);
		sem_post(philo->program->eaten_sem);
		sem_post(philo->program->finish_sem);
		exit(0);
	}
	sem_wait(philo->program->forks_sem);
	print_state(philo, TAKING);
}

void	*philo_process(t_program *program, int id)
{
	t_philo			*philo;
	pthread_t		cth;

	philo = &program->philos[id];
	if (pthread_create(&cth, NULL, &check_death, philo))
		return (0);
	pthread_detach(cth);
	while (1)
	{
		lock_forks(philo);
		print_state(philo, EATING);
		msleep(philo->program->time_to_eat);
		philo->times_eaten++;
		philo->timestamp_ate = get_time_ms();
		sem_post(program->forks_sem);
		sem_post(program->forks_sem);
		print_state(philo, SLEEPING);
		msleep(philo->program->time_to_sleep);
		print_state(philo, THINKING);
	}
	return (0);
}
