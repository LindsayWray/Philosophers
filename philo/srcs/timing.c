/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timing.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/04 16:32:40 by lwray         #+#    #+#                 */
/*   Updated: 2021/09/04 16:32:43 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time(void)
{
	struct timeval	time_values;
	long			time;

	gettimeofday(&time_values, NULL);
	time = ((time_values.tv_sec * 1000) + (time_values.tv_usec / 1000));
	return (time);
}

void	ft_sleep(long ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}
