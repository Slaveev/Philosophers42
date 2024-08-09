/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:29:30 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/09 18:32:06 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_flag(t_data *philo_data)
{
	pthread_mutex_lock(&philo_data->dead);
	if (philo_data->dead_flag)
	{
		pthread_mutex_unlock(&philo_data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo_data->dead);
	return (0);
}

int	check_state(t_data *philo_data)
{
	int	i;

	i = -1;
	while (++i < philo_data->nb_philo)
	{
		pthread_mutex_lock(&philo_data->philos[i].mut_state);
		if ((get_time() - philo_data->philos[i].last_time_eat)
			> (unsigned long long)philo_data->time_die)
		{
			printf("%llu %d died\n", get_time() - philo_data->start_time,
				philo_data->philos[i].id);
			pthread_mutex_lock(&philo_data->dead);
			philo_data->dead_flag = 1;
			pthread_mutex_unlock(&philo_data->dead);
			pthread_mutex_unlock(&philo_data->philos[i].mut_state);
			return (1);
		}
		pthread_mutex_unlock(&philo_data->philos[i].mut_state);
	}
	return (0);
}

void	*monitoring(void *data)
{
	t_data	*philo_data;

	philo_data = (t_data *)data;
	while (1)
	{
		if (full_philos(philo_data))
			return (NULL);
		if (check_flag(philo_data))
			return (NULL);
		if (check_state(philo_data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

// void	*monitoring(void *data)
// {
// 	t_data	*philo_data;
// 	int		i;

// 	philo_data = (t_data *)data;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo_data->dead);
// 		if (philo_data->dead_flag)
// 		{
// 			pthread_mutex_unlock(&philo_data->dead);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&philo_data->dead);
// 		i = -1;
// 		while (++i < philo_data->nb_philo)
// 		{
// 			pthread_mutex_lock(&philo_data->philos[i].mut_state);
// 			if ((get_time() - philo_data->philos[i].last_time_eat)
// 				> (unsigned long long)philo_data->time_die)
// 			{
// 				pthread_mutex_lock(&philo_data->dead);
// 				philo_data->dead_flag = 1;
// 				pthread_mutex_unlock(&philo_data->dead);
// 				pthread_mutex_unlock(&philo_data->philos[i].mut_state);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&philo_data->philos[i].mut_state);
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
// }
