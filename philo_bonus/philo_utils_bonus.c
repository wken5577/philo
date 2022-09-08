/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:39:50 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/09/08 18:24:26 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	validation(int is_of[], t_arg_data	*result)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (is_of[i])
		{
			return (0);
		}
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

int	init_pids_sem(t_arg_data *arg_data)
{
	pid_t	*pids;
	sem_t	*p_psem;
	sem_t	*log_sem;

	if ((sem_unlink(NAME_POSIX_SEM) != 0 && errno != ENOENT) || \
			sem_unlink(LOG_POSIX_SEM) != 0 && errno != ENOENT)
		return (0);
	pids = malloc (sizeof(pid_t) * arg_data->num_philo);
	if (!pids)
		return (0);
	arg_data->pids = pids;
	p_psem = sem_open(NAME_POSIX_SEM, O_CREAT, S_IRWXU, arg_data->num_philo);
	log_sem = sem_open(LOG_POSIX_SEM, O_CREAT, S_IRWXU, 1);
	if (p_psem == SEM_FAILED || log_sem == SEM_FAILED)
	{
		free (pids);
		return (0);
	}
	arg_data->p_psem = p_psem;
	arg_data->log_sem = log_sem;
	return (1);
}

void	release_arg_data(t_arg_data	*arg_data)
{
	if (sem_close(arg_data->log_sem) == -1 || sem_unlink(LOG_POSIX_SEM) == -1 \
	|| sem_close(arg_data->p_psem) == -1 || sem_unlink(NAME_POSIX_SEM) == -1)
	{
		free(arg_data->pids);
		free(arg_data);
		return ;
	}
	free(arg_data->pids);
	free(arg_data);
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
	if (!validation(is_of, result) || !init_pids_sem(result))
	{
		free(result);
		return (NULL);
	}
	gettimeofday(&(result->start_time), NULL);
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
