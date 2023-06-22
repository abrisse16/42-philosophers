/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:54:14 by abrisse           #+#    #+#             */
/*   Updated: 2022/10/17 00:09:59 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_quit(int err)
{
	if (err == ERR_MALLOC)
		printf("Error: malloc\n");
	else if (err == ERR_MUTEX)
		printf("Error: mutex\n");
	return (NULL);
}

void	*create_global_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_msg, NULL) != 0)
		return (ft_quit(ERR_MUTEX));
	if (pthread_mutex_init(&data->mutex_simulation_stop, NULL) != 0)
		return (ft_quit(ERR_MUTEX));
	data->simulation_stop = 0;
	return (data);
}

int	free_data(t_data *data, int ret)
{
	if (&(data->mutex_simulation_stop))
		pthread_mutex_destroy(&data->mutex_simulation_stop);
	if (&(data->mutex_msg))
		pthread_mutex_destroy(&data->mutex_msg);
	destroy_forks(data->mutex_forks, data->nbr_philo);
	free_philos(data->philos, data->nbr_philo);
	return (ret);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (get_data(ac, av, &data) != 0)
		return (1);
	data.mutex_forks = create_forks(data.nbr_philo);
	if (!data.mutex_forks)
		return (1);
	data.philos = create_philos(&data);
	if (!data.philos)
		return (free_data(&data, 1));
	if (!create_global_mutex(&data))
		return (free_data(&data, 1));
	if (!launch_philos(&data))
		return (free_data(&data, 1));
	return (free_data(&data, 0));
}
