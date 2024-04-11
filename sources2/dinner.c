/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:10 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 17:33:12 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*dinner(void *arg)
{
	t_philo			*data;
	t_table			*main_table;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

	data = arg;
	pthread_mutex_lock(&data->table.main->table_mutex);
	right_fork = &data->table.forks[data->index];
	if (data->index != data->table.philo_amount)
		left_fork = &data->table.forks[data->index + 1];
	else
		left_fork = &data->table.forks[0];
	pthread_mutex_unlock(&data->table.main->table_mutex);
	main_table = data->table.main;
	while (!is_death(data))
	{
		take_forks(data, right_fork, left_fork);
		eat_meal(data);
		leave_forks(data, right_fork, left_fork);
		sleep_and_think(data);
	}
	return (arg);
}

void	end_dinner(t_oracle *oracle, int index, int flag)
{
	int		i;
	long	now;
	t_philo	*current_philo;

	i = 0;
	now = gettime();
	current_philo = (t_philo *)oracle->table.philos[index];
	pthread_mutex_lock(&oracle->table.main->table_mutex);
	if (flag == DEATH)
		printf("[%ld]\t"CR"Philo [%p] |%d|: muerto\n"DFT,
			now - oracle->table.starting_time, current_philo, index);
	while (i < oracle->table.philo_amount)
	{
		current_philo = &oracle->philo_sheet[i];
		pthread_mutex_lock(&current_philo->philo_mutex);
		current_philo->death = 1;
		pthread_mutex_unlock(&current_philo->philo_mutex);
		i++;
	}
	pthread_mutex_unlock(&oracle->table.main->table_mutex);
	oracle->ended_dinner = 1;
}

void	oracle_check(t_oracle *oracle)
{
	int		index;
	int		satiated_philos;
	t_philo	*current_philo;

	index = 0;
	satiated_philos = 0;
	while (index < oracle->table.philo_amount)
	{
		current_philo = &oracle->philo_sheet[index];
		if (!is_fed(current_philo))
			end_dinner(oracle, index, DEATH);
		if (oracle->ended_dinner)
			break ;
		pthread_mutex_lock(&current_philo->philo_mutex);
		if (current_philo->current_meals >= oracle->table.minimum_meals)
			current_philo->satiated = 1;
		pthread_mutex_unlock(&oracle->philo_sheet[index].philo_mutex);
		if (current_philo->satiated)
			satiated_philos += 1;
		index++;
	}
	if (satiated_philos == oracle->table.philo_amount)
		end_dinner(oracle, 0, SATIATED);
}

void	oracle_routine(t_oracle *oracle)
{
	long	now;
	long	finish_time;

	while (!oracle->ended_dinner)
	{
		finish_time = oracle->table.time_to_die + oracle->current_time;
		now = gettime();
		usleep((finish_time - now) * 1000);
		oracle_check(oracle);
	}
}

void	start_dinner(t_oracle *oracle)
{
	int	i;

	i = 0;
	while (i < oracle->table.philo_amount)
	{
		pthread_create(&oracle->table.philos[i], NULL, dinner,
			&oracle->philo_sheet[i]);
		i++;
	}
	oracle_routine(oracle);
}
