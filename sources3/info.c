/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:20:38 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/12 17:32:39 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes2/philo.h"

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

int	is_death(t_philo *data)
{
	int	death_info;

	pthread_mutex_lock(&data->philo_mutex);
	death_info = data->death;
	pthread_mutex_unlock(&data->philo_mutex);
	return (death_info);
}

int	is_satiated(t_philo *data)
{
	int	satiated_info;

	pthread_mutex_lock(&data->philo_mutex);
	satiated_info = data->meal_count >= data->table.minimum_meals;
	pthread_mutex_unlock(&data->philo_mutex);
	return (satiated_info);
}

void	print_action(t_philo *data, int flag, long aux)
{
	long	now;

	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (flag == TAKE && aux != data->table.number_philos)
		printf("[%ld]\t"BIG"Philo %d [%p] took %ld fork [%p]\n"DFT,
			now - data->table.starting_time, data->index, data->id, aux,
			&data->table.forks[aux]);
	else if (flag == TAKE)
		printf("[%ld]\t"BIG"Philo %d [%p] took %ld fork [%p]\n"DFT,
			now - data->table.starting_time, data->index, data->id, (long)0,
			&data->table.forks[0]);
	else if (flag == LEAVE && aux != data->table.number_philos)
		printf("[%ld]\t"UBIG"Philo %d [%p] dropped %ld fork [%p]\n"DFT,
			now - data->table.starting_time, data->index, data->id, aux,
			&data->table.forks[aux]);
	else if (flag == LEAVE)
		printf("[%ld]\t"UBIG"Philo %d [%p] dropped %ld fork [%p]\n"DFT,
			now - data->table.starting_time, data->index, data->id, (long)0,
			&data->table.forks[0]);
	else if (flag == EAT)
		printf("[%ld]\t"BIY"Philo %d [%p] is eating for %ld\n"DFT,
			now - data->table.starting_time, data->index, data->id, aux / 1000);
	else if (flag == SLEEP)
		printf("[%ld]\t"BP"Philo %d [%p] is sleeping for %ld\n"DFT,
			now - data->table.starting_time, data->index, data->id, aux / 1000);
	else if (flag == THINK)
		printf("[%ld]\t"IP"Philo %d [%p] is thinking\n"DFT,
			now - data->table.starting_time, data->index, data->id);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}
