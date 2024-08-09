/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:28:48 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/09 18:34:16 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *philo)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)philo;
	if (philosopher->id % 2 == 0)
		usleep(philosopher->data->time_eat - 10);
	while (1)
	{
		if (full_philos(philosopher->data))
			return (NULL);
		if (check_flag(philosopher->data))
			return (NULL);
		eat(philosopher);
		if (check_flag(philosopher->data))
			return (NULL);
		sleep_philo(philosopher);
		if (check_flag(philosopher->data))
			return (NULL);
		think(philosopher);
		if (check_flag(philosopher->data))
			return (NULL);
		pthread_mutex_lock(&philosopher->mut_state);
		philosopher->meals_head++;
		pthread_mutex_unlock(&philosopher->mut_state);
	}
	return (NULL);
}

// void	*routine(void *philo)
// {
// 	t_philo	*philosopher;

// 	philosopher = (t_philo *)philo;
// 	if (philosopher->id % 2 == 0)
// 		ft_usleep(philosopher->data->time_eat - 10);
// 	while (1)
// 	{
// 		if (full_philos(philosopher->data))
// 			break ;
// 		if (philosopher->data->dead_flag)
// 			break ;
// 		eat(philosopher);
// 		if (philosopher->data->dead_flag)
// 			break ;
// 		sleep_philo(philosopher);
// 		if (philosopher->data->dead_flag)
// 			break ;
// 		think(philosopher);
// 		if (philosopher->data->dead_flag)
// 			break ;
// 		pthread_mutex_lock(&philosopher->mut_state);
// 		philosopher->meals_head++;
// 		pthread_mutex_unlock(&philosopher->mut_state);
// 	}
// 	return (NULL);
// }

void	eat_sleep_think(t_philo *philosopher)
{
	eat(philosopher);
	sleep_philo(philosopher);
	think(philosopher);
}

void	think(t_philo *philosopher)
{
	if (check_flag(philosopher->data))
	{
		printf("exiting in think\n");
		return ;
	}
	printf("%llu %d is thinking\n",
		get_time() - philosopher->data->start_time, philosopher->id);
}

void	sleep_philo(t_philo *philosopher)
{
	if (check_flag(philosopher->data))
	{
		printf("exiting in sleep\n");
		return ;
	}
	printf("%llu %d is sleeping\n",
		get_time() - philosopher->data->start_time, philosopher->id);
	ft_usleep(philosopher->data->time_sleep, philosopher);
}

void	eat(t_philo *philosopher)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philosopher->left_fork;
	second = philosopher->right_fork;
	if (philosopher->id == philosopher->data->nb_philo - 1)
	{
		first = philosopher->right_fork;
		second = philosopher->left_fork;
	}
	pthread_mutex_lock(first);
	if (check_flag(philosopher->data))
	{
		pthread_mutex_unlock(first);
		return ;
	}
	print_forks(philosopher);
	pthread_mutex_lock(second);
	print_forks(philosopher);
	printf("%llu %d is eating\n",
		get_time() - philosopher->data->start_time, philosopher->id);
	update_last_meal(philosopher);
	ft_usleep(philosopher->data->time_eat, philosopher);
	drop_forks(first, second);
}
