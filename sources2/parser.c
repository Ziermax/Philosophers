/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:03:10 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 17:23:28 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

t_table	parser_input(char **argv)
{
	t_table	table;
	int		fail;
	int		i;

	i = 0;
	fail = 0;
	while (argv[i])
	{
		if (i == 0)
			table.philo_amount = pos_fail_atoi(argv[i], &fail);
		if (i == 1)
			table.time_to_die = pos_fail_atoi(argv[i], &fail);
		if (i == 2)
			table.time_to_eat = pos_fail_atoi(argv[i], &fail);
		if (i == 3)
			table.time_to_sleep = pos_fail_atoi(argv[i], &fail);
		if (i == 4)
			table.minimum_meals = pos_fail_atoi(argv[i], &fail);
		i++;
	}
	if (i == 4)
		table.minimum_meals = -1;
	if (fail)
		table.philo_amount = 0;
	return (table);
}
