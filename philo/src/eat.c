/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:38:27 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 20:02:05 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	finalize_eating(t_philo *philo, t_data *data)
{
	bool	terminated;

	terminated = false;
	pthread_mutex_lock(&philo->key_mutex);
	philo->last_eat = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->key_mutex);
	display_move(philo, EAT);
	if (wait_ms_or_terminate(data->time_to_eat, data))
		terminated = true;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	if (check_dead(data) || check_finished(data))
		terminated = true;
	return (terminated);
}

bool	ft_eat(t_philo *philo, t_data *data)
{
	bool	terminated;

	terminated = false;
	if (data->nb_philosophers == 1)
	{
		terminated = handle_single_philosopher(philo, data);
	}
	else if (check_dead(data) || check_finished(data))
	{
		terminated = true;
	}
	else if (data->nb_must_eat > 0 && philo->nb_meals >= data->nb_must_eat)
	{
		terminated = true;
	}
	else
	{
		terminated = perform_eating(philo, data);
	}
	return (terminated);
}
