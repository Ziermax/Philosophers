/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:32:07 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 21:16:03 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "colors.h"

# define LEFT 1
# define RIGHT 0
# define DEATH 42
# define SATIATED 24

typedef struct s_table
{
	int				number_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				minimum_meals;
	long			starting_time;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	table_mutex;
	struct s_table	*main;
}	t_table;

typedef struct s_philo
{
	int				index;
	void			*id;
	long			current_time;
	int				meal_count;
	int				fed;
	int				death;
	pthread_mutex_t	philo_mutex;
	t_table			table;
}	t_philo;

typedef struct s_oracle
{
	long	current_time;
	int		dinner_ended;
	t_philo	*philos_sheet;
	t_table	table;
}	t_oracle;

long	gettime(void);
void	print_info(t_oracle *oracle);
void	init_table(t_table *table, char **argv);
void	init_oracle(t_oracle *oracle, t_table table);
int		is_death(t_philo *data);
int		is_satiated(t_philo *data);
void	take_forks(t_philo *data, pthread_mutex_t *forks[2]);
void	eat_meal(t_philo *data);
void	leave_forks(t_philo *data, pthread_mutex_t *forks[2]);
void	sleep_and_think(t_philo *data);
void	start_dinner(t_oracle *oracle);

#endif
