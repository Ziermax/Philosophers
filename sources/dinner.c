/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:11:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/10 14:26:09 by mvelazqu         ###   ########.fr       */
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
	printf("[%ld]\t"BIC"Philo [%p] %d: vivo\n"DFT,
		gettime() - data->philo_dt.starting_time, data->id, index);
	meals = 1;
//	if (index % 2)
//		usleep(300);
//		usleep(data->philo_dt.time_to_eat * 250);
	while (data->philo_dt.minimum_meals == -1
		|| meals <= data->philo_dt.minimum_meals)
	{
//	FILOSOFO COGE LOS TENEDORES
	//	FILOSOFOS INPARES COGEN 1ER TENEDOR PRIMERO
		if (index % 2)
		{
			pthread_mutex_lock(data->forks[index - 1]);
			printf("[%ld]\t"BIG"Philo [%p] |%d|: toma 1er tenedor %d [%p]\n"
				DFT, gettime() - data->philo_dt.starting_time, data->id,
				index, index, data->forks[index - 1]);
			if (data->forks[index] != NULL)
				pthread_mutex_lock(data->forks[index]);
			else
				pthread_mutex_lock(data->forks[0]);
			printf("[%ld]\t"G"Philo [%p] |%d|: toma 2do tenedor %d [%p]\n"
				DFT, gettime() - data->philo_dt.starting_time, data->id,
				index, index + 1, data->forks[index]);
		}
	//	FILOSOFOS PARES COGEN 2DO TENEDOR PRIMERO
		else
		{
			if (data->forks[index] != NULL)
				pthread_mutex_lock(data->forks[index]);
			else
				pthread_mutex_lock(data->forks[0]);
			printf("[%ld]\t"G"Philo [%p] |%d|: toma 2do tenedor %d [%p]\n"DFT,
				gettime() - data->philo_dt.starting_time, data->id,
				index, index + 1, data->forks[index]);
			pthread_mutex_lock(data->forks[index - 1]);
			printf("[%ld]\t"BIG"Philo [%p] |%d|: toma 1er tenedor %d [%p]\n"
				DFT, gettime() - data->philo_dt.starting_time, data->id,
				index, index, data->forks[index - 1]);
		}


//	FILOSOFO ESTA COMIENDO
		usleep(data->philo_dt.time_to_eat * 1000);
		printf("[%ld]\t"BIY"Philo [%p] |%d|: ha comido %d vez\n"DFT,
			gettime() - data->philo_dt.starting_time, data->id, index, meals);
		meals++;

//	FILSOSOFO SUELTA LOS TENEDORES
		pthread_mutex_unlock(data->forks[index - 1]);
		printf("[%ld]\t"UBIG"Philo [%p] |%d|: suelta 1er tenedor %d[%p]\n"
			DFT, gettime() - data->philo_dt.starting_time, data->id,
			index, index, data->forks[index - 1]);
		if (data->forks[index] != NULL)
			pthread_mutex_unlock(data->forks[index]);
		else
			pthread_mutex_unlock(data->forks[0]);
		printf("[%ld]\t"UG"Philo [%p] |%d|: suelta 2do tenedor %d[%p]\n"DFT,
			gettime() - data->philo_dt.starting_time, data->id,
			index, index + 1, data->forks[index]);

//	FILOSOFO DUERME LA SIESTA
		printf("[%ld]\t"BP"Philo [%p] |%d|: durmiendo por %d\n"DFT,
			gettime() - data->philo_dt.starting_time, data->id, index,
			data->philo_dt.time_to_sleep);
		usleep(data->philo_dt.time_to_sleep * 1000);

//	FILOSOFO DESPIERTA
		printf("[%ld]\t"IP"Philo [%p] |%d|: despierta\n"DFT,
			gettime() - data->philo_dt.starting_time, data->id, index);
	}
	printf("[%ld]\t"CR"Philo [%p] |%d|: muerto\n"DFT,
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

//	MALLOCO LA ESTRUCTRAS DE PHILOSOFOS (pthreads)
	philos = create_philosophers(philo_dt.philo_num);
	if (!philos)
		return ;

// MALLOCO LA ESTRUCTURAS DE TENEDORES (mutex)
	forks = create_forks(philo_dt.philo_num);
	if (!forks)
		return ;
	id = 0;
	philo_dt.starting_time = gettime();

//	CREO LOS HILOS EJECUTANDOLOR CON LA FUNCION dinner
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

//	RECOJO LOS CADAVERES DE LOS PHILOSOFOS necesito matarlos antes
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
