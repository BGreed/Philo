/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:38:27 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 15:00:29 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool ft_eat(t_philo *philo, t_data *data)
{
    bool terminated = false;

    if (data->nb_philosophers == 1)
        {
            pthread_mutex_lock(&philo->fork);
            display_move(philo, FORK);
            wait_ms_or_terminate(data->time_to_die, data);
            pthread_mutex_unlock(&philo->fork);
            return true;
        }
    if (check_dead(data) || check_finished(data))
        return true;
    if (data->nb_must_eat > 0)
    {
        pthread_mutex_lock(&philo->key_mutex);
        if (philo->nb_meals >= data->nb_must_eat)
        {
            pthread_mutex_unlock(&philo->key_mutex);
            return true;
        }
        pthread_mutex_unlock(&philo->key_mutex);
    }
    if (philo->id % 2 == 0)
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

    if (wait_ms_or_terminate(data->time_to_eat, data))
        terminated = true;

    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->next->fork);

    if (check_dead(data) || check_finished(data))
        terminated = true;

    return terminated;
}


bool ft_think(t_philo *philo, t_data *data)
{
    if (check_dead(data) || check_finished(data))
        return true;
    display_move(philo, THINK);
    usleep(1000);
    return false;
}