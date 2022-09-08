/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:26:37 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 09:44:48 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_fork
{
	int				status;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_arg_data
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				eat_num;
	t_fork			**forks;
	pthread_mutex_t	mutex;
	int				stop_flag;
	struct timeval	start_time;
	int				default_flag;
}	t_arg_data;

typedef enum e_action
{
	TAKE_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_action;

typedef struct s_philo
{
	pthread_t		thd;
	t_fork			*lfork;
	t_fork			*rfork;
	int				last_eat;
	int				eat_cnt;
}	t_philo;

typedef struct s_thread_data
{
	t_philo		**philos;
	t_arg_data	*arg_data;
	int			idx;
}	t_thread_data;

int				ft_atoi(const char *str, int *is_overflow);
t_arg_data		*init_arg_data(int argc, char **argv);
void			write_log(int idx, t_action action, \
						t_arg_data *arg_data, t_philo **philos);
void			pickup(t_philo **philos, int idx, t_arg_data *arg_data);
void			do_sleep(t_philo **philos, int idx, t_arg_data *arg_data);
void			do_think(t_philo **philos, int idx, t_arg_data *arg_data);
void			release_arg_data(t_arg_data	*arg_data);
void			release_data(void **data, int n);
void			set_time(t_philo **philo, int idx);
void			my_usleep(long usleep_time);
int				monitering(t_philo **philos, t_arg_data *arg_data);
t_thread_data	**get_thread_data(t_philo **philos, \
						t_arg_data *arg_data, int idx);
void			unlock_forks(t_arg_data	*arg_data);
void			join_all_thread(t_arg_data *arg_data, t_philo **philos);
void			*start_think(void *data);
int				start_make(t_thread_data **thread_data, t_arg_data *arg_data, \
				t_philo **philos, int n);
#endif