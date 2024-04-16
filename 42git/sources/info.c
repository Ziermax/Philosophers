/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:29:06 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 20:21:02 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_sec %= 31556925;
	return (time.tv_sec * 1e6 + time.tv_usec);
}

int	is_death(t_philo *philo)
{
	int	death_info;

	pthread_mutex_lock(&philo->philo_mutex);
	death_info = philo->death;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (death_info);
}

int	is_satiated(t_philo *philo)
{
	int	satiated_info;

	pthread_mutex_lock(&philo->philo_mutex);
	satiated_info = philo->meal_count >= philo->table.minimun_meals;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (satiated_info);
}

int	is_time_to_die(t_oracle *oracle)
{
	if (oracle->current_time <= gettime())
	{
		oracle->current_time += oracle->table.time_to_die;
		return (1);
	}
	return (0);
}

void	print_action(t_philo *philo, int flag, long aux)
{
	long	now;
	pthread_mutex_lock(&data->table.main->table_mutex);
	now = gettime();
	if (flag == TAKE)
		printf("[%ld\t"BIG"Philo %d took %ld fork\n"DFT,
			now - philo->table.starting_time, philo->index, aux);
	if (flag == LEAVE)
		printf("[%ld\t"UBIG"Philo %d droped %ld fork\n"DFT,
			now - philo->table.starting_time, philo->index, aux);
	if (flag == EAT)
		printf("[%ld\t"BIY"Philo %d is eating\n"DFT,
			now - philo->table.starting_time, philo->index);
	if (flag == SLEEP)
		printf("[%ld\t"BP"Philo %d is sleeping\n"DFT,
			now - philo->table.starting_time, philo->index);
	if (flag == THINK)
		printf("[%ld\t"IP"Philo %d is thinking\n"DFT,
			now - philo->table.starting_time, philo->index);
	if (flag == DEATH)
		printf("[%ld\t"IP"Philo %d is DEATH\n"DFT,
			now - philo->table.starting_time, philo->index);
	pthread_mutex_unlock(&data->table.main->table_mutex);
}
