/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:57:36 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 19:30:35 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <semaphore.h>
# include <pthread.h>

# define FORKS_N "/forks"
# define EATEN_N "/eaten"
# define FINISH_N "/finish"
# define PRINT_N "/print"

typedef struct s_philo
{
	struct s_program	*program;
	int					id;
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
	long			timebase;
	t_philo			*philos;
	pid_t			*pids;
	sem_t			*forks_sem;
	sem_t			*eaten_sem;
	sem_t			*finish_sem;
	sem_t			*print_sem;
}	t_program;

#endif