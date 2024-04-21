/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:00:56 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/21 14:54:59 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_take(t_philo *philo, int fork_id)
{
	long	now;

	pthread_mutex_lock(&philo->table.main->table_mutex);
	now = gettime();
	if (!is_death(philo))
		printf("[%ld]\t"BIG"Philo %d took fork %d\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index, fork_id);
	pthread_mutex_unlock(&philo->table.main->table_mutex);
}

void	print_eat(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->table.main->table_mutex);
	now = gettime();
	if (!is_death(philo))
		printf("[%ld]\t"BIY"Philo %d is eating\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index);
	pthread_mutex_unlock(&philo->table.main->table_mutex);
}

void	print_leave(t_philo *philo, int fork_id)
{
	long	now;

	pthread_mutex_lock(&philo->table.main->table_mutex);
	now = gettime();
	if (!is_death(philo))
		printf("[%ld]\t"UBIG"Philo %d dropped fork %d\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index, fork_id);
	pthread_mutex_unlock(&philo->table.main->table_mutex);
}

void	print_sleep(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->table.main->table_mutex);
	now = gettime();
	if (!is_death(philo))
		printf("[%ld]\t"BP"Philo %d is sleeping\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index);
	pthread_mutex_unlock(&philo->table.main->table_mutex);
}

void	print_think(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->table.main->table_mutex);
	now = gettime();
	if (!is_death(philo))
		printf("[%ld]\t"IP"Philo %d is thinking\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index);
	pthread_mutex_unlock(&philo->table.main->table_mutex);
}
