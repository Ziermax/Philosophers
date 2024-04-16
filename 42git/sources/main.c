/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:01:47 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 20:24:13 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_oracle	oracle;
	if (argc != 5 && argc != 6)
		return (0);
	init_table(&table, &argv[1]);
	init_oracle(&oracle, &table);
	dinner(&oracle);
}
