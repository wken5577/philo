/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:00:37 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 19:02:56 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_time(t_philo **philo, int idx)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo[idx]->last_eat = time.tv_sec * 1000 + time.tv_usec / 1000;
}

void	my_usleep(long usleep_time)
{
	struct timeval	time;
	int				start_time;
	int				now;

	gettimeofday(&time, NULL);
	start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	usleep((usleep_time * 1000) * 0.7);
	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (now - start_time < usleep_time)
	{
		usleep(500);
		gettimeofday(&time, NULL);
		now = time.tv_sec * 1000 + time.tv_usec / 1000;
	}
}

void	monitering(t_philo **philos, t_arg_data *arg_data, int n)
{
	struct timeval	time;
	int				now;
	int				data;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (now - philos[n]->last_eat > arg_data->time_to_die)
	{
		write_log(n, DIED, arg_data, philos);
		release_data((void **)philos, arg_data->num_philo);
		release_arg_data(arg_data);
		kill(0, SIGKILL);
	}
}

t_thread_data	*get_thread_data(t_arg_data *arg_data, t_philo **philos, int n)
{
	t_thread_data	*result;

	result = malloc(sizeof (t_thread_data *));
	if (!result)
		return (0);
	result->idx = n;
	result->philos = philos;
	result->arg_data = arg_data;
	return (result);
}

void	send_signal(t_arg_data *arg_data)
{
	int	i;

	i = -1;
	while (++i < arg_data->num_philo)
	{
		kill((arg_data->pids)[i], SIGCONT);
	}
}
