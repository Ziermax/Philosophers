/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:47:10 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 15:45:14 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes2/philo.h"

int	pos_fail_atoi(char *num, int *fail_flag)
{
	unsigned int	nbr;

	nbr = 0;
	if ('+' == *num)
		num++;
	while (*num >= '0' && *num <= '9')
	{
		nbr = nbr * 10 + *num - '0';
		num++;
		if (nbr > 2147483647)
		{
			*fail_flag = 1;
			break ;
		}
	}
	if (*num)
		*fail_flag = 1;
	return ((int)nbr);
}

void	parser_input(t_table *table, char **argv)
{
	int		fail;
	int		i;

	i = 0;
	fail = 0;
	while (argv[i])
	{
		if (i == 0)
			table->number_philos = pos_fail_atoi(argv[i], &fail);
		if (i == 1)
			table->time_to_die = pos_fail_atoi(argv[i], &fail) * 1000;
		if (i == 2)
			table->time_to_eat = pos_fail_atoi(argv[i], &fail) * 1000;
		if (i == 3)
			table->time_to_sleep = pos_fail_atoi(argv[i], &fail) * 1000;
		if (i == 4)
			table->minimum_meals = pos_fail_atoi(argv[i], &fail);
		i++;
	}
	if (i == 4)
		table->minimum_meals = -1;
	if (fail || table->number_philos > 400)
		table->number_philos = 0;
}

void	init_table(t_table *table, char **argv)
{
	int	i;

	parser_input(table, argv);
	if (!table->number_philos)
		return ;
	table->forks = NULL;
	table->philos = malloc(sizeof(pthread_t) * table->number_philos);
	if (!table->philos)
		return ;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philos);
	if (!table->forks)
		return (free(table->philos));
	i = 0;
	while (i < table->number_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->table_mutex, NULL);
	table->main = table;
	table->starting_time = gettime();
}

void	init_philo(t_philo *philo, int index, t_table table)
{
	philo->index = index;
	philo->id = &table.philos[index];
	philo->current_time = table.starting_time;
	philo->meal_count = 0;
	philo->fed = 0;
	philo->death = 0;
	pthread_mutex_init(&philo->philo_mutex, NULL);
	philo->table = table;
}

void	init_oracle(t_oracle *oracle, t_table table)
{
	int	index;

	oracle->table = table;
	oracle->philos_sheet = malloc(sizeof(t_philo) * table.number_philos);
	printf("\nPhilos_sheet: [%p]\n", oracle->philos_sheet);
	if (!oracle->philos_sheet)
		return ;
	index = 0;
	while (index < table.number_philos)
	{
		init_philo(&oracle->philos_sheet[index], index, table);
		printf("Philo %d: [%p]\n", index, &oracle->philos_sheet[index]);
		index++;
	}
	oracle->current_time = table.starting_time + table.time_to_die;
	oracle->dinner_ended = 0;
}
