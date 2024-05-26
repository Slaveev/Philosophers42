/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:53:57 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:16:30 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv) != 0)
		return (MALLOC_ERROR);
	init_philo(&data);
	init_forks(&data);
	start_threads(&data);
	join_threads(&data);
	free_data(&data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 1)
	{
		print_instructions();
		return (INPUT_ERROR);
	}
	start(argc, argv);
	return (0);
}
