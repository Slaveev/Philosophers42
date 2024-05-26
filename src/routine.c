/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:14:57 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:14:59 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine(t_philo *philo_ptr)
{
	t_philo	philo;

	philo = (t_philo *) philo_ptr;
	update_last_meal(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_eat);
	while (get_state(philo) != DEAD)
	{
		if
	}
}
