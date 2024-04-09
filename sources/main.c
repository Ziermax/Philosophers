/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:35:05 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/07 17:48:49 by mvelazqu         ###   ########.fr       */
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
	t_philo_data	data;

	if (argc != 6 && argc != 5)
		error_message(0, "Wrong number of arguments");
	data = parser_input(&argv[1]);
	if (data.philo_num == -1)
		error_message(0, "Wrong sysntax in arguments");
	printf("num: %d\ndie: %d\neat: %d\nslp: %d\nmin: %d\n",
		data.philo_num, data.time_to_die, data.time_to_eat,
		data.time_to_sleep, data.minimum_meals);
	start_dinner(data);
}
