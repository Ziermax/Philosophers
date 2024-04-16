/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oracle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:48:13 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 20:52:04 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	set_death(t_oracle *oracle, int index)
{
	int	index;
	t_philo	*philo;

	pthread_mutex_lock(&oracle->table.main->table_mutex);
	index = 0;
	while (index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index];
		pthread_mutex_lock(&philo->philo_mutex);
		philo->death = 1;
		pthread_mutex_unlock(&philo->philo_mutex);
		index++;
	}
	pthread_mutex_unlock(&oracle->table.main->table_mutex);
}

static void	check_death(t_oracle *oracle)
{
	int	index;
	t_philo	*philo;

	index = 0;
	while (index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index];
		pthread_mutex_lock(&philo->philo_mutex);
		if (!philo->fed)
		{
			print_action(philo, DEATH, 0);
			oracle->dinner_ended = 1;
			break ;
		}
		else
			philo->fed = 0;
		pthread_mutex_unlock(&philo->philo_mutex);
		index++;
	}
	if (oracle->dinner_ended)
		pthread_mutex_unlock(&philo->philo_mutex);
}

void	oracle_routine(t_oracle *oracle)
{
	while (!oracle->dinner_ended)
	{
		oracle->satitated_philos = 0;
		if (!is_time_to_die(oracle))
			check_death(oracle);
		if (oracle->dinner_ended)
			break ;
		cheack_satiated(oracle);
		if (oracle->satitated_philos == oracle->table.amount_philos)
			oracle->dinner_ended = 1;
	}
	set_death(oracle);
}
