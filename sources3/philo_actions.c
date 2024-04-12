/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:54:17 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/12 17:26:51 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes2/philo.h"

void	take_forks(t_philo *data, pthread_mutex_t *forks[2])
{
	pthread_mutex_lock(forks[RIGHT]);
	printf("[%p] locking: [%p]\n", data->id, forks[RIGHT]);
	if (!is_death(data))
		print_action(data, TAKE, data->index);
	pthread_mutex_lock(forks[LEFT]);
	printf("[%p] locking: [%p]\n", data->id, forks[LEFT]);
	if (!is_death(data))
		print_action(data, TAKE, data->index + 1);
}

void	eat_meal(t_philo *data)
{
	long	now;
	long	finish_time;

	now = gettime();
	finish_time = data->current_time + data->table.time_to_eat;
	printf("Eating for %ld micros | time: %ld | eat: %ld | now %ld\n",
		finish_time - now, data->current_time,
		(long)data->table.time_to_eat, now);
	if (!is_death(data))
		print_action(data, EAT, finish_time - now);
	usleep(finish_time - now);
	pthread_mutex_lock(&data->philo_mutex);
	data->fed = 1;
	data->meal_count += 1;
	pthread_mutex_unlock(&data->philo_mutex);
	data->current_time = finish_time;
}

void	leave_forks(t_philo *data, pthread_mutex_t *forks[2])
{
	pthread_mutex_unlock(forks[RIGHT]);
	printf("[%p] unlockng: [%p]\n", data->id, forks[RIGHT]);
	pthread_mutex_unlock(forks[LEFT]);
	printf("[%p] unlockng: [%p]\n", data->id, forks[LEFT]);
	if (!is_death(data))
	{
		print_action(data, LEAVE, data->index);
		print_action(data, LEAVE, data->index + 1);
	}
}

void	sleep_and_think(t_philo *data)
{
	long	now;
	long	finish_time;

	now = gettime();
	finish_time = data->current_time + data->table.time_to_sleep;
	printf("Sleeping for %ld micros\n", finish_time - now);
	if (!is_death(data))
		print_action(data, SLEEP, finish_time - now);
	usleep(finish_time - now);
	if (!is_death(data))
		print_action(data, THINK, -1);
	data->current_time = finish_time;
}
