/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:12:41 by abrisse           #+#    #+#             */
/*   Updated: 2022/10/26 17:20:48 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	speak(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->mutex_msg);
	pthread_mutex_lock(philo->mutex_simulation_stop);
	if (*(philo->simulation_stop) != 1)
		printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->mutex_msg);
	pthread_mutex_unlock(philo->mutex_simulation_stop);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	speak(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork[1]);
	speak(philo, "has taken a fork");
	speak(philo, "is eating");
	pthread_mutex_lock(&philo->mutex_eating);
	philo->time_of_death = get_time() + philo->time_to_die;
	philo->meal_ate += 1;
	pthread_mutex_unlock(&philo->mutex_eating);
	take_alert_sleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_unlock(philo->fork[1]);
}

void	*alone(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	speak(philo, "has taken a fork");
	take_alert_sleep(philo->time_to_die, philo);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, "died");
	pthread_mutex_unlock(philo->fork[0]);
	return (NULL);
}

void	*activity(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->nbr_philo == 1)
		return (alone(philo));
	if (philo->id % 2)
		take_alert_sleep(philo->time_to_eat, philo);
	while (check_dead(philo) == 0)
	{
		eat(philo);
		speak(philo, "is sleeping");
		take_alert_sleep(philo->time_to_sleep, philo);
		speak(philo, "is thinking");
	}
	return (NULL);
}
