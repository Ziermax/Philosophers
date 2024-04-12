/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:20:38 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 21:16:03 by mvelazqu         ###   ########.fr       */
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

void	print_action(t_data *data, int flag, int fork_index)
{
	long	now;

	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (flag == TAKE)
	printf("[%ld]\tPhilo %d took %d fork\n",
		data->current_time - now, data->index, fork_index);
	if (flag == LEAVE)
	printf("[%ld]\tPhilo %d dropped %d fork\n",
		data->current_time - now, data->index, fork_index);
	if (flag == EAT)
	printf("[%ld]\tPhilo %d is eating\n",
		data->current_time - now, data->index);
	if (flag == SLEEP)
	printf("[%ld]\tPhilo %d is sleeping\n",
		data->current_time - now, data->index);
	if (flag == THINK)
	printf("[%ld]\tPhilo %d is thinking\n",
		data->current_time - now, data->index);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}
