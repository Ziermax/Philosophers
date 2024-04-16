/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oracle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:48:13 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 20:52:04 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	oracle_routine(t_oracle *oracle)
{
	int	index;

	index = 0;
	while (index < oracle->table.amount_philos)
	{
		if (!is_time_to_die(oracle))
			check_death(
		index++;
	}
}
