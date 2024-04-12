/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:54:17 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 21:16:03 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes2/philo.h"

void	take_forks(t_philo *data, pthread_mutex_t *forks[2])
{
	long	now;

	pthread_mutex_lock(fork[RIGHT]);
	if (!is_death(data))
		print_action(data, TAKE, index);
	pthread_mutex_lock(fork[LEFT]);
	if (!is_death(data))
		print_action(data, TAKE, index + 1);
}

void	eat_meal(t_philo *data)
{
	long	now;
	long	finish_time;

	if (!is_death(data))
		print_action(data, EAT, -1);
	now = gettime();
	finish_time = data->current_time + data->table.time_to_eat;
	usleep((finish_time - now) * 1000);
}

void	leave_forks(t_philo *data, pthread_mutex_t *forks[2])
{
	long	now;

	pthread_mutex_unlock(fork[RIGHT]);
	pthread_mutex_unlock(fork[LEFT]);
	if (!is_death(data))
	{
		print_action(data, LEAVE, index);
		print_action(data, LEAVE, index + 1);
	}
}

void	sleep_and_think(t_philo *data)
{
	long	now;

	if (!is_death(data))
		print_action(data, SLEEP, -1);
	now = gettime();
	finish_time = data->current_time + data->table.time_to_sleep;
	usleep((finish_time - now) * 1000);
	if (!is_death(data))
		print_action(data, THINK, -1);
}
