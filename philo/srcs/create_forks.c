#include "philosophers.h"

int	create_forks(t_data *data)
{
	int	i;
	pthread_mutex_t	*forks;
	bool *fork_taken;

	forks = malloc(data->philosophers * sizeof(pthread_mutex_t));
	if (!forks)
		return (print_error("Malloc Error :"));
	fork_taken = malloc(data->philosophers * sizeof(bool));
	if (!fork_taken)
	{
		free (forks);
		return (print_error("Malloc Error :"));
	}
	i = 0;
	while (i < data->philosophers)
	{
		fork_taken[i] = false;
		if (pthread_mutex_init(&forks[i], DEFAULT_ATTRIBUTE))
		{
			//destroy mutexed forks?
			free (forks);
			free (fork_taken);
			return (print_error("Mutex Error :"));
		}
		i++;
	}
	data->fork_taken = fork_taken;
	data->forks = forks;
	return (EXIT_SUCCESS);
}