/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:38:27 by braugust          #+#    #+#             */
/*   Updated: 2025/04/19 20:38:53 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_eat(t_philo *philo, t_data *data)
{
	bool	died;

	died = false;
	if (philo->next == philo)
	{
		pthread_mutex_lock(&philo->fork);
		display_move(philo, FORK);
		wait_or_check_dead(data->time_to_die, data);
		pthread_mutex_unlock(&philo->fork);
		return (true);
	}
	if (philo->id % 2 == 0 && philo->data->nb_philosophers % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		display_move(philo, FORK);
		pthread_mutex_lock(&philo->next->fork);
		display_move(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		display_move(philo, FORK);
		pthread_mutex_lock(&philo->fork);
		display_move(philo, FORK);
	}
	pthread_mutex_lock(&philo->key_mutex);
	philo->last_eat = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->key_mutex);
	display_move(philo, EAT);
	if (wait_or_check_dead(data->time_to_eat, data))
		died = true;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (died);
}

void join_threads(t_data *data)
{
    t_philo *temp = data->philo;
    int i = 0;
    
    while (i < data->nb_philosophers)
    {
        pthread_join(temp->pid, NULL);
        temp = temp->next;
        i++;
    }
}
