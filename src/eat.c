/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:12:46 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:12:53 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_eat_time);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->mut_eat_time);
}

void	drop_forks(t_philo *philo)
{
}
void	update_meals_nb(t_philo *philo)
{
}

int	check_forks(t_philo *philo)
{
}

void	eating_time(t_philo *philo)
{
	// ft_usleep(philo->data->time_eat);
}

int	eating(t_philo *philo)
{
	if (check_forks(philo) != 0)
		return (1)
	set_state(philo, EATING);
	update_last_meal(philo);
	eating_time(philo);
	update_meals_nb(philo);
	drop_forks(philo);
	return (0);
}
