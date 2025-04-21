/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:22:43 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 14:39:05 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_ARG "Usage:%s nb_philo time_to_die time_to_eat time_to_sleep\n"
# define NEG_ARG "Error: All args must be positive numbers.\n"
# define INF_ARG "Error: All values of philos must be greater than zero.\n"
# define FORK "has taken a fork"
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIED "died"

typedef struct s_philo
{
	int				id;
	bool			ate;
	bool			slept;
	int				nb_meals;
	long			last_eat;
	pthread_t		pid;
	pthread_mutex_t	fork;
	pthread_mutex_t	key_mutex;
	struct s_data	*data;
	struct s_philo	*next;
}					t_philo;

typedef struct s_data
{
	int				nb_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int             time_to_think;
	int				nb_must_eat;
	long			start_time;
	bool			died;
	t_philo			*philo;
	pthread_mutex_t	all_finished;
	pthread_mutex_t	smn_died;
}					t_data;

// lib

int					ft_atoi(const char *str);
void				ft_lstaddback(t_philo **lst, t_philo *new);
t_philo				*ft_lstnew(int id);
long				get_time(void);
void				join_lst(t_philo **head);
void				cut_circle(t_data *data);
bool				check_dead(t_data *data);
bool				ft_sleep(t_philo *philo, t_data *data);
bool				check_finished(t_data *data);
bool				wait_or_check_dead(long ms, t_data *data);
bool				ft_think(t_philo *philo, t_data *data);
bool				check_finished(t_data *data);
// main

bool				display_move(t_philo *philo, char *str);
void				*routine(void *tmp);
bool				philo_init(t_data *data);

// parsing

int					parse_args(int ac, char **av, t_data *data);

// eat

bool				ft_eat(t_philo *philo, t_data *data);
void				join_threads(t_data *data);
void				waiter(t_philo *philo);

// start

int  list_length(t_philo *head);
void launch_threads(t_data *data);
void join_threads(t_data *data);
bool wait_ms_or_terminate(long ms, t_data *data);


#endif