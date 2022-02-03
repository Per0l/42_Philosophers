/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:54:11 by aperol-h          #+#    #+#             */
/*   Updated: 2022/02/03 14:11:25 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_utils.h"

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	get_timestamp(void)
{
	static long		timebase;

	if (timebase == 0)
		timebase = get_time_ms();
	return (get_time_ms() - timebase);
}

void	msleep(int ms)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(50);
}
