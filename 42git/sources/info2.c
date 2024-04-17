/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:29:06 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/17 21:03:01 by mvelazqu         ###   ########.fr       */
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

int	philo_status(t_philo *philo, int flag)
{
	int	info;

	pthread_mutex_lock(&philo->philo_mutex);
	if (flag == DEATH)
		info = philo->death;
	else if (flag == SATITATED)
		info = philo->meal_count >= philo->table.minimun_meals;
	else if (flag == FED)
		info = philo->fed;
	else if (flag == SET_FED)
	{
		philo->fed = 1;
		philo->meal_count += 1;
	}
	else if (flag == RESET_FED)
		philo->fed = 0;
	else if (flag == SET_DEATH)
		philo->death = 1;
	else
		info = -1;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (info);
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

void	print_status(t_philo *philo, int flag, long aux)
{
	long	now;

	now = gettime();
	if (flag == TAKE)
		printf("[%ld]\t"BIG"Philo %d took %ld fork\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index, aux);
	if (flag == LEAVE)
		printf("[%ld]\t"UBIG"Philo %d droped %ld fork\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index, aux);
	if (flag == EAT)
		printf("[%ld]\t"BIY"Philo %d is eating\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index);
	if (flag == SLEEP)
		printf("[%ld]\t"BP"Philo %d is sleeping\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index);
	if (flag == THINK)
		printf("[%ld]\t"IP"Philo %d is thinking\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index);
	if (flag == DEATH)
		printf("[%ld]\t"CR"Philo %d is DEATH\n"DFT,
			(now - philo->table.starting_time) / 1000, philo->index);
}

void	print_action(t_philo *philo, int flag, long aux)
{
	pthread_mutex_lock(&philo->table.main->table_mutex);
	if (!philo_status(philo, DEATH))
		print_status(philo, flag, aux),
	pthread_mutex_unlock(&philo->table.main->table_mutex);
}
