/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oracle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:09:27 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/21 15:55:34 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	kill_philos(t_oracle *oracle)
{
	int		index;
	t_philo	*philo;

	if (oracle->dinner_ended)
		return ;
	index = 0;
	oracle->dinner_ended = 1;
	while (index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index];
		set_death(philo);
		index++;
	}
}

static void	check_satiated(t_oracle *oracle)
{
	int		index;
	t_philo	*philo;

	if (oracle->dinner_ended)
		return ;
	index = 0;
	oracle->satiated_philos = 0;
	while (index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index];
		if (is_satiated(philo))
			oracle->satiated_philos += 1;
		index++;
	}
	if (oracle->satiated_philos == oracle->table.amount_philos)
	{
		pthread_mutex_lock(&oracle->table.main->table_mutex);
		kill_philos(oracle);
		pthread_mutex_unlock(&oracle->table.main->table_mutex);
	}
}

static void	check_death(t_oracle *oracle)
{
	int		index;

	index = 0;
	while (index < oracle->table.amount_philos)
	{
		if (!is_fed(&oracle->philos[index]))
		{
			pthread_mutex_lock(&oracle->table.main->table_mutex);
			printf("[%ld]\t"CR"Philo %d is DEATH\n"DFT,
				(gettime() - oracle->philos[index].table.starting_time) / 1000,
				oracle->philos[index].index);
			kill_philos(oracle);
			pthread_mutex_unlock(&oracle->table.main->table_mutex);
			break ;
		}
		index++;
	}
}

void	oracle_routine(t_oracle *oracle)
{
	if (oracle->table.minimun_meals == -1)
	{
		while (!oracle->dinner_ended)
		{
			usleep(2000);
			if (is_time_to_die(oracle))
				check_death(oracle);
		}
		return ;
	}
	while (!oracle->dinner_ended)
	{
		usleep(5000);
		if (is_time_to_die(oracle))
			check_death(oracle);
		check_satiated(oracle);
	}
}
