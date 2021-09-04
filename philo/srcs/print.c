#include "philosophers.h"

int	print_error(char *str)
{
	while (*str != '\0')
	{
		write (STDERR_FILENO, str, 1);
		str++;
	}
	return (EXIT_FAILURE);
}

int	mutex_print(t_data *data)
{
	pthread_mutex_t stdout_lock;

	if (pthread_mutex_init(&stdout_lock, DEFAULT_ATTRIBUTE))
	{
		print_error("Error :");
		return (EXIT_FAILURE);
	}
	data->stdout_lock = stdout_lock;
	return (EXIT_SUCCESS);
}

int	ft_strequal(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	return (0);
}

void	print_status(char *status, int number, t_data *data)
{
	static bool death_occured = false;

	pthread_mutex_lock(&data->stdout_lock);
	if (!death_occured)
	{
		if (ft_strequal(status, DIED))
			death_occured = true;
		printf("%5ld: ", (get_time() - data->start_time));
		printf("philosopher %d %s\n", number, status);
	}
	pthread_mutex_unlock(&data->stdout_lock);
}
