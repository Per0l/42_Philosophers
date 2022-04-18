/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:20:59 by aperol-h          #+#    #+#             */
/*   Updated: 2022/02/01 17:39:35 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include "structs.h"

enum e_philo_state
{
	TAKING,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};
void	print_state(t_philo *philo, int state);
#endif