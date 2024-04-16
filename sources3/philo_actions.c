/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:54:17 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 15:45:14 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes2/philo.h"

void	take_forks(t_philo *data, pthread_mutex_t *forks[2])
{
	pthread_mutex_lock(forks[RIGHT]);
	if (!is_death(data))
		print_action(data, TAKE, data->index);
	pthread_mutex_lock(forks[LEFT]);
	if (!is_death(data))
		print_action(data, TAKE, data->index + 1);
}

void	eat_meal(t_philo *data)
{
	long	now;
	int		diff;

	data->current_time += data->table.time_to_eat;
	now = gettime();
	diff = data->current_time - now;
	while (diff <= 0)
	{
		diff += data->table.time_to_eat;
		data->current_time += data->table.time_to_eat;
	}
	if (!is_death(data))
		print_action(data, EAT, diff);
	printf("Philo %d before usleep eat [%ld]\n", data->index,
		gettime() - data->table.starting_time);
	if (!is_death(data))
		usleep(diff);
	printf("Philo %d after usleep eat [%ld]\n", data->index,
		gettime() - data->table.starting_time);
	pthread_mutex_lock(&data->philo_mutex);
	data->fed = 1;
	data->meal_count += 1;
	printf("Philo %d mealcount: %d [%ld]\n",data->index,
		data->meal_count, gettime() - data->table.starting_time);
	pthread_mutex_unlock(&data->philo_mutex);
}

void	leave_forks(t_philo *data, pthread_mutex_t *forks[2])
{
	pthread_mutex_unlock(forks[RIGHT]);
	if (!is_death(data))
		print_action(data, LEAVE, data->index);
	pthread_mutex_unlock(forks[LEFT]);
	if (!is_death(data))
		print_action(data, LEAVE, data->index + 1);
}

void	sleep_and_think(t_philo *data)
{
	long	now;
	int		diff;

	data->current_time += data->table.time_to_sleep;
	now = gettime();
	diff = data->current_time - now;
	while (diff <= 0)
	{
		data->current_time += data->table.time_to_sleep;
		diff += data->table.time_to_sleep;
	}
	if (!is_death(data))
		print_action(data, SLEEP, diff);
	printf("Philo %d before usleep sleep [%ld]\n", data->index,
		gettime() - data->table.starting_time);
	if (!is_death(data))
		usleep(diff);
	printf("Philo %d after usleep sleep [%ld]\n", data->index,
		gettime() - data->table.starting_time);
	if (!is_death(data))
		print_action(data, THINK, -1);
}
