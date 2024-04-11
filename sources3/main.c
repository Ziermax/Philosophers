/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:44:41 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 20:29:37 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes2/philo.h"

void	free_all(t_oracle *oracle)
{
	int	i;

	i = 0;
	while (i < oracle->table.number_philos)
	{
		pthread_join(oracle->table.philos[i], NULL);
		pthread_mutex_destroy(&oracle->table.forks[i]);
		pthread_mutex_destroy(&oracle->philos_sheet[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&oracle->table.main->table_mutex);
	free(oracle->table.philos);
	free(oracle->table.forks);
	free(oracle->philos_sheet);
}

void	print_info(t_oracle *oracle)
{
	t_table	table;
	t_philo	*philo;
	int		i;
	long	now;

	now = gettime();
	table = oracle->table;
	printf("\n###TABLE###\nNPH: %d | TTD: %d | TTE: %d | TTS: %d | MIN:%d\n"
		"Start: %li\nPhilo array: %p\nFork array: %p\nMain dir: %p\n\n",
		table.number_philos, table.time_to_die, table.time_to_eat,
		table.time_to_sleep, table.minimum_meals, now - table.starting_time,
		table.philos, table.forks, table.main);
	printf("###ORACLE###\nCurrent time: %li\nDinner ended: %d\n"
		"Philos sheet: %p\n\n", now - oracle->current_time,
		oracle->dinner_ended, oracle->philos_sheet);
	i = -1;
	while (++i < oracle->table.number_philos)
	{
		philo = &oracle->philos_sheet[i];
		printf("###PHILO [%p]###\nindex: %d\nid: %p | fork: %p\nCurrent time: "
			"%li\nMeal count: %d | Fed: %d | Death: %d\n\n", philo,
			philo->index, philo->id, &oracle->table.forks[i],
			now - philo->current_time, philo->meal_count, philo->fed,
			philo->death);
	}
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_oracle	oracle;

	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments\n"));
	init_table(&table, &argv[1]);
	if (!table.number_philos)
		return (printf("Wrong number of arguments\n"));
	if (!table.philos)
		return (printf("Mallocation failed\n"));
	init_oracle(&oracle, table);
	if (!oracle.philos_sheet)
		return (free(table.philos), free(table.forks),
			printf("Mallocation failed\n"));
	start_dinner(&oracle);
	print_info(&oracle);
	free_all(&oracle);
}
//	start_monitoring(&oracle);
