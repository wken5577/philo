/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   each_thread1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:37:53 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 09:45:16 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_sleep(t_philo **philos, int idx, t_arg_data *arg_data)
{
	if (philos[idx]->eat_cnt >= arg_data->eat_num || \
			arg_data->stop_flag)
		return ;
	write_log(idx, SLEEPING, arg_data, philos);
	my_usleep(arg_data->time_to_sleep);
}

void	do_think(t_philo **philos, int idx, t_arg_data *arg_data)
{
	if (philos[idx]->eat_cnt >= arg_data->eat_num || \
			arg_data->stop_flag)
		return ;
	write_log(idx, THINKING, arg_data, philos);
}
