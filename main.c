#include "../includes/philo.h"

int init_malloc(t_data *data)
{
    data->philos = malloc(sizeof(t_philo) * data->philo_num);
    if (data->philos == NULL)
        return (MALLOC_ERROR);
    data->forks = malloc(sizeof(t_philo) * data->philo_num);
    if (data->forks == NULL)
        return (free(data->philos), MALLOC_ERROR);
    data->tid = malloc(sizeof(t_philo) * data->philo_num);
    if (data->tid == NULL)
    {
        free(data->philos);
        free(data->forks);
        return (MALLOC_ERROR);
    }
    return (0);
}

int init_data(t_data *data,int argc, char **argv)
{
    data->philo_num = ft_atoi(argv[1]);
    data->death_time = (u_int64_t) ft_atoi(argv[2]);
    data->eat_time = (u_int64_t) ft_atoi(argv[3]);
    data->sleep_time = (u_int64_t) ft_atoi(argv[4]);
    data->meals_nb = -1;
    if (argc == 6)
        data->meals_nb = ft_atoi(argv[5]);
    pthread_mutex_init(&data->mut_eat, NULL);
    pthread_mutex_init(&data->mut_die, NULL);
    pthread_mutex_init(&data->mut_sleep, NULL);
    pthread_mutex_init(&data->mut_nb_philo, NULL);
    pthread_mutex_init(&data->write, NULL);
    pthread_mutex_init(&data->mut_start_dine, NULL);
    pthread_mutex_init(&data->mut_iteration, NULL);
    return (init_malloc(data));
}

int init_philo(t_data *data)
{
    t_philo  *philos;
    int         i;

    i = 0;
    philos = data->philos;
    while (i < data->philo_num)
    {
        philos[i].data = data;
        philos[i].id = i + 1;
        philos[i].eat_count = 0;
        philos[i].status = 0;
        philos[i].eating = 0;
        pthread_mutex_init(&philos[i].mut_state, NULL);
        pthread_mutex_init(&philos[i].mut_nb_meals_had, NULL);
        pthread_mutex_init(&philos[i].mut_last_eat_time, NULL);
        i++;
    }
    return (0);
}

int init_forks(t_data *data)
{
    int     i;
    t_philo *philos;

    philos = data->philos;
    i = 0;
    while (i < data->philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    i = 0;
    philos[i].left_fork = &data->forks[0];
    philos[i].right_fork = &data->forks[data->philo_num - 1];
    while (i < data->philo_num)
    {
        philos[i].left_fork = &data->forks[i];
        philos[i].right_fork = &data->forks[i - 1];
    }
    return (0);
}

int start(int argc, char **argv)
{
    t_data  data;

    if (init_data(&data, argc, argv) != 0)
        return (MALLOC_ERROR);
    init_philo(&data);
    init_forks(&data);
}

int main(int argc, char **argv)
{
    t_data   data;

    if (check_args(argc, argv) != 1)
    {
        print_instructions();
        return (INPUT_ERROR);
    }
}