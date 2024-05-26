/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:11:51 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:11:53 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_state	set_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->mut_state);
	philo->state = state;
	pthread_mutex_unlock(&philo->mut_state);
	return (state);
}
