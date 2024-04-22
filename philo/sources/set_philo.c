/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:26:27 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/22 21:16:27 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->death = 1;
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	set_fed(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = gettime();
	philo->meal_count += 1;
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	precise_usleep(long time_to_wait)
{
	long	finish_time;

	finish_time = gettime() + time_to_wait;
	while (gettime() <= finish_time)
		usleep(500);
}

void	dinner(t_oracle *oracle)
{
	int			index;
	pthread_t	*philo_thread;
	t_philo		*philo;

	index = 0;
	while (index < oracle->table.amount_philos)
	{
		philo_thread = &oracle->table.philo_threads[index];
		philo = &oracle->philos[index];
		pthread_create(philo_thread, NULL, philo_routine, philo);
		index++;
	}
}
