/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:15:42 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:15:44 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_threads(t_data *data)
{
	int	philos;
	int	i;

	philos = get_philos(data);
	i = 0;
	data->start_time = get_time();
	while (i < philos)
	{
		if (pthread_create(&data->ths[i], NULL, &routine, &data->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&data->all_alive, NULL, &check_all_alive, data))
		return (1);
	if (nb_meals(data) == 1
		&& pthread_create(&data->all_eaten, NULL, &check_all_eaten, data))
		return (1);
	return (0);
}

int	join_threads(t_data *data)
{
	int	philos;
	int	i;

	philos = get_philos(data);
	i = 0;
	if (pthread_join(data->all_alive, NULL))
		return (1);
	if (nb_meals(data) == 1 && pthread_join(data->all_eaten, NULL))
		return (1);
	while (i < philos)
	{
		if (pthread_join(data->ths[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
