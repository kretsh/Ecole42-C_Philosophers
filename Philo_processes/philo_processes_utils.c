/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:32:31 by cowen             #+#    #+#             */
/*   Updated: 2021/12/12 13:00:18 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_processes.h"

void	status_output(int tid, int philid)
{
	sem_wait(g_struct.printf);
	if (tid == FORK)
		printf("%ld %d has taken a fork\n", get_act_time(), philid);
	if (tid == EATING)
	{
		g_struct.when_ate_last_time = g_struct.when_ate;
		g_struct.when_ate = get_act_time();
		printf("%ld %d is eating\n", g_struct.when_ate, philid);
	}
	if (tid == SLEEPING)
		printf("%ld %d is sleeping\n", get_act_time(), philid);
	if (tid == THINKING)
		printf("%ld %d is thinking\n", get_act_time(), philid);
	sem_post(g_struct.printf);
}

void	my_usleep(int value)
{
	value += get_act_time();
	usleep(value - 100);
	while (get_act_time() < (long) value)
		usleep(450);
}

long	get_act_time(void)
{
	long	value;
	long	temp;

	gettimeofday(&g_struct.time_act, NULL);
	value = g_struct.time_act.tv_sec - g_struct.time_s.tv_sec;
	temp = g_struct.time_act.tv_usec - g_struct.time_s.tv_usec;
	if (temp < 0)
	{
		value--;
		temp = temp + 1000000;
	}
	value = value * 1000 + temp / 1000;
	return (value);
}

long	get_act_time_main(void)
{
	long	value;
	long	temp;

	gettimeofday(&g_struct.time_main, NULL);
	value = g_struct.time_main.tv_sec - g_struct.time_s.tv_sec;
	temp = g_struct.time_main.tv_usec - g_struct.time_s.tv_usec;
	if (temp < 0)
	{
		value--;
		temp = temp + 1000000;
	}
	value = value * 1000 + temp / 1000;
	return (value);
}

void	semunorlinked(int k)
{	
	if (k == DELETE)
	{
		sem_close(g_struct.fork);
		sem_close(g_struct.printf);
		sem_unlink("/philo_fork");
		sem_unlink("/philo_printf");
	}
	else if (k == OPEN)
	{
		sem_unlink("/philo_fork");
		sem_unlink("/philo_printf");
		g_struct.fork = sem_open("/philo_fork", O_CREAT, S_IRWXU,
				g_struct.n_philos);
		g_struct.printf = sem_open("/philo_printf", O_CREAT, S_IRWXU, 1);
	}
}
