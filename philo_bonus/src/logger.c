/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:20:27 by aperol-h          #+#    #+#             */
/*   Updated: 2022/04/18 21:15:06 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "logger.h"
#include "time_utils.h"

void	print_state(t_philo *philo, int state)
{
	static const char	*state_strings[] = {
		"has taken a fork", "is eating", "is sleeping", "is thinking", "died"
	};

	if (state == EATING)
	{
		philo->timestamp_ate = get_timestamp();
		if (philo->program->n_times_to_eat > 0
			&& philo->times_eaten < philo->program->n_times_to_eat)
			philo->times_eaten++;
	}
	sem_wait(philo->program->print_sem);
	printf("%li %i %s\n", get_timestamp(), philo->id, state_strings[state]);
	sem_post(philo->program->print_sem);
}
