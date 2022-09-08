/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   each_philos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:05:51 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 19:18:35 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo **philos, int idx, t_arg_data *arg_data)
{
	write_log(idx, EATING, arg_data, philos);
	my_usleep(arg_data->time_to_eat);
}

void	pick_up(t_arg_data *arg_data, t_philo **philos, int n)
{
	if (philos[n]->eat_cnt >= arg_data->eat_num)
		exit(0);
	sem_wait(arg_data->p_psem);
	sem_wait(arg_data->p_psem);
	write_log(n, TAKE_FORK, arg_data, philos);
	eat(philos, n, arg_data);
	sem_post(arg_data->p_psem);
	sem_post(arg_data->p_psem);
}

void	do_sleep(t_philo **philos, int idx, t_arg_data *arg_data)
{
	if (philos[idx]->eat_cnt >= arg_data->eat_num)
		exit(0);
	write_log(idx, SLEEPING, arg_data, philos);
	my_usleep(arg_data->time_to_sleep);
}

void	do_think(t_philo **philos, int idx, t_arg_data *arg_data)
{
	if (philos[idx]->eat_cnt >= arg_data->eat_num)
		exit(0);
	write_log(idx, THINKING, arg_data, philos);
}

void	*start_monitering(void *data)
{
	t_thread_data	*thread_data;

	thread_data = (t_thread_data *) data;
	while (1)
	{
		monitering(thread_data->philos, \
				thread_data->arg_data, thread_data->idx);
		usleep(200);
	}
	return (0);
}
