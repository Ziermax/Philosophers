/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:18:11 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 21:16:03 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes2/philo.h"

void	*dinner(void *arg)
{
	t_philo			*data;
	pthread_mutex_t	*forks[2];

	data = arg;
	forks[RIGHT] = data->table.forks[i];
	if (i != data->table.number_philos)
		forks[LEFT] = data->table.forks[i + 1];
	else
		forks[LEFT] = data->table.forks[0];
	while (!is_death(data) && !is_satiated(data))
	{
		take_forks(data, forks);
		eat_meal(data);
		leave_forks(data, forks);
		sleep_and_think(data);
	}
	return (arg);
}

void	start_dinner(t_oracle *oracle)
{
	int			index;
	pthread_t	*philo;
	t_philo		*data;

	index = 0;
	while (index < oracle->table.number_philos)
	{
		philo = &oracle->table.philos[index];
		data = &oracle->philos_sheet[index];
		pthread_create(philo, NULL, dinner, data);
		index++;
	}
}

void	oracle_routine(t_oracle *oracle, t_philo *philo_data)
{

}

void	start_monitoring(t_oracle *oracle)
{
	int	index;

	while (!oracle->dinner_ended)
	{
		index = 0;
		while (index < oracle->number_philos)
		{
			oracle_routine(oracle, &oracle->philos_sheet[index]);
			index++;
		}
	}
}
