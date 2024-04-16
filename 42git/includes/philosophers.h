/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:48 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/16 20:51:50 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/types.h>
# include <sys/errno.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# include "colors.h"

# define RIGHT 0
# define LEFT 1
# define SATITATED 24
# define TAKE 1
# define LEAVE 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DEATH 6

typedef struct s_table
{
	int				amount_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				minimun_meals;
	long			starting_time;
	pthread_t		*philo_threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t table_mutex;
	struct s_table	*main;
}	t_table;

typedef struct s_philo
{
	int				index;
	void			*id;
	long			current_time;
	pthread_mutex_t	*fork[2];
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
	int		satitated_philos;
	t_philo	*philos;
	t_table	table;
}	t_oracle;

void	init_table(t_table *table, char **argv);
void	init_oracle(t_oracle *oracle, t_table table);

long	gettime(void);
int		is_death(t_philo *philo);
int		is_satiated(t_philo	*philo);
int		is_time_to_die(t_oracle *oracle);
void	print_action(t_philo *philo, int flag, long aux);

void	*philo_routine(void *arg);
void	oracle_routine(t_oracle *oracle);

#endif
