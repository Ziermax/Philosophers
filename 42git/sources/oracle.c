/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oracle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:48:13 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/17 17:51:44 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	set_death(t_oracle *oracle)
{
	int		index;
	t_philo	*philo;

	pthread_mutex_lock(&oracle->table.main->table_mutex);
//	printf("Setting DEATH at [%ld]\n", gettime() - oracle->table.starting_time);
	index = 0;
	while (index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index];
		pthread_mutex_lock(&philo->philo_mutex);
		philo->death = 1;
		pthread_mutex_unlock(&philo->philo_mutex);
		index++;
	}
//	printf("Setting DEATH ended at [%ld]\n",
//		gettime() - oracle->table.starting_time);
	pthread_mutex_unlock(&oracle->table.main->table_mutex);
}

static void	check_death(t_oracle *oracle)
{
	int		index;
	t_philo	*philo;

	index = 0;
	pthread_mutex_lock(&oracle->table.main->table_mutex);
//	printf("Checking DEATH at [%ld]\n",
//		gettime() - oracle->table.starting_time);
	pthread_mutex_unlock(&oracle->table.main->table_mutex);
	while (!oracle->dinner_ended && index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index++];
		pthread_mutex_lock(&philo->philo_mutex);
		if (!philo->fed)
		{
			print_action(philo, DEATH, 0);
			oracle->dinner_ended = 1;
		}
		else
			philo->fed = 0;
		pthread_mutex_unlock(&philo->philo_mutex);
	}
	pthread_mutex_lock(&oracle->table.main->table_mutex);
//	printf("Checking DEATH ended at [%ld]\n",
//		gettime() - oracle->table.starting_time);
	pthread_mutex_unlock(&oracle->table.main->table_mutex);
}

static void	cheack_satiated(t_oracle *oracle)
{
	int		index;
	t_philo	*philo;

	index = 0;
	oracle->satitated_philos = 0;
	while (index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index];
		if (is_satiated(philo))
			oracle->satitated_philos += 1;
		index++;
	}
	if (oracle->satitated_philos == oracle->table.amount_philos)
		oracle->dinner_ended = 1;
}

void	oracle_routine(t_oracle *oracle)
{
	while (!oracle->dinner_ended)
	{
		if (is_time_to_die(oracle))
			check_death(oracle);
		if (oracle->dinner_ended)
			break ;
		if (oracle->table.minimun_meals != -1)
			cheack_satiated(oracle);
	}
	set_death(oracle);
}

void	precise_usleep(long	time_to_wait, t_philo *philo)
{
	long	diff;

	philo->current_time += time_to_wait;
	diff = philo->current_time - gettime();
	while (diff <= 0)
	{
		diff += time_to_wait;
		philo->current_time += time_to_wait;
	}
	while (philo->current_time >= gettime())
		usleep(500);
}
