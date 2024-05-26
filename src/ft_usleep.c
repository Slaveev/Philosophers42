/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:14:08 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 15:07:53 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_usleep(size_t milisecs)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < milisecs)
	{
		usleep(500);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "getttimeofday error\n", 20);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
