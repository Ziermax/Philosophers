/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:45:51 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 17:25:52 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_fork(t_philo *data, pthread_mutex_t *fork, int flag)
{
	long	now;

	pthread_mutex_lock(fork);
	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (!is_death(data) && flag == RIGHT)
		printf("[%ld]\t"BIG"Philo [%p] |%d|: toma 1er tenedor %d [%p]\n"DFT,
			now - data->table.starting_time, data->id, data->index,
			data->index, fork);
	else if (!is_death(data) && flag == LEFT)
		printf("[%ld]\t"BIG"Philo [%p] |%d|: toma 2do tenedor %d [%p]\n"DFT,
			now - data->table.starting_time, data->id, data->index,
			data->index + 1, fork);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}

void	take_forks(t_philo *dt, pthread_mutex_t *rfork, pthread_mutex_t *lfork)
{
	if (dt->index + 1 % 2)
	{
		pick_fork(dt, rfork, RIGHT);
		pick_fork(dt, lfork, LEFT);
	}
	else
	{
		pick_fork(dt, lfork, LEFT);
		pick_fork(dt, rfork, RIGHT);
	}
}

void	eat_meal(t_philo *data)
{
	int		total_meals;
	long	finish_time;
	long	now;

	now = gettime();
	finish_time = data->table.time_to_eat + data->current_time;
	data->current_time = finish_time;
	usleep((finish_time - now) * 1000);
	pthread_mutex_lock(&data->philo_mutex);
	data->fed = 1;
	data->current_meals += 1;
	total_meals = data->current_meals;
	pthread_mutex_unlock(&data->philo_mutex);
	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (!is_death(data))
		printf("[%ld]\t"BIY"Philo [%p] |%d|: ha comido %d vez\n"DFT,
			now - data->table.starting_time, data->id,
			data->index, total_meals);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}

void	leave_forks(t_philo *dt, pthread_mutex_t *rfork, pthread_mutex_t *lfork)
{
	long	now;

	pthread_mutex_unlock(rfork);
	pthread_mutex_unlock(lfork);
	pthread_mutex_lock(&dt->table.main->table_mutex);
	now = gettime();
	if (!is_death(dt))
	{
		printf("[%ld]\t"UBIG"Philo [%p] |%d|: suelta 1er tenedor %d[%p]\n"DFT,
			now - dt->table.starting_time, dt->id, dt->index, dt->index, rfork);
		printf("[%ld]\t"UBIG"Philo [%p] |%d|: suelta 2do tenedor %d[%p]\n"DFT,
			now - dt->table.starting_time, dt->id, dt->index, dt->index, lfork);
	}
	pthread_mutex_unlock(&dt->table.main->table_mutex);
}

void	sleep_and_think(t_philo *data)
{
	long	finish_time;
	long	now;

	finish_time = data->table.time_to_sleep + data->current_time;
	data->current_time = finish_time;
	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (!is_death(data))
		printf("[%ld]\t"BP"Philo [%p] |%d|: durmiendo\n"DFT,
			now - data->table.starting_time, data->id, data->index);
	pthread_mutex_unlock(&data->table.main->table_mutex);
	usleep((finish_time - now) * 1000);
	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (!is_death(data))
		printf("[%ld]\t"IP"Philo [%p] |%d|: despierta\n"DFT,
			now - data->table.starting_time, data->id, data->index);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}
