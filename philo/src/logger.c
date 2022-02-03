/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:20:27 by aperol-h          #+#    #+#             */
/*   Updated: 2022/02/03 16:35:00 by aperol-h         ###   ########.fr       */
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

	if (philo->program->finished)
		return ;
	if (state != DIED && !philo->is_alive)
		return ;
	if (state == EATING)
	{
		philo->timestamp_ate = get_timestamp();
		if (philo->program->n_times_to_eat > 0
			&& philo->times_eaten < philo->program->n_times_to_eat)
			philo->times_eaten++;
	}
	if (state == DIED)
		philo->program->finished = 1;
	printf("%li %i %s\n", get_timestamp(), philo->id, state_strings[state]);
}
