/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_forks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/04 16:32:47 by lwray         #+#    #+#                 */
/*   Updated: 2021/09/04 16:32:48 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	create_forks(t_data *data)
{
	int	i;

	data->forks = malloc(data->philosophers * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (print_error("Malloc Error :"));
	data->fork_taken = malloc(data->philosophers * sizeof(bool));
	if (!data->fork_taken)
		return (print_error("Malloc Error :"));
	i = 0;
	while (i < data->philosophers)
	{
		data->fork_taken[i] = false;
		if (pthread_mutex_init(&data->forks[i], DEFAULT_ATTRIBUTE))
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&data->forks[i]);
			}
			free (data->fork_taken);
			return (print_error("Mutex Error :"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
