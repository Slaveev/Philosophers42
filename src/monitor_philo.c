/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:22:06 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:55:41 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	philo_ate(t_data *data, t_philo *philo)
{
	bool	ate;

	ate = false;
	if (get_meals_count(philo) >= data->meals_had)
		ate = true;
	return (ate);
}

bool	philo_dead(t_philo *philo)
{
	bool	dead;
	t_data	*data;

	data = philo->data;
	dead = false;
	if (get_time() - get_last_meal_time(philo) > get_die_time(data))
	{
		if (get_state(philo) != EATING)
		{
			set_state(philo, DEAD);
			dead = true;
		}
	}
	return (dead);
}

void	*check_all_alive(void *data)
{
	
}

void	*check_all_eaten(void *data)
{
}

void	stop_philos(t_data *data)
{
}
