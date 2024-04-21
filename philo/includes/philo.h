/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:35:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/21 19:00:34 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <sys/errno.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include "colors.h"

# define RIGHT 0
# define LEFT 1
# define TAKE 1
# define LEAVE 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DEATH 6
# define FED 7
# define SATIATED 8
# define SET_FED 9
# define RESET_FED 10
# define SET_DEATH 11

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
	pthread_mutex_t	table_mutex;
	struct s_table	*main;
}	t_table;

typedef struct s_philo
{
	int				index;
	pthread_mutex_t	*fork[2];
	int				fork_id[2];
	int				meal_count;
	long			last_meal;
	int				death;
	pthread_mutex_t	philo_mutex;
	t_table			table;
}	t_philo;

typedef struct s_oracle
{
	long	current_time;
	int		dinner_ended;
	int		satiated_philos;
	t_philo	*philos;
	t_table	table;
}	t_oracle;

/*	Initialize datas	*/
void	init_table(t_table *table, char **argv);
void	init_oracle(t_oracle *oracle, t_table table);
/*	Philo	*/
void	set_death(t_philo *philo);
void	set_fed(t_philo *philo);
/*	Info	*/
long	gettime(void);
int		is_death(t_philo *philo);
int		is_fed(t_philo *philo);
int		is_satiated(t_philo *philo);
void	precise_usleep(long time_to_wait);
/*	Print action of philo	*/
void	print_take(t_philo *philo, int fork_id);
void	print_leave(t_philo *philo, int fork_id);
void	print_eat(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_think(t_philo *philo);
/*	Routine	*/
void	dinner(t_oracle *oracle);
void	*philo_routine(void *arg);
void	oracle_routine(t_oracle *oracle);

#endif
