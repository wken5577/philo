/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:26:39 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 14:27:24 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	init_fork(t_philo **philos, t_arg_data *arg_data)
{
	t_fork	**forks;
	int		i;

	forks = arg_data->forks;
	i = -1;
	while (++i < arg_data->num_philo)
	{
		philos[i]->lfork = forks[i];
		philos[i]->rfork = forks[(i + 1) % arg_data->num_philo];
	}
}

t_philo	**allocate_ph(t_arg_data *arg_data)
{
	t_philo		**result;
	int			i;

	result = malloc(sizeof(t_philo *) * arg_data->num_philo);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < arg_data->num_philo)
	{
		result[i] = malloc(sizeof(t_philo));
		if (!result[i])
		{
			release_data((void **)result, i);
			return (NULL);
		}
		result[i]->eat_cnt = 0;
	}
	init_fork(result, arg_data);
	return (result);
}

void	*start_think(void *data)
{
	t_philo		**philos;
	int			idx;
	t_arg_data	*arg_data;

	philos = ((t_thread_data *) data)->philos;
	arg_data = ((t_thread_data *) data)->arg_data;
	idx = ((t_thread_data *) data)->idx;
	if (arg_data->num_philo == 1)
		return (NULL);
	while (!arg_data->stop_flag)
	{
		if (philos[idx]->eat_cnt >= arg_data->eat_num)
			return (NULL);
		pickup(philos, idx, arg_data);
		do_sleep(philos, idx, arg_data);
		do_think(philos, idx, arg_data);
	}
	return (NULL);
}

void	make_thread(t_arg_data *arg_data, t_philo **philos)
{
	t_thread_data	**thread_data;
	int				i;

	thread_data = get_thread_data(philos, arg_data, i);
	if (!thread_data)
		return ;
	start_make(thread_data, arg_data, philos, 0);
	start_make(thread_data, arg_data, philos, 1);
	i = monitering(philos, arg_data);
	if (i >= 0)
		write_log(i, DIED, arg_data, philos);
	else
		arg_data->stop_flag = 1;
	join_all_thread(arg_data, philos);
	release_data((void **)thread_data, arg_data->num_philo);
}

int	main(int argc, char **argv)
{
	t_arg_data	*arg_data;
	t_philo		**philos;

	if (!(argc == 6 || argc == 5))
		return (0);
	arg_data = init_arg_data(argc, argv);
	if (!arg_data)
		return (0);
	philos = allocate_ph(arg_data);
	if (!philos)
		return (0);
	make_thread(arg_data, philos);
	release_data((void **)philos, arg_data->num_philo);
	release_arg_data(arg_data);
}
