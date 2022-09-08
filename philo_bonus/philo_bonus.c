/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:50:14 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 18:49:30 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

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
	return (result);
}

void	start_think(t_arg_data *arg_data, t_philo **philos, int n)
{
	t_thread_data	*thread_data;

	thread_data = get_thread_data(arg_data, philos, n);
	if (!thread_data)
		return ;
	set_time(philos, n);
	if (pthread_create(&(philos[n]->thd), NULL, start_monitering, \
			(void *) thread_data) != 0 || pthread_detach(philos[n]->thd) != 0)
		return ;
	if (arg_data->num_philo == 1)
		usleep(arg_data->time_to_die * 2 * 1000);
	while (1)
	{
		pick_up(arg_data, philos, n);
		do_sleep(philos, n, arg_data);
		do_think(philos, n, arg_data);
	}
}

void	make_process(t_arg_data *arg_data, t_philo **philos, int n)
{
	pid_t	pid;

	if (n == arg_data->num_philo)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		(arg_data->pids)[n] = pid;
		kill(pid, SIGSTOP);
		make_process(arg_data, philos, n + 1);
	}
	else
		start_think(arg_data, philos, n);
}

void	wait_all_pids(t_arg_data *arg_data)
{
	int	i;

	i = -1;
	while (++i < arg_data->num_philo)
	{
		waitpid((arg_data->pids)[i], NULL, 0);
	}
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
	make_process(arg_data, philos, 0);
	send_signal(arg_data);
	wait_all_pids(arg_data);
	release_data((void **)philos, arg_data->num_philo);
	release_arg_data(arg_data);
}
