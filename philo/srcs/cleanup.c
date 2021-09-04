#include "philosophers.h"

void	final_cleanup(t_philo *philo, pthread_t *threads)
{
	int i;

	i = 0;
	while (i < philo->data->philosophers)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	free(philo->data->forks);
	free(threads);
	free(philo->data->fork_taken);
	pthread_mutex_destroy(&philo->data->stdout_lock);
	free(philo);
}