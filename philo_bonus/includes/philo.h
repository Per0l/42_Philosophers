/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:44:56 by aperol-h          #+#    #+#             */
/*   Updated: 2022/04/18 21:24:16 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "time_utils.h"
# include "logger.h"
# include <signal.h>

void	*philo_process(t_program *program, int id);
void	stop_simulation(t_program *program);
void	check_finished(t_program *program);
#endif