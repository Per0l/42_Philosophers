/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:45:22 by aperol-h          #+#    #+#             */
/*   Updated: 2022/02/02 19:15:21 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parser.h"
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_parseint(char *str)
{
	int	res;
	int	size;
	int	i;

	size = ft_strlen(str);
	res = 0;
	i = -1;
	while (i++ < size - 1)
	{
		if (ft_isspace(str[i]))
			continue ;
		if (!ft_isdigit(str[i]))
			return (-1);
		res *= 10;
		res += str[i] - '0';
	}
	return (res);
}

int	valid_args(t_program program)
{
	long long	check;

	check = program.n_philos * program.time_to_die
		* program.time_to_eat * program.time_to_sleep;
	if (check < 0 || program.n_times_to_eat == -1)
	{
		printf("Error: Parameters should be valid positive integers.\n");
		return (0);
	}
	return (1);
}
