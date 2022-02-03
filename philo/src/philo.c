/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:44:21 by aperol-h          #+#    #+#             */
/*   Updated: 2022/02/03 16:35:01 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_simulation(t_program *program)
{
	int	i;

	i = -1;
	program->finished = 1;
	while (i++ < program->n_philos - 1)
	{
		program->philos[i].is_alive = 0;
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->program->forks[philo->id - 1]));
	pthread_mutex_unlock(&(philo->program->forks[philo->id
			% philo->program->n_philos]));
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	fork2 = &(philo->program->forks[philo->id
			% philo->program->n_philos]);
	fork1 = &(philo->program->forks[philo->id - 1]);
	if (philo->id % 2)
		pthread_mutex_lock(fork1);
	else
		pthread_mutex_lock(fork2);
	print_state(philo, TAKING);
	if (philo->id % 2)
		pthread_mutex_lock(fork2);
	else
		pthread_mutex_lock(fork1);
	print_state(philo, TAKING);
}

void	*check_death(void *self)
{
	t_philo			*philo;
	long			time_now;

	philo = self;
	while (!philo->program->finished)
	{
		if (philo->times_eaten == philo->program->n_times_to_eat)
		{
			philo->times_eaten++;
			pthread_mutex_lock(&(philo->program->eaten_m));
			philo->program->n_philos_ate++;
			pthread_mutex_unlock(&(philo->program->eaten_m));
		}
		if (philo->program->n_philos_ate == philo->program->n_philos)
			stop_simulation(philo->program);
		time_now = get_timestamp();
		if ((time_now - philo->timestamp_ate) >= philo->program->time_to_die)
		{
			philo->is_alive = 0;
			print_state(philo, DIED);
			unlock_forks(philo);
			stop_simulation(philo->program);
		}
		usleep(1000);
	}
}

void	*philo_thread(void *self)
{
	t_philo			*philo;
	pthread_t		cth;

	philo = self;
	if (pthread_create(&cth, NULL, check_death, philo))
		return (0);
	pthread_detach(cth);
	while (philo->is_alive)
	{
		lock_forks(philo);
		if (philo->program->finished)
			break ;
		print_state(philo, EATING);
		msleep(philo->program->time_to_eat);
		unlock_forks(philo);
		if (philo->program->finished)
			break ;
		print_state(philo, SLEEPING);
		msleep(philo->program->time_to_sleep);
		print_state(philo, THINKING);
		usleep(500);
	}
	return (NULL);
}
