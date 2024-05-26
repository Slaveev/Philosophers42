/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:10:59 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:11:07 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	sleeping(t_philo *philo)
{
	set_state(philo, SLEEPING);
	if (get_state(philo) == DEAD)
		return (1);
	ft_usleep(get_sleep_time(philo->data));
	return (0);
}
