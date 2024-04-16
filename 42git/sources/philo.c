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

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[RIGHT]);
	if (!is_death(philo))
		print_action(philo, TAKE, data->index);
	pthread_mutex_lock(philo->fork[LEFT]);
	if (!is_death(philo))
		print_action(philo, TAKE, data->index + 1);
}

static void	eat_meal(t_philo *philo)
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

static void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork[RIGHT]);
	if (!is_death(philo))
		print_action(philo, LEAVE, data->index);
	pthread_mutex_unlock(philo->fork[LEFT]);
	if (!is_death(philo))
		print_action(philo, LEAVE, data->index + 1);
}

static void	sleep_and_think(t_philo *philo)
{
	if (!is_death(philo))
		print_action(philo, SLEEP, 0);
	if (!is_death(philo))
		usleep(philo->table.time_to_sleep);
	if (!is_death(philo))
		print_action(philo, THINK, 0);
}

void	*dinner_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if ((philo->index + 1) % 2)
		usleep(500);
	while (!is_death(philo))
	{
		take_forks(philo);
		eat_meal(philo);
		leave_forks(philo);
		sleep_and_think(philo);
	}
}
