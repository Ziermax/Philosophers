/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:41:09 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/21 15:53:43 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	fail_pos_atoi(char *num, int *fail)
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
			*fail = 1;
			break ;
		}
		num++;
	}
	if (*num || nbr == 0)
		*fail = 1;
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
			table->amount_philos = fail_pos_atoi(argv[i], &fail);
		if (i == 1)
			table->time_to_die = fail_pos_atoi(argv[i], &fail) * 1000;
		if (i == 2)
			table->time_to_eat = fail_pos_atoi(argv[i], &fail) * 1000;
		if (i == 3)
			table->time_to_sleep = fail_pos_atoi(argv[i], &fail) * 1000;
		if (i == 4)
			table->minimun_meals = fail_pos_atoi(argv[i], &fail);
		i++;
	}
	if (i == 4)
		table->minimun_meals = -1;
	if (fail)
		table->amount_philos = 0;
}
// || table->amount_philos > 400)

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
		pthread_mutex_init(&table->forks[index++], NULL);
	pthread_mutex_init(&table->table_mutex, NULL);
	table->main = table;
	table->starting_time = gettime();
}

static void	init_philo(t_philo *philo, int index, t_table table)
{
	philo->index = index + 1;
	philo->last_meal = table.starting_time;
	philo->fork[RIGHT] = &table.forks[index];
	philo->fork_id[RIGHT] = index + 1;
	if (index + 1 != table.amount_philos)
	{
		philo->fork[LEFT] = &table.forks[index + 1];
		philo->fork_id[LEFT] = index + 2;
	}
	else
	{
		philo->fork[LEFT] = &table.forks[0];
		philo->fork_id[LEFT] = 1;
	}
	philo->meal_count = 0;
	philo->death = 0;
	pthread_mutex_init(&philo->philo_mutex, NULL);
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
