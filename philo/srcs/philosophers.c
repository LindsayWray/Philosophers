#include "philosophers.h"

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_data		data;
	t_philo		*philo;
	int i;

	if (argc != 5 && argc != 6)
		return (print_error("Incorrect amount of arguments\n"));
	if (parsing(argc, argv, &data) != EXIT_SUCCESS)
		return (print_error("Incorrect input\n"));
	if (create_forks(&data) != EXIT_SUCCESS)
		return (print_error("Fork Failure\n"));
	if (mutex_print(&data) != EXIT_SUCCESS)
		return (print_error("Mutex Failure\n"));
	threads = malloc(data.philosophers * sizeof(pthread_t));
	if (!threads)
		return (print_error("Malloc Error: "));
	philo = malloc(data.philosophers * sizeof(t_philo));
	if (!philo)
		return (print_error("Malloc Error: "));
	data.start_time = get_time();
	i = 0;
	while (i < data.philosophers) 
	{
		philo[i].number = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].data = &data;
		philo[i].time_of_death = get_time() + philo->data->time_to_die;
		if (pthread_create(&threads[i], DEFAULT_ATTRIBUTE, create_thread, (void *)&philo[i]) != EXIT_SUCCESS)
			return (print_error("Pthread Failure\n"));
		i++;
	}
	death_monitor(philo, data.philosophers, threads);
	return (0);
}