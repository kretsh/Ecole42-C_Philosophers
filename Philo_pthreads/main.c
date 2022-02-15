/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:35:50 by cowen             #+#    #+#             */
/*   Updated: 2021/12/06 18:24:32 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (parse_arguments(argc, argv) != -1)
	{
		init_func();
		pthread_mutex_destroy(&g_struct.print);
	}
	else
	{
		write(2, "Incorrect arguments\n", 20);
		return (-1);
	}
	return (0);
}
