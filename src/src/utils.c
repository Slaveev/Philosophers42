/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:52:15 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/05 17:04:56 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

unsigned long long get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

int	ft_usleep(suseconds_t time)
{
	unsigned long long	start;

	start = get_time();
	while ((get_time() - start) < (long unsigned int)time)
		ft_usleep(time / 10);
	return (0);
}

void	one_philo(t_data *data)
{
	data->start_time = get_time();
	printf("%llu 1 is thinking\n", get_time() - data->start_time);
	ft_usleep(data->time_die * 1000);
	printf("%llu 1 died\n", get_time() - data->start_time);
}

int	full_philos(t_data *data)
{
	if (data->philos->meals_head == data->nb_full_philos)
	{
		pthread_mutex_lock(&data->anotherone1);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->anotherone1);
		return (1);
	}
	return (0);
}
