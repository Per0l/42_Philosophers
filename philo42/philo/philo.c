/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:44:21 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 18:23:36 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	msleep(t_philo *philo, long ms)
{
	long	start;

	start = get_time_ms();
	while (philo->program->finished == 0)
	{
		if (get_time_ms() - start >= ms)
			break ;
		usleep(10);
	}
}

void	end_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->end);
	philo->program->finished = 1;
	pthread_mutex_unlock(&philo->program->end);
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_state(philo, "has taken a fork");
	if (philo->program->n_philos == 1)
	{
		print_state(philo, "died");
		philo->program->finished = 1;
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	pthread_mutex_lock(&philo->next->fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	msleep(philo, philo->program->time_to_eat);
	philo->times_eaten++;
	philo->timestamp_ate = get_time_ms();
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	check_death(t_program *program, t_philo **philos)
{
	int	i;
	int	n_philos_ate;

	n_philos_ate = 0;
	i = -1;
	while (++i < program->n_philos && program->finished == 0)
	{
		if ((get_time_ms() - philos[i]->timestamp_ate) > program->time_to_die)
		{
			print_state(philos[i], "died");
			philos[i]->program->finished = 1;
			break ;
		}
		if (philos[i]->times_eaten == program->n_times_to_eat)
			if (n_philos_ate++ > program->n_philos)
				break ;
		if (i == program->n_philos - 1)
			i = -1;
	}
	program->finished = 2;
}

void	*philo_thread(void *self)
{
	t_philo			*philo;

	philo = (t_philo *)self;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->program->finished)
			return (NULL);
		lock_forks(philo);
		if (philo->program->finished)
			return (NULL);
		print_state(philo, "is sleeping");
		msleep(philo, philo->program->time_to_sleep);
		if (philo->program->finished)
			return (NULL);
		print_state(philo, "is thinking");
	}
	return (NULL);
}
