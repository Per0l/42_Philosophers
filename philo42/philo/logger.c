/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:20:27 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 18:23:29 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->program->print);
	if (philo->program->finished == 0)
		printf("%li %i %s\n", get_time_ms() - philo->program->timebase,
			philo->id, state);
	pthread_mutex_unlock(&philo->program->print);
}
