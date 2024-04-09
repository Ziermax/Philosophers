/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:00:22 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/09 18:06:31 by mvelazqu         ###   ########.fr       */
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

t_philo_data	parser_input(char **argv)
{
	t_philo_data	data;
	int				fail;
	int				i;

	i = 0;
	fail = 0;
	while (argv[i])
	{
		if (i == 0)
			data.philo_num = pos_fail_atoi(argv[i], &fail);
		if (i == 1)
			data.time_to_die = pos_fail_atoi(argv[i], &fail);
		if (i == 2)
			data.time_to_eat = pos_fail_atoi(argv[i], &fail);
		if (i == 3)
			data.time_to_sleep = pos_fail_atoi(argv[i], &fail);
		if (i == 4)
			data.minimum_meals = pos_fail_atoi(argv[i], &fail);
		i++;
	}
	if (i == 4)
		data.minimum_meals = -1;
	if (fail || data.philo_num == 0)
		data.philo_num = -1;
	return (data);
}
