/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:27:39 by cowen             #+#    #+#             */
/*   Updated: 2021/12/06 18:25:11 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_processes.h"

int	main(int argc, char **argv)
{
	if (parse_arguments(argc, argv) != -1)
		init_func();
	else
	{
		write(2, "Incorrect arguments\n", 20);
		return (-1);
	}
	return (0);
}
