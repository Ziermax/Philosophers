/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:05:31 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 16:28:49 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	fail_pos_atoi(char *num, int *fail)
{
	unsigned int	nbr;

	nbr = 0;
	if (*num == '+')
		num++;
	while (*num >= '0' && *num <= '9')
	{
		nbr = nbr * 10 + *num - '0';
		if (nbr > 2147483647)
		{
			*fail_flag = 1;
			break ;
		}
		num++;
	}
	if (*num)
		*fail_flag = 1;
	return ((int)nbr);
}

static void	parser_input(t_table *table, char **argv)
{
	int		fail;
	int		i;

	i = 0;
	fail = 0;
	while (argv[i])
	{
		if (i == 0)
			table->number_philos = fail_pos_atoi(argv[i], &fail);
		if (i == 1)
			table->time_to_die = fail_pos_atoi(argv[i], &fail) * 1000;
		if (i == 2)
			table->time_to_eat = fail_pos_atoi(argv[i], &fail) * 1000;
		if (i == 3)
			table->time_to_sleep = fail_pos_atoi(argv[i], &fail) * 1000;
		if (i == 4)
			table->minimum_meals = fail_pos_atoi(argv[i], &fail);
		i++;
	}
	if (i == 4)
		table->minimum_meals = -1;
	if (fail || table->number_philos > 400)
		table->number_philos = 0;
}

void	init_table(t_table *table, char **argv)
{
	int	index;

	parser_input(table, argv);
	table->philo_threads = malloc(sizeof(pthread_t) * table->amount_philos);
	if (!table->philo_threads)
		return ;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->amount_philos);
	if (!table->forks)
		return (free(table->philo_threads));
	index = 0;
	while (index < table->amount_philos)
		pthread_mutex_init(&table->forks[index++]);
	pthread_mutex_init(&table->table_mutex);
	table->main = table;
	table->starting_time = gettime();
}

void	init_philo(t_philo *philo, int index, t_table table)
{
	philo->index = index;
	philo->id = &table.philo_threads[index];
	philo->current_time = table.starting_time;
	philo->fork[RIGHT] = table.fork[index];
	if (index + 1 != table.amount_philos)
		philo->fork[LEFT] = table.fork[index + 1];
	else
		philo->fork[LEFT] = table.fork[0];
	philo->meal_count = 0;
	philo->fed = 0;
	philo->death = 0;
	philo->table = table;
}

void	init_oracle(t_oracle *oracle, t_table table)
{
	int	index;

	oracle->current_time = table.starting_time + table.time_to_die;
	oracle->dinner_ended = 0;
	oracle->philos = malloc(sizeof(t_philo) * table.amount_philos);
	if (!oracle->philos)
		return (free(table.philo_threads), free(table.forks));
	index = -1;
	while (++index < table.amount_philos)
		init_philo(&oracle->philos[index], index, table);
	oracle->table = table;
}
