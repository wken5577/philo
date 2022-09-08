/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:24:33 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 19:13:16 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_died(int time, int idx, t_arg_data *arg_data)
{
	arg_data->stop_flag = 1;
	printf("%d %d died\n", time, idx);
}

void	print_eat(int time, int idx, t_arg_data *arg_data, t_philo **philos)
{
	set_time(philos, idx);
	printf("%d %d is eating\n", time, idx);
	if (arg_data->default_flag != 1)
		philos[idx]->eat_cnt += 1;
}

void	write_log(int idx, t_action action, \
						t_arg_data *arg_data, t_philo **philos)
{	
	struct timeval	time;
	int				start_time;
	int				now;

	pthread_mutex_lock(&(arg_data->mutex));
	if (arg_data->stop_flag == 1)
	{
		pthread_mutex_unlock(&(arg_data->mutex));
		return ;
	}
	gettimeofday(&time, NULL);
	start_time = arg_data->start_time.tv_sec * 1000 \
		+ arg_data->start_time.tv_usec / 1000;
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (action == TAKE_FORK)
		printf("%d %d has taken a fork\n", now - start_time, idx);
	else if (action == EATING)
		print_eat(now - start_time, idx, arg_data, philos);
	else if (action == SLEEPING)
		printf("%d %d is sleeping\n", now - start_time, idx);
	else if (action == THINKING)
		printf("%d %d is thinking\n", now - start_time, idx);
	else if (action == DIED)
		print_died(now - start_time, idx, arg_data);
	pthread_mutex_unlock(&(arg_data->mutex));
}
