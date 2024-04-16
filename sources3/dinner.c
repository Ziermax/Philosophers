/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:18:11 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 15:45:14 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes2/philo.h"

void	assign_forks(t_philo *data, pthread_mutex_t *forks[2])
{
	if (1 + (data->index + 1) % 2)
	{
		forks[RIGHT] = &data->table.forks[data->index];
		if (data->index + 1 != data->table.number_philos)
			forks[LEFT] = &data->table.forks[data->index + 1];
		else
			forks[LEFT] = &data->table.forks[0];
	}
	else
	{
		forks[LEFT] = &data->table.forks[data->index];
		if (data->index + 1 != data->table.number_philos)
			forks[RIGHT] = &data->table.forks[data->index + 1];
		else
			forks[RIGHT] = &data->table.forks[0];
	}
}

void	*dinner(void *arg)
{
	t_philo			*data;
	pthread_mutex_t	*forks[2];

	data = arg;
	assign_forks(data, forks);
	if ((data->index + 1) % 2)
		usleep(500);
	while (!is_death(data))// && (data->table.minimum_meals == -1
//		|| !is_satiated(data)))
	{
		take_forks(data, forks);
		eat_meal(data);
		leave_forks(data, forks);
		sleep_and_think(data);
	}
	printf(BIY"Ended dinner Philo %d\n"DFT, data->index);
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
	pthread_mutex_lock(&philo_data->philo_mutex);
	printf("Philo %d fed: %d [%ld]\n", philo_data->index, philo_data->fed,
		gettime() - oracle->table.starting_time);
	if (!philo_data->fed)
	{
		oracle->dinner_ended = 1;
		pthread_mutex_lock(&oracle->table.main->table_mutex);
		printf(CR"[%ld]\tPhilo %d is dead\n"DFT,
			(gettime() - oracle->table.starting_time) / 1000, philo_data->index);
		pthread_mutex_unlock(&oracle->table.main->table_mutex);
		oracle->dinner_ended = 1;
	}
	else
		philo_data->fed = 0;
	pthread_mutex_unlock(&philo_data->philo_mutex);
}

void	set_death(t_philo *data)
{
	pthread_mutex_lock(&data->philo_mutex);
	data->death = 1;
	pthread_mutex_unlock(&data->philo_mutex);
}

void	kill_philos(t_oracle *oracle)
{
	int	index;

	index = 0;
	pthread_mutex_lock(&oracle->table.main->table_mutex);
	while (index < oracle->table.number_philos)
	{
		printf("Killing philo %d [%ld]\n", oracle->philos_sheet[index].index,
			gettime() - oracle->table.starting_time);
		set_death(&oracle->philos_sheet[index]);
		index++;
	}
	pthread_mutex_unlock(&oracle->table.main->table_mutex);
}

void	start_monitoring(t_oracle *oracle)
{
	int	index;

	while (!oracle->dinner_ended)
	{
//		usleep(oracle->table.time_to_die);
		oracle->satiated_philos = 0;
		index = 0;
		if (is_time_to_die(oracle))
		{
			while (!oracle->dinner_ended && index < oracle->table.number_philos)
			{
				oracle_routine(oracle, &oracle->philos_sheet[index]);
				if (is_satiated(&oracle->philos_sheet[index]))
					oracle->satiated_philos += 1;
				index++;
			}
		}
		else
		{
			while (!oracle->dinner_ended && index < oracle->table.number_philos)
			{
				if (is_satiated(&oracle->philos_sheet[index]))
					oracle->satiated_philos += 1;
				index++;
			}
			if (oracle->satiated_philos == oracle->table.number_philos)
				oracle->dinner_ended = 1;
		}
	}
	kill_philos(oracle);
}
