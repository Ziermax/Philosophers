/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:37:15 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 20:47:22 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[RIGHT]);
	if (!is_death(philo))
		print_action(philo, TAKE, data->index);
	pthread_mutex_lock(philo->fork[LEFT]);
	if (!is_death(philo))
		print_action(philo, TAKE, data->index + 1);
}

void	eat_meal(t_philo *philo)
{
	if (!is_death(philo))
		print_action(philo, EAT, 0);
	if (!is_death(philo))
		usleep(philo->table.time_to_eat);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->fed = 1;
	philo->meal_count += 1;
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork[RIGHT]);
	if (!is_death(philo))
		print_action(philo, LEAVE, data->index);
	pthread_mutex_unlock(philo->fork[LEFT]);
	if (!is_death(philo))
		print_action(philo, LEAVE, data->index + 1);
}

void	sleep_and_think(t_philo *philo)
{
	if (!is_death(philo))
		print_action(philo, SLEEP, 0);
	if (!is_death(philo))
		usleep(philo->table.time_to_sleep);
	if (!is_death(philo))
		print_action(philo, THINK, 0);
}
