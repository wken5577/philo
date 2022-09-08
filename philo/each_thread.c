/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   each_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:29:08 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 19:13:14 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo **philos, int idx, t_arg_data *arg_data)
{
	write_log(idx, EATING, arg_data, philos);
	my_usleep(arg_data->time_to_eat);
}

void	pick_fork(t_fork *fork)
{
	pthread_mutex_lock(&(fork->mutex));
	fork->status = 1;
}

void	put_down(t_fork *fork)
{
	fork->status = 0;
	pthread_mutex_unlock((&fork->mutex));
}

void	pickup(t_philo **philos, int idx, t_arg_data *arg_data)
{
	if (philos[idx]->eat_cnt >= arg_data->eat_num || \
			arg_data->stop_flag)
		return ;
	if ((idx + 1) % 2 == 0)
	{
		pick_fork(philos[idx]->lfork);
		pick_fork(philos[idx]->rfork);
		write_log(idx, TAKE_FORK, arg_data, philos);
		eat(philos, idx, arg_data);
		put_down(philos[idx]->lfork);
		put_down(philos[idx]->rfork);
	}
	else if ((idx + 1) % 2 == 1)
	{
		pick_fork(philos[idx]->rfork);
		pick_fork(philos[idx]->lfork);
		write_log(idx, TAKE_FORK, arg_data, philos);
		eat(philos, idx, arg_data);
		put_down(philos[idx]->rfork);
		put_down(philos[idx]->lfork);
	}
}
