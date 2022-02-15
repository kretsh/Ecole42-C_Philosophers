/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:36:15 by cowen             #+#    #+#             */
/*   Updated: 2021/12/06 15:20:50 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_func(void)
{	
	int	s;
	int	i;

	i = -1;
	g_struct.philos = malloc(sizeof(t_philo) * g_struct.n_philos);
	if (g_struct.philos == NULL)
		return (MALLOC_ERROR);
	g_struct.p_threads = malloc(sizeof(pthread_t) * g_struct.n_philos);
	if (g_struct.p_threads == NULL)
		return (MALLOC_ERROR);
	g_struct.done_operations = malloc(sizeof(int) * g_struct.n_philos);
	if (g_struct.done_operations == NULL)
		return (MALLOC_ERROR);
	if (create_philos())
		return (MUTEX_INIT_ERROR);
	gettimeofday(&g_struct.time_s, NULL);
	start_threads(0);
	usleep(700);
	start_threads(1);
	s = monitoring(i);
	if (s)
		deattach_threads(s);
	return (0);
}

int	create_philos(void)
{
	int	i;

	i = 0;
	while (i < g_struct.n_philos)
	{
		g_struct.philos[i].start = 0;
		g_struct.philos[i].id = i + 1;
		g_struct.philos[i].when_ate = 0;
		if (pthread_mutex_init(&g_struct.philos[i].fork, NULL))
			return (MUTEX_INIT_ERROR);
		g_struct.philos[i].right_fork = &g_struct.philos[i].fork;
		if (i)
			g_struct.philos[i].left_fork = &g_struct.philos[i - 1].fork;
		i++;
	}
	g_struct.philos[0].left_fork = &g_struct.philos[i - 1].fork;
	gettimeofday(&g_struct.time_s, NULL);
	if (pthread_mutex_init(&g_struct.print, NULL))
		return (MUTEX_INIT_ERROR);
	if (pthread_mutex_init(&g_struct.sleep, NULL))
		return (MUTEX_INIT_ERROR);
	return (0);
}

int	start_threads(int evenorodd)
{
	while (evenorodd < g_struct.n_philos)
	{
		if (pthread_create(&g_struct.p_threads[evenorodd], NULL,
				routine, &g_struct.philos[evenorodd]))
			return (PTHREAD_ERROR_CREATE);
		evenorodd = evenorodd + 2;
	}
	return (0);
}

void	*routine(void *philos)
{
	int		how_long;
	t_philo	*temp;

	temp = (t_philo *)philos;
	how_long = g_struct.eat_iters;
	while (how_long)
	{
		pthread_mutex_lock(temp->right_fork);
		status_output(FORK, temp->id);
		pthread_mutex_lock(temp->left_fork);
		status_output(FORK, temp->id);
		temp->when_ate = get_act_time();
		status_output(EATING, temp->id);
		my_usleep(g_struct.time_to_eat);
		status_output(SLEEPING, temp->id);
		pthread_mutex_unlock(temp->right_fork);
		pthread_mutex_unlock(temp->left_fork);
		my_usleep(g_struct.time_to_sleep);
		status_output(THINKING, temp->id);
		if (how_long != -1)
			how_long = how_long - 1;
	}
	g_struct.summ_iters++;
	temp->done_operations = 1;
	return (0);
}

int	monitoring(int i)
{
	while (1)
	{
		i = -1;
		while (++i < g_struct.n_philos)
		{
			if (g_struct.summ_iters == g_struct.n_philos)
				return (END);
			if (g_struct.philos[i].done_operations != 1)
			{
				if (g_struct.philos[i].when_ate == 0)
				{
					g_struct.philos[i].when_ate = get_act_time_main();
					if (g_struct.philos[i].when_ate >= g_struct.time_to_eat)
						return (PHILO_DIED);
				}
				if ((get_act_time_main()
						- g_struct.philos[i].when_ate) > g_struct.time_to_die)
				{
					g_struct.died_id = i + 1;
					return (PHILO_DIED);
				}
			}	
		}
	}
}
