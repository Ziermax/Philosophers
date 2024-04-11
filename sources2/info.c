/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:20:38 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 16:27:47 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_death(t_philo *data)
{
	int	death_info;

	pthread_mutex_lock(&data->philo_mutex);
	death_info = data->death;
	pthread_mutex_unlock(&data->philo_mutex);
	return (death_info);
}

int	is_fed(t_philo *data)
{
	int	fed_info;

	pthread_mutex_lock(&data->philo_mutex);
	fed_info = data->fed;
	pthread_mutex_unlock(&data->philo_mutex);
	return (fed_info);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}
