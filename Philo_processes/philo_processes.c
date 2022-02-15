/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:20:21 by cowen             #+#    #+#             */
/*   Updated: 2021/12/12 12:59:46 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_processes.h"

void	init_func(void)
{
	semunorlinked(OPEN);
	gettimeofday(&g_struct.time_s, NULL);
	create_philos();
	if (g_struct.iter == g_struct.n_philos)
		main_process();
	else
	{
		g_struct.iter++;
		child_process(&g_struct.philos);
	}
	semunorlinked(DELETE);
}

int	create_philos(void)
{
	g_struct.iter = 0;
	while (g_struct.iter < g_struct.n_philos)
	{
		g_struct.allpid[g_struct.iter] = fork();
		if (!g_struct.allpid[g_struct.iter])
			break ;
		g_struct.iter++;
	}
	return (0);
}

int	main_process(void)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < g_struct.n_philos)
	{
		waitpid(-1, &ret, 0);
		if (ret == DEAD)
		{
			i = -1;
			while (++i < g_struct.n_philos)
				kill(g_struct.allpid[i], SIGTERM);
			break ;
		}
	}
	return (NO_DEADS);
}

void	child_process(t_philo *per)
{	
	pthread_t	mon;

	pthread_create(&mon, NULL, monitor, per);
	pthread_detach(mon);
	usleep((g_struct.iter % 2) * 100);
	while (g_struct.eat_iters)
	{
		sem_wait(g_struct.fork);
		status_output(FORK, g_struct.iter);
		sem_wait(g_struct.fork);
		status_output(FORK, g_struct.iter);
		status_output(EATING, g_struct.iter);
		my_usleep(g_struct.time_to_eat);
		sem_post(g_struct.fork);
		sem_post(g_struct.fork);
		if (g_struct.eat_iters != -1)
			g_struct.eat_iters--;
		if (g_struct.eat_iters)
		{
			status_output(SLEEPING, g_struct.iter);
			my_usleep(g_struct.time_to_sleep);
			status_output(THINKING, g_struct.iter);
		}
	}
	exit (END);
}

void	*monitor(void *ret)
{
	t_philo	*temp;

	temp = (t_philo *) ret;
	while (1)
	{
		if (g_struct.when_ate == 0)
		{
			g_struct.when_ate = get_act_time_main();
			if (g_struct.when_ate >= g_struct.time_to_eat)
			{	
				sem_wait(g_struct.printf);
				printf("%ld %d died\n", get_act_time_main(), g_struct.iter);
				exit (DEAD);
			}
		}
		if ((get_act_time_main() - g_struct.when_ate) > g_struct.time_to_die)
		{
			sem_wait(g_struct.printf);
			printf("%ld %d died\n", get_act_time_main(), g_struct.iter);
			exit (DEAD);
		}
		usleep(500);
	}
}
