/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:44:56 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 18:25:41 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	long				timestamp_ate;
	int					times_eaten;
	pthread_t			thread;
	pthread_mutex_t		fork;
	struct s_philo		*next;
	struct s_program	*program;
}	t_philo;

typedef struct s_program
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_to_eat;
	int				finished;
	long			timebase;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
}	t_program;

long	get_timestamp(long timebase);
long	get_time_ms(void);
int		ft_parseint(char *str);
int		valid_args(t_program program);
void	*philo_thread(void *self);
void	check_death(t_program *program, t_philo **philos);
void	print_state(t_philo *philo, char *state);
void	end_sim(t_philo *philo);
#endif