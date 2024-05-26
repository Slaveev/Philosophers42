/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:13:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 15:39:47 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	check_forks(t_philo *philo)
{
	if (take_left_fork(philo) != 0)
		return (1);
	if (take_right_fork(philo) != 0)
	{
		drop_forks(philo);
		return (2);
	}
	return (0);
}

int	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	return (0);
}

int	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	return (0);
}
