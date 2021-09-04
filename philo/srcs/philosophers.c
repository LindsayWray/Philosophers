/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/04 16:33:01 by lwray         #+#    #+#                 */
/*   Updated: 2021/09/04 16:33:03 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	startup_threads(t_philo *philo, t_data *data, pthread_t	*threads)
{
	int	i;

	i = 0;
	while (i < data->philosophers)
	{
		philo[i].number = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].data = data;
		philo[i].time_of_death = get_time() + philo->data->time_to_die;
		if (pthread_create(&threads[i], DEFAULT_ATTRIBUTE, create_thread,
				(void *)&philo[i]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_data		data;
	t_philo		*philo;

	if (argc != 5 && argc != 6)
		return (print_error("Incorrect amount of arguments\n"));
	if (parsing(argc, argv, &data) != EXIT_SUCCESS)
		return (print_error("Incorrect input\n"));
	threads = malloc(data.philosophers * sizeof(pthread_t));
	if (!threads)
		return (print_error("Malloc Error: "));
	philo = malloc(data.philosophers * sizeof(t_philo));
	if (!philo)
		return (error_malloc(threads));
	if (mutex_print(&data) != EXIT_SUCCESS)
		return (error_mutex_print(philo, threads));
	if (create_forks(&data) != EXIT_SUCCESS)
		return (error_create_forks(philo, threads, &data));
	data.start_time = get_time();
	if (startup_threads(philo, &data, threads) != EXIT_SUCCESS)
		return (error_startup_threads(philo, threads));
	death_monitor(philo, data.philosophers, threads);
	return (0);
}
