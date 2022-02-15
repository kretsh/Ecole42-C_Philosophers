/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:29:54 by cowen             #+#    #+#             */
/*   Updated: 2021/12/06 18:09:27 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

# define DEAD 0
# define EATING 666
# define SLEEPING 888
# define THINKING 999
# define FORK 777
# define END 1
# define DELETE 1
# define OPEN 2
# define NO_DEADS 999

typedef struct s_philo
{
	pid_t			pid;
	int				iter;
}				t_philo;

typedef struct s_glob_data
{
	int				iter;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_iters;
	long			when_ate;
	long			when_ate_last_time;
	sem_t			*fork;
	sem_t			*printf;
	struct timeval	time_s;
	struct timeval	time_act;
	struct timeval	time_main;
	t_philo			philos;
	int				allpid[220];
}		t_glob_data;

t_glob_data	g_struct;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_strlen_is_digit(const char *str);
int		fill_arg(char *str, int arg);
int		parse_arguments(int argc, char **argv);
void	init_func(void);
int		create_philos(void);
int		main_process(void);
void	child_process(t_philo *per);
void	*monitor(void *ret);
void	status_output(int tid, int philid);
void	my_usleep(int value);
long	get_act_time(void);
long	get_act_time_main(void);
void	semunorlinked(int k);

#endif