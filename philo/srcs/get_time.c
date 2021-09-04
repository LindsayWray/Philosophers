#include "philosophers.h"

long	get_time()
{
	struct timeval time_values;
	long time;

	gettimeofday(&time_values, NULL);
	time = ((time_values.tv_sec * 1000) + (time_values.tv_usec / 1000));
	return (time);
}

void    ft_sleep(long ms)
{
    long    start;

    start = get_time();
    while ((get_time() - start) < ms)
        usleep(100);
}