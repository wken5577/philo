/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:38:19 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 19:09:41 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_arg_data(t_arg_data	*arg_data)
{
	int	i;

	i = -1;
	unlock_forks(arg_data);
	while (++i < arg_data->num_philo)
	{
		if (pthread_mutex_destroy(&(arg_data->forks[i]->mutex)) != 0)
		{
			release_data((void **) arg_data->forks, arg_data->num_philo);
			free (arg_data);
			return ;
		}
	}
	if (pthread_mutex_destroy(&(arg_data->mutex)) != 0)
	{
		release_data((void **) arg_data->forks, arg_data->num_philo);
		free (arg_data);
		return ;
	}
	release_data((void **) arg_data->forks, arg_data->num_philo);
	free(arg_data);
}

int	eat_all(t_philo **philos, t_arg_data *arg_data)
{
	int	i;

	i = -1;
	while (++i < arg_data->num_philo)
	{
		if (philos[i]->eat_cnt < arg_data->eat_num)
			return (0);
	}
	return (1);
}

int	monitering(t_philo **philos, t_arg_data *arg_data)
{
	struct timeval	time;
	int				i;
	int				now;

	while (1)
	{
		i = -1;
		while (++i < arg_data->num_philo)
		{
			if (eat_all(philos, arg_data))
				return (-1);
			gettimeofday(&time, NULL);
			now = time.tv_sec * 1000 + time.tv_usec / 1000;
			pthread_mutex_lock(&(arg_data->mutex));
			if (now - philos[i]->last_eat > arg_data->time_to_die)
			{
				pthread_mutex_unlock(&(arg_data->mutex));
				return (i);
			}
			pthread_mutex_unlock(&(arg_data->mutex));
		}
		usleep(200);
	}
}

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
