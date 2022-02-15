/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:34:01 by cowen             #+#    #+#             */
/*   Updated: 2021/12/06 15:12:12 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

# define MUTEX_INIT_ERROR -1
# define MALLOC_ERROR -2
# define PTHREAD_ERROR_CREATE -3
# define FORK 777
# define EATING 666
# define SLEEPING 888
# define THINKING 999
# define PHILO_DIED 555
# define END 444

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				when_ate;
	long			start;
	long			done_operations;	
}				t_philo;

typedef struct s_glob_data
{
	int				iterator;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_iters;
	int				summ_iters;
	int				died_id;
	int				*done_operations;
	struct timeval	time_s;
	struct timeval	time_act;
	struct timeval	time_main;
	t_philo			*philos;
	pthread_t		*p_threads;
	pthread_mutex_t	print;
	pthread_mutex_t	sleep;
}		t_glob_data;

t_glob_data	g_struct;

int		ft_strlen_is_digit(const char *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		parse_arguments(int argc, char **argv);
int		fill_arg(char *str, int arg);
int		init_func(void);
int		create_philos(void);
int		start_threads(int evenorodd);
void	*routine(void *philos);
void	status_output(int tid, int philid);
long	get_act_time(void);
void	my_usleep(int value);
int		monitoring(int i);
long	get_act_time_main(void);
void	deattach_threads(int id);

#endif