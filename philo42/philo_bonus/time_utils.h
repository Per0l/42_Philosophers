/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:54:26 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 19:15:16 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_UTILS_H
# define TIME_UTILS_H

# include <sys/time.h>
# include <unistd.h>

void	msleep(long ms);
long	get_timestamp(long timebase);
long	get_time_ms(void);
#endif