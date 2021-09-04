/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/04 16:32:23 by lwray         #+#    #+#                 */
/*   Updated: 2021/09/04 16:32:26 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	assign_input(int *input, int argc, t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = input[0];
	data->time_to_die = input[1];
	data->time_to_eat = input[2];
	data->time_to_sleep = input[3];
	if (argc == 6)
		data->meals = input[4];
	else
		data->meals = NO_MINIMUM_MEALS;
	data->shutdown = false;
}

static int	ft_atoi(char *str)
{
	long	number;

	if (!*str)
		return (-1);
	if (*str == '-')
	{
		print_error("Negative input is invalid: ");
		return (-1);
	}
	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
		if (number > 2147483647)
			return (-1);
	}
	if (*str != '\0')
		return (-1);
	return (number);
}

int	parsing(int argc, char **argv, t_data *data)
{
	int		input[5];
	int		i;

	argv++;
	i = 0;
	while (i < (argc - 1))
	{
		input[i] = ft_atoi(argv[i]);
		if (input[i] == -1)
			return (EXIT_FAILURE);
		i++;
	}
	assign_input(input, argc, data);
	if (data->philosophers < 1)
	{
		print_error("Must be at least one philosopher: ");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
