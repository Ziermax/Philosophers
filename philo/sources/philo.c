/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:29:50 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/22 21:47:09 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[RIGHT]);
	print_take(philo, philo->fork_id[RIGHT]);
	pthread_mutex_lock(philo->fork[LEFT]);
	print_take(philo, philo->fork_id[LEFT]);
}

static void	eat_meal(t_philo *philo)
{
	print_eat(philo);
	if (!is_death(philo))
		precise_usleep(philo->table.time_to_eat);
}

static void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork[RIGHT]);
	print_leave(philo, philo->fork_id[RIGHT]);
	set_fed(philo);
	pthread_mutex_unlock(philo->fork[LEFT]);
	print_leave(philo, philo->fork_id[LEFT]);
}

static void	sleep_and_think(t_philo *philo)
{
	print_sleep(philo);
	if (!is_death(philo))
		precise_usleep(philo->table.time_to_sleep);
	print_think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->table.amount_philos == 1)
	{
		pthread_mutex_lock(philo->fork[RIGHT]);
		print_take(philo, philo->fork_id[RIGHT]);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		return (NULL);
	}
	if (philo->index % 2)
		usleep(philo->table.time_to_eat / 2);
	while (!is_death(philo))
	{
		take_forks(philo);
		eat_meal(philo);
		leave_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
