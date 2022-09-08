/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:35:15 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/08/30 15:08:35 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

static int	is_space(char ch)
{
	return (ch == '\t' || ch == '\n' || ch == '\f' || ch == '\v'
		|| ch == '\r' || ch == ' ');
}

static int	make_return_value(int flag, char str[], int i, int *overflow)
{
	unsigned long long	result;

	result = 0;
	while (str[i] != 0 && '0' <= str[i] && str[i] <= '9')
	{
		result *= 10;
		result += (str[i] - '0');
		if (flag == 1 && result > INT32_MAX && overflow)
		{
			*overflow = 1;
			break ;
		}
		else if (flag == -1 && result - 1 > INT32_MAX && overflow)
		{
			*overflow = 1;
			break ;
		}
		i++;
	}
	return (result * flag);
}

int	ft_atoi(const char *str, int *is_overflow)
{
	int					flag;
	int					i;

	i = 0;
	flag = 1;
	*is_overflow = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
	{
		i++;
		flag = -1;
	}
	else if (str[i] == '+')
		i++;
	return (make_return_value(flag, (char *)str, i, is_overflow));
}
