/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:57:36 by aperol-h          #+#    #+#             */
/*   Updated: 2022/02/03 16:35:12 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <pthread.h>

typedef struct s_philo
{
	pthread_t			thread;
	struct s_program	*program;
	int					id;
	int					is_alive;
	long				timestamp_ate;
	int					times_eaten;
}	t_philo;

typedef struct s_program
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_to_eat;
	int				finished;
	int				n_philos_ate;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eaten_m;
}	t_program;

#endif