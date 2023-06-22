/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:52:44 by abrisse           #+#    #+#             */
/*   Updated: 2022/10/17 00:09:09 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*quit(pthread_mutex_t *forks, int err, size_t n)
{
	size_t	i;

	if (err == ERR_MALLOC)
		printf("Error: malloc\n");
	else if (err == ERR_MUTEX)
		printf("Error: mutex\n");
	if (forks)
	{
		i = 0;
		while (i < n)
			pthread_mutex_destroy(&forks[i++]);
		free (forks);
	}
	return (NULL);
}

pthread_mutex_t	*create_forks(unsigned int nbr_philo)
{
	pthread_mutex_t	*forks;
	size_t			i;

	forks = (pthread_mutex_t *)malloc(nbr_philo * sizeof(pthread_mutex_t));
	if (!forks)
		return (quit(NULL, ERR_MALLOC, 0));
	i = 0;
	while (i < nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (quit(forks, ERR_MUTEX, i));
		i++;
	}
	return (forks);
}

void	destroy_forks(pthread_mutex_t *forks, unsigned int nbr_philo)
{
	size_t	i;

	i = 0;
	while (i < nbr_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
