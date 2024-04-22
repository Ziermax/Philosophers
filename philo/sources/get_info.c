/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:25:06 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/22 22:41:18 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_death(t_philo *philo)
{
	int	death_info;

	pthread_mutex_lock(&philo->philo_mutex);
	death_info = philo->death;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (death_info);
}

int	is_fed(t_philo *philo)
{
	int	fed_info;

	pthread_mutex_lock(&philo->philo_mutex);
	fed_info = philo->last_meal >= gettime() - philo->table.time_to_die;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (fed_info);
}

int	is_satiated(t_philo *philo)
{
	int	satiated_info;

	pthread_mutex_lock(&philo->philo_mutex);
	satiated_info = philo->meal_count >= philo->table.minimun_meals;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (satiated_info);
}

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_sec %= 31556925;
	return (time.tv_sec * 1e6 + time.tv_usec);
}
