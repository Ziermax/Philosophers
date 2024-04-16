/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:22:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 20:51:38 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*dinner_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if ((philo->index + 1) % 2)
		usleep(500);
	while (!is_death(philo))
	{
		take_forks(philo);
		eat_meal(philo);
		leave_forks(philo);
		sleep_and_think(philo);
	}
}

void	dinner(t_oracle *oracle)
{
	int			index;
	pthread_t	*philo_thread;
	t_philo		*philo;

	index = 0;
	while (index < oracle->table.amount_philos)
	{
		philo_thread = &oracle->table.philo_threads[index];
		philo = &oracle->philos[index];
		pthread_create(philo_thread, NULL, dinner_philo, philo);
		index++;
	}
}
