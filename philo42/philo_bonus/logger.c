/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:20:27 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/18 20:52:07 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "time_utils.h"

size_t	ft_putchar(char c, int fake)
{
	if (fake >= 0)
		return (1);
	return (write(1, &c, 1));
}

size_t	ft_putlong(long long nbr, int *fake, char *str)
{
	size_t	size;

	size = 0;
	if (nbr >= 10)
	{
		size += ft_putlong(nbr / 10, fake, str);
		size += ft_putlong(nbr % 10, fake, str);
	}
	else
	{
		size += ft_putchar(nbr + '0', *fake);
		if (str)
		{
			str[*fake] = nbr + '0';
			*fake = *fake + 1;
		}
	}
	return (size);
}

size_t	ft_putstr(const char *str, int *fake, char *dest)
{
	int		i;
	size_t	size;

	size = 0;
	i = -1;
	while (str && str[++i])
	{
		size += ft_putchar(str[i], *fake);
		if (dest)
		{
			dest[*fake] = str[i];
			*fake = *fake + 1;
		}
	}
	return (size);
}

void	ft_printphilo(long long time, int id, char *state)
{
	size_t	size;
	char	*out;
	int		tmp;

	tmp = 0;
	size = 3 + ft_putlong(time, &tmp, NULL)
		+ ft_putlong(id, &tmp, NULL) + ft_putstr(state, &tmp, NULL);
	out = malloc(size * sizeof(char));
	if (!out)
		exit(1);
	ft_putlong(time, &tmp, out);
	out[tmp++] = ' ';
	ft_putlong(id, &tmp, out);
	out[tmp++] = ' ';
	ft_putstr(state, &tmp, out);
	out[tmp++] = ' ';
	write(1, out, size);
	free(out);
}

void	print_state(t_philo *philo, int state)
{
	static char	*state_strings[] = {
		"has taken a fork\n", "is eating\n",
		"is sleeping\n", "is thinking\n", "died\n"
	};

	sem_wait(philo->program->print_sem);
	ft_printphilo(get_time_ms() - philo->program->timebase,
		philo->id, state_strings[state]);
	if (state == DIED)
		return ;
	sem_post(philo->program->print_sem);
}
