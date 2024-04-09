/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:43:03 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/09 17:30:39 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <sys/types.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo_data
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		minimum_meals;
	long	starting_time;
}	t_philo_data;

typedef struct s_data
{
	void			*id;
	t_philo_data	philo_dt;
	pthread_t		**philos;
	pthread_mutex_t	**forks;
}	t_data;

long				gettime(void);
t_philo_data		parser_input(char **argv);
void				free_buff_of_buff(void **buffer);
pthread_t			**create_philosophers(int amount);
pthread_mutex_t		**create_forks(int amount);
t_data				*create_data(void *id, t_philo_data philo_dt,
		pthread_t **philos, pthread_mutex_t **forks);
void				start_dinner(t_philo_data data);
int					find_index_dir(void *dir, void **array_dir);

#endif
