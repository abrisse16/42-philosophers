/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:01:15 by abrisse           #+#    #+#             */
/*   Updated: 2022/10/17 00:06:06 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define ERR_MALLOC 0
# define ERR_MUTEX 1
# define ERR_THREAD 2

# define STR_ARG	"Error: invalid number of arguments\n\
Expected : ./philo <number_of_philosophers> <time_to_die> (ms) \
<time_to_eat> (ms) <time_to_sleep> (ms) \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_philo
{
	pthread_mutex_t	mutex_eating;
	time_t			time_of_death;
	unsigned int	nbr_philo;
	unsigned int	id;
	pthread_mutex_t	*mutex_msg;
	pthread_mutex_t	*mutex_simulation_stop;
	int				*simulation_stop;
	time_t			start_time;
	unsigned int	meal_max;
	unsigned int	meal_ate;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	pthread_t		thread;
	pthread_mutex_t	*(fork[2]);
}	t_philo;

typedef struct s_data
{
	unsigned int	nbr_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nbr_philo_must_eat;
	time_t			start_time;
	pthread_mutex_t	mutex_simulation_stop;
	int				simulation_stop;
	pthread_mutex_t	mutex_msg;
	t_philo			*philos;
	pthread_mutex_t	*mutex_forks;
	pthread_t		thread_monitoring;
}	t_data;

/* main.c */
void			*ft_quit(int err);
void			*create_global_mutex(t_data *data);
int				free_data(t_data *data, int ret);

/* parsing.c */
int				get_data(int ac, char **av, t_data *data);

/* philosophers.c */
t_philo			*create_philos(t_data *data);
t_philo			*launch_philos(t_data *data);
void			free_philos(t_philo *philos, unsigned int nbr_philo);

/* activity.c */
void			eat(t_philo *philo);
void			*activity(void *arg);

/* monitoring.c */
int				check_dead(t_philo *philo);
void			*monitoring(void *arg);

/* utils.c */
time_t			get_time(void);
int				take_alert_sleep(time_t duration, t_philo *philo);

/* forks.c */
pthread_mutex_t	*create_forks(unsigned int nbr_philo);
void			destroy_forks(pthread_mutex_t *forks, unsigned int nbr_philo);

#endif
