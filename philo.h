#ifndef PHILO_H
# define PHILO_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/types.h>

# define INPUT_ERROR 0
# define MALLOC_ERROR 1

typedef struct s_philo
{
    int             id;
    int             eat_count;
    int             nb_meals_had;
    struct s_data   *data;
    pthread_t       t1;
    int             status;
    int             eating;
    uint64_t        time_to_die;
    uint64_t        last_eat_time;
    pthread_mutex_t lock;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t mut_state;
    pthread_mutex_t mut_nb_meals_had;
    pthread_mutex_t mut_last_eat_time;
}                   t_philo;

typedef struct s_data
{
    int             philo_num;
    int             meals_nb;
    int             dead;
    int             finished;
    int             nb_full_p;
    bool            keep_iterating;
    t_philo         *philos;
    pthread_t       *tid;
    pthread_t       monit_all_alive;
    pthread_t       monit_all_full;
    uint64_t        death_time;
    uint64_t        eat_time;
    uint64_t        sleep_time;
    uint64_t        start_time;
    pthread_mutex_t mut_eat;
    pthread_mutex_t mut_sleep;
    pthread_mutex_t mut_die;
    pthread_mutex_t mut_start_dine;
    pthread_mutex_t mut_nb_philo;
    pthread_mutex_t mut_iteration;
    pthread_mutex_t write;
    pthread_mutex_t mut_print;
    pthread_mutex_t mut_keep_iter;
    pthread_mutex_t mut_start_time;
    pthread_mutex_t *forks;
}                   t_data;


// utils
int	    ft_atoi(char *str);

// arg check
int     is_input_num(int argc, char **argv);
int     wrong_input_check(int argc, char **argv);
int     check_args(int argc, char **argv);
void    print_instructions(void);

#endif