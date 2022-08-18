/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:54:11 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 19:58:02 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time_utils.h"
#include "structs.h"

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	get_timestamp(long timebase)
{
	return (get_time_ms() - timebase);
}

void	msleep(long ms)
{
	long	start;

	start = get_time_ms();
	while (1)
	{
		if (get_time_ms() - start >= ms)
			break ;
		usleep(10);
	}
}
