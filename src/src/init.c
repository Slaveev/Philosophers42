/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:36:57 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/05 16:44:30 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->nb_full_philos = ft_atoi(argv[5]);
		printf("nb_full_philos = %d\n", data->nb_full_philos);
	}
	else
		data->nb_full_philos = -1;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		free(data);
		return (NULL);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		free(data->philos);
		free(data);
		return (NULL);
	}
	pthread_mutex_init(&data->dead, NULL);
	data->dead_flag = 0;
	return (data);
}

t_philo	*init_philos(t_data *data)
{
	int i;

	if (!data || !data->philos)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_head = 0;
		data->philos[i].data = data;
		data->philos[i].state = WAITING;
		data->philos[i].last_time_eat = 0;
		data->keep_iteration = true;
		data->alive = true;
		pthread_mutex_init(&data->philos[i].mut_meals_had, NULL);
		pthread_mutex_init(&data->philos[i].mut_last_time_eat, NULL);
		pthread_mutex_init(&data->philos[i].mut_state, NULL);
		pthread_mutex_init(&data->dead, NULL);
		pthread_mutex_init(&data->anotherone, NULL);
		pthread_mutex_init(&data->anotherone1, NULL);
		pthread_mutex_init(&data->anotherone2, NULL);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->start_time = get_time();
		i++;
	}
	return (data->philos);
}
