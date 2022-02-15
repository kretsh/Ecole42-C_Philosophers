/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:35:53 by cowen             #+#    #+#             */
/*   Updated: 2021/12/06 13:00:18 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	status_output(int tid, int philid)
{
	pthread_mutex_lock(&g_struct.print);
	if (tid == FORK)
		printf("%ld %d has taken a fork\n", get_act_time(), philid);
	if (tid == EATING)
		printf("%ld %d is eating\n", get_act_time(), philid);
	if (tid == SLEEPING)
		printf("%ld %d is sleeping\n", get_act_time(), philid);
	if (tid == THINKING)
		printf("%ld %d is thinking\n", get_act_time(), philid);
	pthread_mutex_unlock(&g_struct.print);
}

void	my_usleep(int value)
{
	value += get_act_time();
	usleep(value - 100);
	while (get_act_time() < (long) value)
		usleep(100);
}

void	deattach_threads(int id)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&g_struct.print);
	while (++i < g_struct.n_philos)
		pthread_detach(g_struct.p_threads[i]);
	i = -1;
	if (id == PHILO_DIED)
		printf("%ld %d died\n", get_act_time_main(), g_struct.died_id);
	if (id == END)
		printf("All %d iterations has ended", g_struct.eat_iters);
	while (++i < g_struct.n_philos)
		pthread_mutex_destroy(&g_struct.philos[i].fork);
	free(g_struct.philos);
	free(g_struct.p_threads);
	free(g_struct.done_operations);
}
