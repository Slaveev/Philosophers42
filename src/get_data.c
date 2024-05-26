/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:21:59 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:26:05 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_philos(t_data *data)
{
	int	philo_num;

	pthread_mutex_lock(&data->mut_nb_philo);
	philo_num = data->nb_philo;
	pthread_mutex_unlock(&data->mut_nb_philo);
	return (philo_num);
}

t_state	get_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->mut_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}

uint16_t	get_sleep_time(t_data *data)
{
	uint64_t	sleep_time;

	pthread_mutex_lock(&data->mut_sleep_time);
	sleep_time = data->time_sleep;
	pthread_mutex_unlock(&data->mut_sleep_time);
	return (sleep_time);
}

uint64_t	get_eat_time(t_data *data)
{
	uint64_t	eat_time;

	pthread_mutex_lock(&data->mut_eat_time);
	eat_time = data->time_eat;
	pthread_mutex_unlock(&data->mut_eat_time);
	return (eat_time);
}

uint64_t	get_die_time(t_data *data)
{
	uint64_t	die_time;

	pthread_mutex_lock(&data->mut_die_time);
	die_time = data->time_die;
	pthread_mutex_unlock(&data->mut_die_time);
	return (die_time);
}
