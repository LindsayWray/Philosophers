/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/04 16:32:16 by lwray         #+#    #+#                 */
/*   Updated: 2021/09/04 16:32:17 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	error_malloc(pthread_t *threads)
{
	free(threads);
	return (print_error("Malloc Error: "));
}

int	error_mutex_print(t_philo *philo, pthread_t *threads)
{
	free(threads);
	free(philo);
	return (print_error("Mutex Failure\n"));
}

int	error_create_forks(t_philo *philo, pthread_t *threads, t_data *data)
{
	free(threads);
	free(philo);
	free (data->forks);
	pthread_mutex_destroy(&data->stdout_lock);
	return (print_error("Fork Failure\n"));
}

int	error_startup_threads(t_philo *philo, pthread_t *threads)
{
	final_cleanup(philo, threads);
	return (print_error("Pthread Failure\n"));
}
