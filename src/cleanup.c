/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:39:28 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/04 15:02:02 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_one(t_data *data)
{
	pthread_mutex_destroy(&data->philos[0].mut_meals_had);
	pthread_mutex_destroy(&data->philos[0].mut_last_time_eat);
	pthread_mutex_destroy(&data->philos[0].mut_state);
	if (data->philos[0].left_fork != NULL)
		pthread_mutex_destroy(data->philos[0].left_fork);
	if (data->philos[0].right_fork != NULL)
		pthread_mutex_destroy(data->philos[0].right_fork);
	pthread_mutex_destroy(&data->dead);
	if (data->forks != NULL)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos != NULL)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
