#include "../includes/philo.h"

int	ft_atoi(char *str)
{
	int		count;
	long	result;
	int		sign;

	count = 0;
	result = 0;
	sign = 1;
	while (str[count] == '\r' || str[count] == '\t' || str[count] == ' '
		|| str[count] == '\f' || str[count] == '\v' || str[count] == '\n')
		count++;
	if (str[count] == '-')
	{
		sign = -1;
		count++;
	}
	else if (str[count] == '+')
		count++;
	if (!(str[count] >= '0' && str[count] <= '9'))
		return (0);
	while (str[count] >= '0' && str[count] <= '9')
		result = result * 10 + (str[count++] - '0');
	return (result * sign);
}

int is_input_num(int argc, char **argv)
{
    int i = 0;
    int j = 0;

    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (INPUT_ERROR);
            j++;
        }
        i++;
    }
    return (1);
}

int wrong_input_check(int argc, char **argv)
{
    int i;

    i = 1;
    if (argc == 6 && ft_atoi(argv[5]) <= 0)
        return (INPUT_ERROR);
    if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
        return (INPUT_ERROR);
    if (ft_atoi(argv[2]) < 60)
        return (INPUT_ERROR);
    if (ft_atoi(argv[3]) < 60)
        return (INPUT_ERROR);
    if (ft_atoi(argv[4]) < 60)
        return (INPUT_ERROR);
    return (1);
}

int check_args(int argc, char **argv)
{
    if (argc < 5)
       return (INPUT_ERROR);
    if (argc > 6)
        return (INPUT_ERROR);
    if (is_input_num(argc, argv) != 1)
        return (INPUT_ERROR);
    if (wrong_input_check(argc, argv) != 1)
        return (INPUT_ERROR);
    return (1);
}

void    print_instructions(void)
{
    printf("\t\tWRONG INPUT\n\n");
    printf("./philo nb_philos time_to_die ");
    printf("time_to_eat time_to_sleep ");
    printf("number_of_times_philos_must_eat  ");
    printf("{optional arg}\n");
}