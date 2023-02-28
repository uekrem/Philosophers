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

int ft_arg_letter(char **str, int argc)
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
	}
	return (0);
}

int ft_arg_sign(char **str, int argc)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		if (str[i][0] == '-')
			return (1);
	}
	return (0);
}

int ft_int_rang(char **str, int argc)
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