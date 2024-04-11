/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:34:41 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 16:53:26 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_table(t_table *table)
{
	free(table->philos);
	free(table->forks);
	write(2, "Mallocation failed\n", 19);
	exit(errno);
}

void	init_table(t_table *table, char **argv)
{
	table->philos = NULL;
	table->forks = NULL;
	*table = parser_input(argv);
	if (table->philo_amount == 0)
		return ;
	table->philos = malloc(sizeof(pthread_t) * (table->philo_amount));
	if (!table->philos)
		return (free_table(table));
	table->forks = malloc(sizeof(pthread_t) * (table->philo_amount));
	if (!table->forks)
		return (free_table(table));
	table->main = table;
	table->starting_time = gettime();
	if (table->starting_time == -1)
		return (free_table(table));
}

void	init_philo(t_philo *philo, int index, t_table *table)
{
	philo->index = index;
	philo->id = &table->philos[index];
	philo->current_time = table->starting_time;
	philo->current_meals = 0;
	philo->fed = 0;
	philo->satiated = 0;
	philo->death = 0;
	philo->table = *table;
}

void	init_oracle(t_oracle *oracle, t_table *table)
{
	t_philo	*sheets;
	int		i;

	sheets = malloc(sizeof(t_philo) * table->philo_amount);
	oracle->philo_sheet = sheets;
	if (!sheets)
		return (free_table(table));
	i = 0;
	while (i < table->philo_amount)
	{
		init_philo(&sheets[i], i, table);
		i++;
	}
	oracle->table = *table;
	oracle->current_time = table->starting_time;
	oracle->ended_dinner = 0;
}
