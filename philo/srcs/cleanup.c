/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/04 16:32:05 by lwray         #+#    #+#                 */
/*   Updated: 2021/09/04 16:32:11 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	final_cleanup(t_philo *philo, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < philo->data->philosophers)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	free(philo->data->forks);
	free(philo->data->fork_taken);
	free(threads);
	pthread_mutex_destroy(&philo->data->stdout_lock);
	free(philo);
}
