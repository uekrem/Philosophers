/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekrem <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:20:49 by hekrem            #+#    #+#             */
/*   Updated: 2023/03/03 13:20:50 by hekrem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int		i;
	long	res;
	long	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_arg_letter(char **str, int argc)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (str[i][++j])
			if (!(str[i][j] >= '0' && str[i][j] <= '9'))
				return (1);
		if (!str[i][0])
			return (1);
	}
	return (0);
}

int	ft_int_rang(char **str, int argc)
{
	int		i;
	long	temp;

	i = 0;
	while (++i < argc)
	{
		temp = ft_atoi(str[i]);
		if (temp > 2147483647 || temp < -2147483648)
			return (1);
	}
	return (0);
}
