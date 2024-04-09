/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:12:32 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/09 17:30:20 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_buff_of_buff(void **buffer)
{
	int	i;

	i = 0;
	while ((char *)buffer[i])
		free(buffer[i++]);
	free(buffer);
}

pthread_t	**create_philosophers(int amount)
{
	pthread_t	**philosophers;
	int			id;

	philosophers = malloc(sizeof(pthread_t *) * (amount + 1));
	if (!philosophers)
		return (NULL);
	id = 0;
	while (id < amount)
	{
		philosophers[id] = malloc(sizeof(pthread_t));
		if (!philosophers[id])
			return (free_buff_of_buff((void **)philosophers), NULL);
		id++;
	}
	philosophers[id] = NULL;
	return (philosophers);
}

pthread_mutex_t	**create_forks(int amount)
{
	pthread_mutex_t	**forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t *) * (amount + 1));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (free_buff_of_buff((void **)forks), NULL);
		i++;
	}
	forks[i] = NULL;
	return (forks);
}

t_data	*create_data(void *id, t_philo_data philo_dt,
	pthread_t **philos, pthread_mutex_t **forks)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->id = id;
	data->philo_dt = philo_dt;
	data->philos = philos;
	data->forks = forks;
	return (data);
}

int	find_index_dir(void *dir, void **array_dir)
{
	int	i;

	i = 0;
	while (array_dir[i])
	{
		if (array_dir[i] == dir)
			return (1 + i);
		i++;
	}
	return (-1);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}
