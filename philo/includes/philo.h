/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:44:56 by aperol-h          #+#    #+#             */
/*   Updated: 2022/02/03 13:40:28 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "time_utils.h"
# include "logger.h"

void	*philo_thread(void *self);
void	stop_simulation(t_program *program);
void	unlock_forks(t_philo *philo);
#endif