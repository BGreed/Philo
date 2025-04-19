/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:38:27 by braugust          #+#    #+#             */
/*   Updated: 2025/04/19 02:57:56 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

bool ft_eat(t_philo *philo, t_data *data)
{
    bool    died = false;

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
    philo->last_eat = get_time();
    display_move(philo, EAT);
    philo->nb_meals++;
    if (wait_or_check_dead(data->time_to_eat, data))
        died = true;
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->next->fork);
    return (died);
}
