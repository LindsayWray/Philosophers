/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_activity.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/04 16:33:06 by lwray         #+#    #+#                 */
/*   Updated: 2021/09/04 16:33:08 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	try_left(t_data *data, int number)
{
	if (data->shutdown)
		return (false);
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

static bool	try_right(t_data *data, int number)
{
	int	fork_index;

	if (data->shutdown)
		return (false);
	fork_index = number;
	if (number == data->philosophers)
		fork_index = 0;
	pthread_mutex_lock(&data->forks[fork_index]);
	if (data->fork_taken[fork_index] == false)
	{
		data->fork_taken[fork_index] = true;
		print_status(TAKEN_FORK, number, data);
		pthread_mutex_unlock(&data->forks[fork_index]);
		return (true);
	}
	pthread_mutex_unlock(&data->forks[fork_index]);
	return (false);
}

static void	release_forks(t_data *data, int number)
{
	if (data->shutdown)
		return ;
	pthread_mutex_lock(&data->forks[number - 1]);
	data->fork_taken[number - 1] = false;
	pthread_mutex_unlock(&data->forks[number - 1]);
	if (number == data->philosophers)
		number = 0;
	pthread_mutex_lock(&data->forks[number]);
	data->fork_taken[number] = false;
	pthread_mutex_unlock(&data->forks[number]);
}

static int	eating(t_philo *philo, t_data *data, int number)
{
	bool	left;
	bool	right;

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
		print_status(SLEEPING, number, philo->data);
		ft_sleep(philo->data->time_to_sleep);
		print_status(THINKING, number, philo->data);
	}
	return (NULL);
}
