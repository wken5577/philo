/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:48:59 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 14:34:15 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_arg_data	*arg_data)
{
	t_fork	**forks;
	int		i;

	i = -1;
	forks = arg_data->forks;
	while (++i < arg_data->num_philo)
	{
		if (forks[i]->status == 1)
			pthread_mutex_unlock(&(forks[i]->mutex));
	}
}

void	join_all_thread(t_arg_data *arg_data, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < arg_data->num_philo)
	{
		if (pthread_join(philos[i]->thd, NULL) != 0)
			return ;
	}
}

int	start_make(t_thread_data **thread_data, t_arg_data *arg_data, \
				t_philo **philos, int n)
{
	int	i;

	i = -1;
	while (++i < arg_data->num_philo)
	{
		if (i % 2 == n)
		{
			set_time(philos, i);
			if (pthread_create(&(philos[i]->thd), NULL, start_think, \
					thread_data[i]) != 0)
			{
				release_data((void **) philos, arg_data->num_philo);
				return (0);
			}
		}
	}
	return (1);
}
