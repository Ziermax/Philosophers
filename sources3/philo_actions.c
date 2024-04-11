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

//	take right
	pthread_mutex_lock(fork[RIGHT]);
	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime()
	if (!is_death(data))
			printf("[%p]\tPhilo %d took %d fork\n",
				data->current_time - now, data->index, data->index);
	pthread_mutex_unlock(&data->table.main->table_mutex);
//	take left
	pthread_mutex_lock(fork[LEFT]);
	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (!is_death(data))
			printf("[%p]\tPhilo %d took %d fork\n",
				data->current_time - now, data->index, data->index + 1);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}

void	eat_meal(t_philo *data)
{
	long	now;
	long	finish_time;

	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (!is_death(data))
			printf("[%p]\tPhilo %d is eating\n",
				data->current_time - now, data->index);
	pthread_mutex_unlock(&data->table.main->table_mutex);
	finish_time = data->current_time + data->table.time_to_eat;
	usleep((finish_time - now) * 1000);
}

void	leave_forks(t_philo *data, pthread_mutex_t *forks[2])
{
	long	now;

	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (!is_death(data))
			printf("[%p]\tPhilo %d is eating\n",
				data->current_time - now, data->index);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}

void	sleep_and_think(t_philo *data)
{
	long	now;

	usleep(() * 1000);
	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (!is_death(data))
			printf("[%p]\tPhilo %d is eating\n",
				data->current_time - now, data->index);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}
