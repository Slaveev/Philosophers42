/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:55:20 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/09 18:07:57 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>

# define WRONG_INPUT 1
# define MALLOC_ERROR 2

# define FORKS "has taken a fork"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define THINK "is thinking"
# define DIE "has died"

typedef enum s_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	WAITING = 3,
	DEAD = 4
}				t_state;

struct	s_philo;

typedef struct s_data
{
	int					nb_philo;
	int					nb_full_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_meals;
	int					dead_flag;
	bool				keep_iteration;
	bool				alive;
	unsigned long long	start_time;
	struct s_philo		*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead;
	pthread_mutex_t		anotherone;
	pthread_mutex_t		anotherone1;
	pthread_mutex_t		anotherone2;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					meals_head;
	t_data				*data;
	t_state				state;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		mut_meals_had;
	pthread_mutex_t		mut_last_time_eat;
	pthread_mutex_t		mut_state;
	unsigned long long	last_time_eat;
	pthread_t			thread;
	pthread_mutex_t		mutex_dead_flag;
}						t_philo;

// cleanup
void				cleanup_one(t_data *data);
void				cleanup(t_data *data);

// utils
int					ft_atoi(const char *str);
unsigned long long	get_time(void);
int					ft_usleep(unsigned long time, t_philo *philo);
void				one_philo(t_data *data);
int					full_philos(t_data *data);
void				eat_sleep_think(t_philo *philosopher);
int					check_flag(t_data *philo_data);
void				drop_forks(pthread_mutex_t *first_fork,
						pthread_mutex_t *second_fork);
void				print_forks(t_philo *philosopher);
void				update_last_meal(t_philo *philosopher);

// init
t_data				*init_data(int argc, char **argv);
t_philo				*init_philos(t_data *data);

// monitor
void				*monitoring(void *data);

// routine
void				*routine(void *philo);
void				sleep_philo(t_philo *philosopher);
void				think(t_philo *philosopher);
void				drop_forks(pthread_mutex_t *first_fork,
						pthread_mutex_t *second_fork);
void				eat(t_philo *philosopher);

#endif
