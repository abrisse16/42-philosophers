/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:32:48 by abrisse           #+#    #+#             */
/*   Updated: 2022/10/26 17:32:02 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(philo->mutex_simulation_stop);
	if (*(philo->simulation_stop) == 1)
		ret = 1;
	pthread_mutex_unlock(philo->mutex_simulation_stop);
	return (ret);
}

int	someone_dying(t_philo *philo)
{
	time_t	time_actual;

	time_actual = get_time();
	if (time_actual > philo->time_of_death)
	{
		pthread_mutex_lock(philo->mutex_simulation_stop);
		*(philo->simulation_stop) = 1;
		pthread_mutex_unlock(philo->mutex_simulation_stop);
		pthread_mutex_lock(philo->mutex_msg);
		printf("%ld %d %s\n", get_time() - philo->start_time, philo->id,
			"died");
		pthread_mutex_unlock(philo->mutex_msg);
		pthread_mutex_unlock(&philo->mutex_eating);
		return (1);
	}
	return (0);
}

static int	each_philo(t_philo *philo, int *everyone_ate)
{
	pthread_mutex_lock(&philo->mutex_eating);
	if (someone_dying(philo))
		return (1);
	if (philo->meal_ate < philo->meal_max)
		*everyone_ate = 0;
	pthread_mutex_unlock(&philo->mutex_eating);
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	size_t	i;
	int		everyone_ate;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		everyone_ate = 1;
		while (i < data->nbr_philo)
			if (each_philo(&data->philos[i++], &everyone_ate))
				return (NULL);
		if (everyone_ate && data->nbr_philo_must_eat != 0)
		{
			pthread_mutex_lock(&data->mutex_simulation_stop);
			data->simulation_stop = 1;
			pthread_mutex_unlock(&data->mutex_simulation_stop);
			return (NULL);
		}
	}
	return (NULL);
}
