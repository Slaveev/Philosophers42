/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:26:03 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/07 16:26:05 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	drop_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	update_last_meal(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->mut_last_time_eat);
	philosopher->last_time_eat = get_time();
	pthread_mutex_unlock(&philosopher->mut_last_time_eat);
}

void	print_forks(t_philo *philosopher)
{
	printf("%llu %d has taken a fork\n",
		get_time() - philosopher->data->start_time, philosopher->id);
}
