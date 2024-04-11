/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:43:03 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/11 17:03:27 by mvelazqu         ###   ########.fr       */
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

# define RIGHT 42
# define LEFT 24
# define DEATH 12
# define SATIATED 21

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

typedef	struct	s_table
{
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				minimum_meals;
	long			starting_time;
	struct s_table	*main;
	pthread_mutex_t	table_mutex;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
}	t_table;

typedef	struct	s_philo
{
	int				index;
	void			*id;
	long			current_time;
	int				current_meals;
	int				fed;
	int				satiated;
	int				death;
	pthread_mutex_t	philo_mutex;
	t_table			table;
}	t_philo;

typedef struct	s_oracle
{
	t_table	table;
	t_philo	*philo_sheet;
	long	current_time;
	int		ended_dinner;
}	t_oracle;

void	init_table(t_table *table, char **argv);
void	init_philo(t_philo *philo, int index, t_table *table);
void	init_oracle(t_oracle *oracle, t_table *table);
void	free_table(t_table *table);
int		is_death(t_philo *data);
int		is_fed(t_philo *data);
void	start_dinner(t_oracle *oracle);
long	gettime(void);
t_table	parser_input(char **argv);
void	take_forks(t_philo *dt, pthread_mutex_t *rfork, pthread_mutex_t *lfork);
void	eat_meal(t_philo *data);
void	leave_forks(t_philo *dt, pthread_mutex_t *rfork,
			pthread_mutex_t *lfork);
void	sleep_and_think(t_philo *data);





//t_philo_data		parser_input(char **argv);
void				free_buff_of_buff(void **buffer);
pthread_t			**create_philosophers(int amount);
pthread_mutex_t		**create_forks(int amount);
t_data				*create_data(void *id, t_philo_data philo_dt,
		pthread_t **philos, pthread_mutex_t **forks);
//void				start_dinner(t_philo_data data);
int					find_index_dir(void *dir, void **array_dir);

#endif
