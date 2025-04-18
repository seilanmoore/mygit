/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:34:18 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/10 19:15:09 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <bits/pthreadtypes.h>

bool	all_threads_running(t_mutex *mutex, int *n_thread, int n_philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*n_thread == n_philo)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	all_philo_full(t_mutex *mutex, int *n_full_philo, int n_philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*n_full_philo == n_philo)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	increase_full_philo(t_mutex *mutex, int *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

void	increase_running_threads(t_mutex *mutex, int *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

void	sync_threads(t_data *data)
{
	while (!get_bool(&(data->data_mutex), &(data->threads_ready)))
		;
}
