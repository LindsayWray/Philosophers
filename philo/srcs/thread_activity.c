#include "philosophers.h"

// void	take_left_fork(t_data *data, int number)
// {
// 	pthread_mutex_lock(&data->forks[number - 1]);
// 	print_status(TAKEN_FORK, number, data);
// }

// void	take_right_fork(t_data *data, int number)
// {
// 	if (number == data->philosophers)
// 		pthread_mutex_lock(&data->forks[0]);
// 	else
// 		pthread_mutex_lock(&data->forks[number]);
// 	print_status(TAKEN_FORK, number, data);
// }

bool	try_left(t_data *data, int number)
{
	// if (data->shutdown)
	// 	return (false);
	pthread_mutex_lock(&data->forks[number - 1]);
	if (data->fork_taken[number - 1] == false)
	{
		data->fork_taken[number - 1] = true;
		print_status(TAKEN_FORK, number, data);
		pthread_mutex_unlock(&data->forks[number - 1]);
		return (true);
	}
	pthread_mutex_unlock(&data->forks[number - 1]);
	return (false);
}

bool	try_right(t_data *data, int number)
{
	// if (data->shutdown)
	// 	return (false);
	if (number == data->philosophers)
		number = 0;
	pthread_mutex_lock(&data->forks[number]);
	if (data->fork_taken[number] == false)
	{
		data->fork_taken[number] = true;
		print_status(TAKEN_FORK, number, data);
		pthread_mutex_unlock(&data->forks[number]);
		return (true);
	}
	pthread_mutex_unlock(&data->forks[number]);
	return (false);
}

void	release_forks(t_data *data, int number)
{
	// if (data->shutdown)
	// 	return ;
	pthread_mutex_lock(&data->forks[number - 1]);
	data->fork_taken[number - 1] = false;
	pthread_mutex_unlock(&data->forks[number - 1]);
	if (number == data->philosophers)
		number = 0;
	pthread_mutex_lock(&data->forks[number]);
	data->fork_taken[number] = false;
	pthread_mutex_unlock(&data->forks[number]);
}

int	eating(t_philo *philo, t_data *data, int number)
{
	bool left;
	bool right;

	left = false;
	right = false;
	while (!left || !right)
	{
		if (!left)
			left = try_left(data, number);
		if (!right)
			right = try_right(data, number);
		usleep(100);
		if (data->shutdown)
			return (1);
	}
	philo->time_of_death = get_time() + data->time_to_die;
	print_status(EATING, number, data);
	ft_sleep(data->time_to_eat);
	if (data->meals != -1)
		philo->meals_eaten++;
	release_forks(data, number);
	return (0);
}

// void	eating(t_philo *philo, t_data *data, int number)
// {
// 	if (1)
// 	{
// 		take_right_fork(data, number);
// 		take_left_fork(data, number);
// 	}
// 	else
// 	{
// 		take_left_fork(data, number);
// 		take_right_fork(data, number);
// 	}
// 	philo->time_of_death = get_time() + data->time_to_die;
// 	print_status(EATING, number, data);
// 	ft_sleep(data->time_to_eat);
// 	if (data->meals != -1)
// 		philo->meals_eaten++;
// 	if (number == data->philosophers)
// 		pthread_mutex_unlock(&data->forks[0]);
// 	else
// 		pthread_mutex_unlock(&data->forks[number]);
// 	pthread_mutex_unlock(&data->forks[number - 1]);
// }

void	sleeping(t_data *data, int number)
{
	print_status(SLEEPING, number, data);
	ft_sleep(data->time_to_sleep);
}

void	*create_thread(void *copy)
{
	int				number;
	t_philo			*philo;

	philo = (t_philo *)copy;
	number = philo->number;
	if (number % 2 != 0)
	{
		print_status(THINKING, number, philo->data);
		ft_sleep(philo->data->time_to_eat / 2);
	}
	while (INFINITE_LOOP)
	{
		if (eating(philo, philo->data, number))
			return (NULL);
		sleeping(philo->data, number);
		print_status(THINKING, number, philo->data);
	}
	return (NULL);
}