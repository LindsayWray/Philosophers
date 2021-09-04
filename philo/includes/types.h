/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/20 16:59:06 by lwray         #+#    #+#                 */
/*   Updated: 2021/08/20 16:59:08 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include <stdbool.h>
# define NO_MINIMUM_MEALS -1
# define DEFAULT_ATTRIBUTE NULL
# define INFINITE_LOOP 1
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define TAKEN_FORK "has taken a fork"
# define DIED "has tragically died. RIP"

typedef struct s_data
{
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	long			start_time;
	bool			*fork_taken;
	bool			shutdown;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stdout_lock;
}	t_data;

typedef struct s_philo
{
	int		number;
	long	time_of_death;
	int		meals_eaten;
	t_data	*data;
}		t_philo;

#endif