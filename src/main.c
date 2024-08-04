/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:53:57 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/04 16:40:13 by dslaveev         ###   ########.fr       */
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

void print_status(t_philo *philosopher, const char *msg)
{
    pthread_mutex_lock(&philosopher->data->print_mutex);
    printf("%lu %d %s\n", get_time() - philosopher->data->start_time, philosopher->id, msg);
    pthread_mutex_unlock(&philosopher->data->print_mutex);
}

void	think(t_philo *philosopher)
{
	print_status(philosopher, THINK);
    philosopher->state = THINKING;
}

void	sleep_philo(t_philo *philosopher)
{
	print_status(philosopher, SLEEP);
    philosopher->state = SLEEPING;
    ft_usleep(philosopher->data->time_sleep * 1000);
}

void eat(t_philo *philosopher)
{
    pthread_mutex_t *first;
    pthread_mutex_t *second;

    if (philosopher->left_fork < philosopher->right_fork)
    {
        first = philosopher->left_fork;
        second = philosopher->right_fork;
    }
    else
    {
        first = philosopher->right_fork;
        second = philosopher->left_fork;
    }
    pthread_mutex_lock(first);
    print_status(philosopher, FORKS);
    pthread_mutex_lock(second);
    print_status(philosopher, FORKS);
    print_status(philosopher, EAT);
    philosopher->state = EATING;
    philosopher->last_time_eat = get_time();
    ft_usleep(philosopher->data->time_eat);
    pthread_mutex_unlock(first);
    pthread_mutex_unlock(second);
}

void *monitoring(void *data)
{
	t_data				*philo_data;
	uint16_t			time_diff_ms;

	philo_data = (t_data *)data;
	while (philo_data->keep_iteration && philo_data->alive)
	{
		for (int i = 0; i < philo_data->nb_philo; i++)
		{
			pthread_mutex_lock(&philo_data->philos[i].mut_last_time_eat);
			time_diff_ms = (get_time() - philo_data->philos[i].last_time_eat);
			if (time_diff_ms > philo_data->time_die)
			{
				philo_data->alive = false;
				pthread_mutex_unlock(&philo_data->philos[i].mut_last_time_eat);
				pthread_mutex_lock(&philo_data->dead);
				philo_data->dead_flag = 1;
				pthread_mutex_unlock(&philo_data->dead);
				return (NULL);
			}
			pthread_mutex_unlock(&philo_data->philos[i].mut_last_time_eat);
			if (!philo_data->alive) break;
		}
		ft_usleep(1000);
	}
	return (NULL);
}

int	full_philos(t_data *data)
{
	if (data->philos->meals_head == data->nb_full_philos)
	{
		pthread_mutex_lock(&data->dead);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*philosopher;
	pthread_t	monitor;

	philosopher = (t_philo *)philo;
	if (philosopher->id % 2)
		sleep_philo(philosopher);
	while (1)
	{
		if (full_philos(philosopher->data))
			break ;
		pthread_create(&monitor, NULL, &monitoring, philosopher->data);
		pthread_mutex_lock(&philosopher->data->dead);
		if (philosopher->data->dead_flag) {
			pthread_mutex_unlock(&philosopher->data->dead);
			break;
		}
		pthread_mutex_unlock(&philosopher->data->dead);
		eat(philosopher);
		sleep_philo(philosopher);
		think(philosopher);
		philosopher->meals_head++;
		pthread_mutex_lock(&philosopher->data->dead);
		if (philosopher->data->dead_flag) {
			pthread_mutex_unlock(&philosopher->data->dead);
			break;
		}
		pthread_mutex_unlock(&philosopher->data->dead);
	}
	return (NULL);
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

	philos = NULL;
	if (!check_args(argc, argv))
		return (WRONG_INPUT);
	data = init_data(argc, argv);
	philos = init_philos(data);
	if (!data)
		return (MALLOC_ERROR);
	if (data->nb_philo == 1)
		return (one_philo(data));
	fork_start(data);
	// print_data(data);
	free(data);
	return (0);
}
