/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:20:27 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 19:55:11 by aperol-h         ###   ########.fr       */
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

	sem_wait(philo->program->print_sem);
	printf("%li %i %s\n", get_time_ms() - philo->program->timebase,
		philo->id, state_strings[state]);
	if (state == DIED)
		return ;
	sem_post(philo->program->print_sem);
}
