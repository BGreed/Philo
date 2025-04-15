/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:07:28 by braugust          #+#    #+#             */
/*   Updated: 2025/04/15 18:14:20 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (printf(ERR_ARG, av[0]), 1);
	while (i < ac)
	{
		if (!is_number(av[i]))
			return (printf(NEG_ARG), 1);
		i++;
	}
	data->nb_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = atoi(av[5]);
	else
		data->nb_must_eat = -1;
	if (data->nb_must_eat <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (printf(INF_ARG), 1);
	if (ac == 6 && data->nb_must_eat <= 0)
		return (printf(INF_ARG), 1);
	return (0);
}
