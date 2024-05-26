/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:11:20 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:11:24 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	thinking(t_philo *philo)
{
	set_state(philo, THINKING);
	if (get_state(philo) == DEAD)
		return (1);
	return (0);
}
