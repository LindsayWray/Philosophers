#include "philosophers.h"


void	shutdown_threads(pthread_t *threads, int philosophers)
{
	int i;

	i = 0;
	while (i < philosophers)
	{
		pthread_detach(threads[i]);
		i++;
	}
}

int		monitor_meals(t_philo *philo, int philosophers, pthread_t *threads)
{
	int i;

	i = 0;
	while (i < philosophers)
	{
		if (philo[i].meals_eaten < philo->data->meals)
			return (0);
		i++;
	}
	philo->data->shutdown = true;
	usleep(500);
	shutdown_threads(threads, philosophers);
	final_cleanup(philo, threads);
	return (1);
}

void 	death_monitor(t_philo *philo, int philosophers, pthread_t *threads)
{
	long current_time;
	int	i;

	while (INFINITE_LOOP)
	{
		current_time = get_time();
		i = 0;
		while (i < philosophers)
		{
			if (philo[i].time_of_death < current_time)
			{
				print_status(DIED, (i + 1), philo[i].data);
				philo->data->shutdown = true;
				usleep(500);
				shutdown_threads(threads, philosophers);
				final_cleanup(philo, threads);
				return ;
			}
			if (philo->data->meals != -1)
				if (monitor_meals(philo, philosophers, threads))
					return ;
			i++;
		}
		usleep(500);
	}
}