/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:53:57 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/05 16:56:17 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Wrong input\n");
		printf("<number_of_philosophers>, <time_to_die>,");
		printf("<time_to_eat>, <time_to_sleep>,");
		return (0);
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		printf("Wrong number of philosophers\n");
		return (0);
	}
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
	{
		printf("Try normal numbers\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("Please\n");
		return (0);
	}
	return (1);
}

void	fork_start(t_data *data)
{
	int i;
	pthread_t	monitor_thread;

	for (i = 0; i < data->nb_philo; i++)
	{
		pthread_mutex_init(&data->forks[i], NULL);
	}
	data->start_time = get_time();
	for (i = 0; i < data->nb_philo; i++)
    {
		data->philos[i].last_time_eat = data->start_time;
	}
	pthread_create(&monitor_thread, NULL, &monitoring, data);
	for (i = 0; i < data->nb_philo; i++)
	{
		pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]);
	}
	for (i = 0; i < data->nb_philo; i++)
	{
		pthread_join(data->philos[i].thread, NULL);
	}
	pthread_join(monitor_thread, NULL);
}

void	die()
{
	printf("Philosopher died\n");
	exit(0);
}


int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	(void)philos;
	philos = NULL;
	if (!check_args(argc, argv))
		return (WRONG_INPUT);
	data = init_data(argc, argv);
	philos = init_philos(data);
	if (!data)
		return (MALLOC_ERROR);
	if (data->nb_philo == 1)
		one_philo(data);
	else
		fork_start(data);
	cleanup(data);
	free(data);
	return (0);
}
