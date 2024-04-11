/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:53:17 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 17:23:41 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_message(int exit_ret, char *error_text)
{
	printf("%s\n", error_text);
	exit(exit_ret);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_oracle	oracle;

	if (argc != 6 && argc != 5)
		error_message(0, "Wrong number of arguments");
	init_table(&table, &argv[1]);
	if (!table.philo_amount)
		error_message(0, "Wrong syntax in arguments");
	init_oracle(&oracle, &table);
	if (!oracle.philo_sheet)
		error_message(errno, "Mallocation failed");
	start_dinner(&oracle);
}
