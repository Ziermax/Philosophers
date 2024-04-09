/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:11:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/09 18:15:12 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



void	*dinner(void *aux)
{
	int		index;
	t_data	*data;
	int		meals;

	data = aux;
	index = find_index_dir(data->id, (void **)data->philos);
	printf("[%ld]\t\033[1;96mPhilo [%p] %d: vivo\n\033[0m",
		gettime() - data->philo_dt.starting_time, data->id, index);
	meals = 1;
//	if (index % 2)
//		usleep(300);
//		usleep(data->philo_dt.time_to_eat * 250);
	while (data->philo_dt.minimum_meals == -1
		|| meals <= data->philo_dt.minimum_meals)
	{
//	FILOSOFO COGE LOS TENEDORES
		if (index % 2)
		{
			pthread_mutex_lock(data->forks[index - 1]);
			printf("[%ld]\t\033[1;92mPhilo [%p] |%d|: toma 1er tenedor %d [%p]\
					\033[0m\n", gettime() - data->philo_dt.starting_time, data->id,
					index, index, data->forks[index - 1]);
			if (data->forks[index] != NULL)
				pthread_mutex_lock(data->forks[index]);
			else
				pthread_mutex_lock(data->forks[0]);
			printf("[%ld]\t\033[32mPhilo [%p] |%d|: toma 2do tenedor %d [%p]\
					\033[0m\n", gettime() - data->philo_dt.starting_time, data->id,
					index, index + 1, data->forks[index]);
		}
		else
		{
			if (data->forks[index] != NULL)
				pthread_mutex_lock(data->forks[index]);
			else
				pthread_mutex_lock(data->forks[0]);
			printf("[%ld]\t\033[32mPhilo [%p] |%d|: toma 2do tenedor %d [%p]\
					\033[0m\n", gettime() - data->philo_dt.starting_time, data->id,
					index, index + 1, data->forks[index]);
			pthread_mutex_lock(data->forks[index - 1]);
			printf("[%ld]\t\033[1;92mPhilo [%p] |%d|: toma 1er tenedor %d [%p]\
					\033[0m\n", gettime() - data->philo_dt.starting_time, data->id,
					index, index, data->forks[index - 1]);
		}


//	FILOSOFO ESTA COMIENDO
		usleep(data->philo_dt.time_to_eat * 1000);
		printf("[%ld]\t\033[1;93mPhilo [%p] |%d|: ha comido %d vez\033[0m\n",
			gettime() - data->philo_dt.starting_time, data->id, index, meals);
		meals++;

//	FILSOSOFO SUELTA LOS TENEDORES
		pthread_mutex_unlock(data->forks[index - 1]);
		printf("[%ld]\t\033[4;1;92mPhilo [%p] |%d|: suelta 1er tenedor %d"
			"[%p]\033[0m\n", gettime() - data->philo_dt.starting_time, data->id,
			index, index, data->forks[index - 1]);
		if (data->forks[index] != NULL)
			pthread_mutex_unlock(data->forks[index]);
		else
			pthread_mutex_unlock(data->forks[0]);
		printf("[%ld]\t\033[4;32mPhilo [%p] |%d|: suelta 2do tenedor %d"
			"[%p]\033[0m\n", gettime() - data->philo_dt.starting_time, data->id,
			index, index + 1, data->forks[index]);

//	FILOSOFO DUERME LA SIESTA
		printf("[%ld]\t\033[1;35mPhilo [%p] |%d|: durmiendo por %d\033[0m\n",
			gettime() - data->philo_dt.starting_time, data->id, index,
			data->philo_dt.time_to_sleep);
		usleep(data->philo_dt.time_to_sleep * 1000);

//	FILOSOFO DESPIERTA
		printf("[%ld]\t\033[1;35mPhilo [%p] |%d|: despierta\033[0m\n",
			gettime() - data->philo_dt.starting_time, data->id, index);
	}
	printf("[%ld]\t\033[3;31mPhilo [%p] |%d|: muerto\033[0m\n",
			gettime() - data->philo_dt.starting_time, data->id, index);
	return (data);
}

void	start_dinner(t_philo_data philo_dt)
{
	pthread_t		**philos;
	pthread_mutex_t	**forks;
	int				id;
	t_data			*data;

	printf("starting dinner\n");
	philos = create_philosophers(philo_dt.philo_num);
	if (!philos)
		return ;
	forks = create_forks(philo_dt.philo_num);
	if (!forks)
		return ;
	id = 0;
	philo_dt.starting_time = gettime();
	while (philos[id])
	{
		pthread_mutex_init(forks[id], NULL);
		data = create_data(philos[id], philo_dt, philos, forks);
		if (!data)
			return (free_buff_of_buff((void **)philos),
				free_buff_of_buff((void **)forks));
		pthread_create(philos[id], NULL, dinner, data);
		id++;
	}
	id = 0;
	while (philos[id])
	{
		pthread_join(*(philos[id]), (void **)&data);
		pthread_mutex_destroy(forks[id]);
		id++;
		free(data);
	}
	free_buff_of_buff((void **)philos);
	free_buff_of_buff((void **)forks);
}
