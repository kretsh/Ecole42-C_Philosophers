/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:34:50 by cowen             #+#    #+#             */
/*   Updated: 2021/12/06 14:49:03 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen_is_digit(const char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	else
	{
		if (str[i] == '+')
			i++;
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long int	sum;
	int				sign;

	sum = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + *str - '0';
		str++;
	}
	if (sum * sign > 2147483647 || sum * sign < -2147483648)
		return (-1);
	return (sum * sign);
}

int	parse_arguments(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (fill_arg(argv[1], 1) == -1)
			return (-1);
		if (fill_arg(argv[2], 2) == -1)
			return (-1);
		if (fill_arg(argv[3], 3) == -1)
			return (-1);
		if (fill_arg(argv[4], 4) == -1)
			return (-1);
		if (argc == 6)
		{
			if (fill_arg(argv[5], 5) == -1)
				return (-1);
		}
		else
		{
			g_struct.eat_iters = -1;
			g_struct.summ_iters = -1;
		}
	}
	else
		return (-1);
	return (0);
}

int	fill_arg(char *str, int arg)
{
	int	temp;

	if (ft_strlen_is_digit(str))
	{	
		temp = ft_atoi(str);
		if (temp != -1)
		{
			if (arg == 1)
				g_struct.n_philos = temp;
			if (arg == 2)
				g_struct.time_to_die = temp;
			if (arg == 3)
				g_struct.time_to_eat = temp;
			if (arg == 4)
				g_struct.time_to_sleep = temp;
			if (arg == 5)
			{
				g_struct.eat_iters = temp;
				g_struct.summ_iters = 0;
			}
			return (1);
		}
	}
	return (-1);
}
