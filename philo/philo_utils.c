/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:39:50 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/07 18:21:49 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validation_init_rest(int is_of[], t_arg_data *result)
{
	int	i;

	i = 0;
	result->stop_flag = 0;
	gettimeofday(&(result->start_time), NULL);
	while (i < 5)
	{
		if (is_of[i])
			return (0);
		i++;
	}
	if (result->num_philo < 1)
		return (0);
	else if (result->time_to_die < 1)
		return (0);
	else if (result->time_to_eat < 1)
		return (0);
	else if (result->time_to_sleep < 1)
		return (0);
	else if (result->eat_num < 1)
		return (0);
	return (1);
}

int	allocate_fork(t_arg_data *arg_data)
{
	t_fork	**forks;
	int		i;

	forks = malloc(sizeof(t_fork *) * arg_data->num_philo);
	if (!forks)
		return (0);
	i = -1;
	while (++i < arg_data->num_philo)
	{
		forks[i] = malloc (sizeof (t_fork));
		if (!forks[i] || pthread_mutex_init(&(forks[i]->mutex), NULL) != 0)
		{
			release_data((void **) forks, i);
			return (0);
		}
		forks[i]->status = 0;
	}
	arg_data->forks = forks;
	if (pthread_mutex_init(&(arg_data->mutex), NULL) != 0)
	{
		release_data((void **) forks, arg_data->num_philo);
		return (0);
	}
	return (1);
}

t_arg_data	*init_arg_data(int argc, char **argv)
{
	t_arg_data	*result;
	int			is_of[5];

	result = malloc(sizeof(t_arg_data));
	if (!result)
		return (NULL);
	result->default_flag = 0;
	result->num_philo = ft_atoi(argv[1], &is_of[0]);
	result->time_to_die = ft_atoi(argv[2], &is_of[1]);
	result->time_to_eat = ft_atoi(argv[3], &is_of[2]);
	result->time_to_sleep = ft_atoi(argv[4], &is_of[3]);
	if (argc == 6)
		result->eat_num = ft_atoi(argv[5], &is_of[4]);
	else
	{
		result->default_flag = 1;
		result->eat_num = ft_atoi("5", &is_of[4]);
	}
	if (!validation_init_rest(is_of, result) || !allocate_fork(result))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

void	release_data(void **data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

t_thread_data	**get_thread_data(t_philo **philos, \
									t_arg_data *arg_data, int idx)
{
	t_thread_data	**result;
	int				i;

	result = malloc (sizeof(t_thread_data *) * arg_data->num_philo);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < arg_data->num_philo)
	{
		result[i] = malloc(sizeof(t_thread_data));
		if (!result[i])
		{
			release_data((void **) philos, arg_data->num_philo);
			release_data((void **) result, i);
			return (NULL);
		}
		result[i]->arg_data = arg_data;
		result[i]->idx = i;
		result[i]->philos = philos;
	}
	return ((void *) result);
}
