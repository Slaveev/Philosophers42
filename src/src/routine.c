/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:28:48 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/05 17:10:12 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *philo)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)philo;
	if (philosopher->id % 2 == 0)
		usleep(philosopher->data->time_die * 10);
	while (1)
	{
		pthread_mutex_lock(&philosopher->data->anotherone);
		if (philosopher->data->dead_flag)
		{
			pthread_mutex_unlock(&philosopher->data->anotherone);
			return (NULL);
		}
		pthread_mutex_unlock(&philosopher->data->anotherone);
		if (full_philos(philosopher->data))
			break ;
		eat(philosopher);
		sleep_philo(philosopher);
		think(philosopher);
		pthread_mutex_lock(&philosopher->mut_state);
		philosopher->meals_head++;
		pthread_mutex_unlock(&philosopher->mut_state);
	}
	return (NULL);
}

void	think(t_philo *philosopher)
{
	printf("%llu %d is thinking\n",
		get_time() - philosopher->data->start_time, philosopher->id);
	philosopher->state = THINKING;
}

void	sleep_philo(t_philo *philosopher)
{
	printf("%llu %d is sleeping\n",
		get_time() - philosopher->data->start_time, philosopher->id);
	philosopher->state = SLEEPING;
	ft_usleep(philosopher->data->time_sleep);
}

void	drop_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	eat(t_philo *philosopher)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philosopher->id != philosopher->data->nb_philo - 1)
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
	printf("%llu %d has taken a fork\n",
		get_time() - philosopher->data->start_time, philosopher->id);
	pthread_mutex_lock(second);
	printf("%llu %d has taken a fork\n",
		get_time() - philosopher->data->start_time, philosopher->id);
	printf("%llu %d is eating\n",
		get_time() - philosopher->data->start_time, philosopher->id);
	pthread_mutex_lock(&philosopher->mut_state);
	philosopher->state = EATING;
	philosopher->last_time_eat = get_time();
	pthread_mutex_unlock(&philosopher->mut_state);
	ft_usleep(philosopher->data->time_eat);
	drop_forks(first, second);
}
