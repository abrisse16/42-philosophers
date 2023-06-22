/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:52:16 by abrisse           #+#    #+#             */
/*   Updated: 2022/10/26 17:30:10 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*quit_create(t_philo *philos, int err, size_t n)
{
	size_t	i;

	i = 0;
	if (err == ERR_MALLOC)
		printf("Error: malloc\n");
	else if (err == ERR_MUTEX)
		printf("Error: mutex\n");
	while (i < n)
	{
		pthread_mutex_destroy(&philos[i].mutex_eating);
		i++;
	}
	free(philos);
	return (NULL);
}

static void	fill_philos(t_data *data, t_philo *philos, int i)
{
		philos[i].time_of_death = data->start_time + data->time_to_die;
		philos[i].nbr_philo = data->nbr_philo;
		philos[i].mutex_msg = &data->mutex_msg;
		philos[i].mutex_simulation_stop = &data->mutex_simulation_stop;
		philos[i].simulation_stop = &data->simulation_stop;
		philos[i].start_time = data->start_time;
		philos[i].id = i + 1;
		philos[i].time_to_die = data->time_to_die;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		philos[i].meal_max = data->nbr_philo_must_eat;
		philos[i].meal_ate = 0;
		philos[i].fork[(i + 1) % 2] = &data->mutex_forks[i];
		philos[i].fork[i % 2] = &data->mutex_forks[(i + 1) % data->nbr_philo];
}

t_philo	*create_philos(t_data *data)
{
	size_t	i;
	t_philo	*philos;

	philos = (t_philo *) malloc(data->nbr_philo * sizeof(t_philo));
	if (!philos)
		return (quit_create(philos, ERR_MALLOC, 0));
	i = 0;
	data->start_time = get_time();
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&philos[i].mutex_eating, NULL) != 0)
			return (quit_create(philos, ERR_MUTEX, i));
		fill_philos(data, philos, i);
		i++;
	}
	return (philos);
}

static void	*quit_launch(t_data *data, int err, size_t n)
{
	size_t	i;

	i = 0;
	if (err == ERR_THREAD)
		printf("Error: thread\n");
	pthread_mutex_lock(&data->mutex_simulation_stop);
	data->simulation_stop = 1;
	pthread_mutex_unlock(&data->mutex_simulation_stop);
	while (i < n)
		pthread_detach(data->philos[i++].thread);
	return (NULL);
}

t_philo	*launch_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&activity, &data->philos[i]) != 0)
			return (quit_launch(data, ERR_THREAD, i));
		i++;
	}
	if (data->nbr_philo != 1)
	{
		if (pthread_create(&data->thread_monitoring, NULL,
				&monitoring, data) != 0)
			return (quit_launch(data, ERR_THREAD, i));
	}
	i = 0;
	pthread_join(data->thread_monitoring, NULL);
	while (i < data->nbr_philo)
		pthread_join(data->philos[i++].thread, NULL);
	return (data->philos);
}
