/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:18:46 by abrisse           #+#    #+#             */
/*   Updated: 2022/10/16 19:54:36 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atoi(const char *str)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	return (sign * value);
}

static int	check_int(char *str)
{
	if (ft_atoi(str) > INT_MAX || ft_atoi(str) < INT_MIN)
		return (0);
	if (ft_atoi(str) == 0)
		return (0);
	return (1);
}

static int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	get_data(int ac, char **av, t_data *data)
{
	size_t	i;

	i = ac;
	memset(data, 0, sizeof(t_data));
	if (ac < 5 || ac > 6)
		return (printf(STR_ARG));
	while (--i)
		if (!check_number(av[i]) || !check_int(av[i]))
			return (printf("Error: invalid arguments\n"));
	data->nbr_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nbr_philo_must_eat = 0;
	if (ac == 6)
		data->nbr_philo_must_eat = ft_atoi(av[5]);
	return (0);
}
