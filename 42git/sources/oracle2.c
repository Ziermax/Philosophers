/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oracle2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:38:05 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/17 21:02:56 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	set_death(t_oracle *oracle)
{
	int		index;
	t_philo	*philo;

	index = 0;
	while (index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index];
		philo_status(philo, SET_DEATH);
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
		if (philo_status(philo, SATITATED))
			oracle->satiated_philos += 1;
		index++;
	}
	if (oracle->satiated_philos == oracle->table.amount_philos)
	{
		pthread_mutex_lock(&oracle->table.main->table_mutex);
		set_death(oracle);
		pthread_mutex_unlock(&oracle->table.main->table_mutex);
	}
}

static void	check_death(t_oracle *oracle)
{
	int		index;
	t_philo	*philo;

	pthread_mutex_lock(&oracle->table.main->table_mutex);
	index = 0;
	while (index < oracle->table.amount_philos)
	{
		philo = &oracle->philos[index];
		if (philo_status(philo, FED))
			philo_status(philo, RESET_FED);
		else
		{
			print_status(philo, DEATH);
			set_death(oracle);
			break ;
		}
		index++;
	}
	pthread_mutex_lock(&oracle->table.main->table_mutex);
}

void	oracle_routine(t_oracle *oracle)
{
	if (oracle->table.minimun_meals == -1)
	{
		while (!oracle->dinner_ended)
			if (is_time_to_die(oracle))
				check_death(oracle);
		return ;
	}
	while (!oracle->dinner_ended)
	{
		if (is_time_to_die(oracle))
			check_death(oracle);
		check_satiated(oracle);
	}
}

void	precise_usleep(long time_to_wait, t_philo *philo)
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
