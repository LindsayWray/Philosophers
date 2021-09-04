/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwray <lwray@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/20 16:59:06 by lwray         #+#    #+#                 */
/*   Updated: 2021/08/20 16:59:08 by lwray         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "types.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

int		parsing(int argc, char **argv, t_data *time);
int		create_forks(t_data *data);
void	*create_thread(void *data);
int		mutex_print(t_data *data);
long	get_time(void);
void	ft_sleep(long ms);
void	print_status(char *status, int number, t_data *data);
void	death_monitor(t_philo *philo, int philosophers, pthread_t *threads);
int		print_error(char *str);
int		error_malloc(pthread_t *threads);
int		error_mutex_print(t_philo *philo, pthread_t *threads);
int		error_create_forks(t_philo *philo, pthread_t *threads, t_data *data);
int		error_startup_threads(t_philo *philo, pthread_t *threads);
void	final_cleanup(t_philo *philo, pthread_t *threads);

#endif