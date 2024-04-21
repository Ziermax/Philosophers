/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:32:45 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/21 15:59:00 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	join_destroy_and_free(t_table table, t_oracle oracle)
{
	int	index;

	index = 0;
	while (index < table.amount_philos)
	{
		pthread_join(table.philo_threads[index], NULL);
		pthread_mutex_destroy(&table.forks[index]);
		index++;
	}
	free(table.philo_threads);
	free(table.forks);
	free(oracle.philos);
}

static void	print_exit(int exit_value, char *str)
{
	printf("%s\n", str);
	exit(exit_value);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_oracle	oracle;

	if (argc != 5 && argc != 6)
		print_exit(0, "Wrong number of arguments");
	init_table(&table, &argv[1]);
	if (!table.amount_philos)
		print_exit(0, "Wrong syntax in arguments");
	if (!table.philo_threads)
		print_exit(0, "Failed mallocation");
	init_oracle(&oracle, table);
	if (!oracle.philos)
		print_exit(0, "Failed mallocation");
	dinner(&oracle);
	oracle_routine(&oracle);
	join_destroy_and_free(table, oracle);
}
