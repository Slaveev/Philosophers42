/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:29:30 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/05 17:08:12 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *monitoring(void *data)
{
	t_data *philo_data;
	int i;

	philo_data = (t_data *)data;
	while (1)
	{
		pthread_mutex_lock(&philo_data->anotherone2);
		if (philo_data->dead_flag)
		{
			pthread_mutex_unlock(&philo_data->anotherone2);
			return (NULL);
		}
		pthread_mutex_unlock(&philo_data->anotherone2);
		i = -1;
		while (++i < philo_data->nb_philo)
		{
			pthread_mutex_lock(&philo_data->philos[i].mut_state);
			if ((get_time() - philo_data->philos[i].last_time_eat) > (unsigned long long)philo_data->time_die)
			{
				pthread_mutex_lock(&philo_data->dead);
				philo_data->dead_flag = 1;
				pthread_mutex_unlock(&philo_data->dead);
				pthread_mutex_unlock(&philo_data->philos[i].mut_state);
				return (NULL);
			}
			pthread_mutex_unlock(&philo_data->philos[i].mut_state);
		}
		usleep(100);
	}
	return (NULL);
}
