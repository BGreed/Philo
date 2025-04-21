/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:35:07 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 20:18:52 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_think(t_philo *philo, t_data *data)
{
	if (check_dead(data) || check_finished(data))
		return (true);
	display_move(philo, THINK);
	usleep(1000);
	return (false);
}

bool	ft_sleep(t_philo *philo, t_data *data)
{
	long	start;

	if (check_dead(data) || check_finished(data))
		return (true);
	display_move(philo, SLEEP);
	start = get_time();
	while (get_time() - start < data->time_to_sleep)
	{
		if (check_dead(data) || check_finished(data))
			return (true);
		usleep(1000);
	}
	philo->slept = true;
	return (false);
}

int	check_meals_limit(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->key_mutex);
	if (philo->nb_meals >= data->nb_must_eat)
	{
		pthread_mutex_unlock(&philo->key_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->key_mutex);
	return (0);
}

int	execute_philo_routine(t_philo *philo, t_data *data)
{
	if (ft_eat(philo, data))
		return (1);
	if (ft_sleep(philo, data))
		return (1);
	if (ft_think(philo, data))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(data->time_to_eat * 1000 / 2);
	while (1)
	{
		if (data->nb_must_eat > 0)
		{
			if (check_meals_limit(philo, data))
				break ;
		}
		usleep(1000);
		if (check_dead(data))
			break ;
		if (execute_philo_routine(philo, data))
			break ;
	}
	return (NULL);
}
