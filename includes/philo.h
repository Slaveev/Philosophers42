/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:55:20 by dslaveev          #+#    #+#             */
/*   Updated: 2024/05/26 14:53:02 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

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

struct	s_data;

typedef struct s_philo
{
	pthread_t			t1;
	int					id;
	int					meals_had;
	struct s_data		*data;
	t_state				state;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		mut_meals_had;
	pthread_mutex_t		mut_last_time_eat;
	pthread_mutex_t		mut_state;
	u_int64_t			last_time_eat;
}						t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_full_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meals;
	bool			keep_iteration;
	u_int64_t		start_time;
	pthread_mutex_t	mut_eat_time;
	pthread_mutex_t	mut_die_time;
	pthread_mutex_t	mut_sleep_time;
	pthread_mutex_t	mut_nb_philo;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_keep_iteration;
	pthread_t		all_alive;
	pthread_t		all_eaten;
	pthread_t		*ths
	t_philo			*philos;
}					t_data;

// arguments check
int			ft_atoi(const char *str);
int			is_input_num(int argc, char **argv);
int			wrong_input_check(int argc, char **argv);
int			check_args(int argc, char **argv)
void		print_instructions(void);

// get data
int			get_philos(t_data *data);
t_state		get_state(t_philo *philo);
uint16_t	get_sleep_time(t_data *data);
uint64_t	get_eat_time(t_data *data);
uint64_t	get_die_time(t_data *data);

// set data
t_state		set_state(t_philo *philo, t_state state);

// init data
int			init_malloc(t_data *data);
int			init_data(t_data *data, int argc, char **argv);
int			init_philo(t_data *data);
int			init_forks(t_data *data);

// eat utils
void		update_last_meal(t_philo *philo);
void		drop_forks(t_philo *philo);
void		update_meals_nb(t_philo *philo);
int			check_forks(t_philo *philo);
void		eating_time(t_philo *philo);
int			eating(t_philo *philo);

// thinking
int			thinking(t_philo *philo);

// sleeping
int			sleeping(t_philo *philo);

// threads
int			join_threads(t_data *data);
int			start_threads(t_data *data);

// monitor
void		*check_all_alive(void *data);
void		*check_all_eaten(void *data);
bool		philo_ate(t_philo *philo);
bool		philo_dead(t_philo *philo);
void		stop_philos(t_data *data);

// routine
void		routine(t_philo *philo_ptr);

// ft_usleep
void		ft_usleep(uint64_t time);
u_int64_t	get_time(void);

#endif
