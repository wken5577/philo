/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:50:50 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 11:06:51 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <errno.h>
# include <signal.h>

typedef struct s_arg_data
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				eat_num;
	struct timeval	start_time;
	pid_t			*pids;
	sem_t			*p_psem;
	sem_t			*log_sem;
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
	int				last_eat;
	int				eat_cnt;
	pthread_t		thd;
}	t_philo;

typedef struct s_thread_data
{
	t_philo		**philos;
	t_arg_data	*arg_data;
	int			idx;
}	t_thread_data;

# define NAME_POSIX_SEM "./mysem"
# define LOG_POSIX_SEM "./logsem"

void			release_data(void **data, int n);
t_arg_data		*init_arg_data(int argc, char **argv);
void			write_log(int idx, t_action action, \
						t_arg_data *arg_data, t_philo **philos);
void			set_time(t_philo **philo, int idx);
void			my_usleep(long usleep_time);
void			do_think(t_philo **philos, int idx, t_arg_data *arg_data);
void			do_sleep(t_philo **philos, int idx, t_arg_data *arg_data);
void			pick_up(t_arg_data *arg_data, t_philo **philos, int n);
int				ft_atoi(const char *str, int *is_overflow);
t_thread_data	*get_thread_data(t_arg_data *arg_data, t_philo **philos, int n);
void			monitering(t_philo **philos, t_arg_data *arg_data, int n);
void			*start_monitering(void *data);
void			release_arg_data(t_arg_data	*arg_data);
void			send_signal(t_arg_data *arg_data);
#endif