/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:19:31 by abrisse           #+#    #+#             */
/*   Updated: 2022/10/17 00:09:17 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int	take_alert_sleep(time_t duration, t_philo *philo)
{
	time_t	time_to_wake_up;

	time_to_wake_up = get_time() + duration;
	while (get_time() < time_to_wake_up)
	{
		if (check_dead(philo))
			break ;
		usleep(100);
	}
	return (0);
}
