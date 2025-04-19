/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:38:27 by braugust          #+#    #+#             */
/*   Updated: 2025/04/19 12:05:39 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo.h"

// bool ft_eat(t_philo *philo, t_data *data)
// {
//     bool    died = false;

//     if (philo->id % 2 == 0)
//     {
//         pthread_mutex_lock(&philo->fork);
//         display_move(philo, FORK);
//         pthread_mutex_lock(&philo->next->fork);
//         display_move(philo, FORK);
//     }
//     else
//     {
//         pthread_mutex_lock(&philo->next->fork);
//         display_move(philo, FORK);
//         pthread_mutex_lock(&philo->fork);
//         display_move(philo, FORK);
//     }
//     philo->last_eat = get_time();
//     display_move(philo, EAT);
//     philo->nb_meals++;
//     if (wait_or_check_dead(data->time_to_eat, data))
//         died = true;
//     pthread_mutex_unlock(&philo->fork);
//     pthread_mutex_unlock(&philo->next->fork);
//     return (died);
// }


bool ft_eat(t_philo *philo, t_data *data)
{
    t_philo *next_philo;

    if (check_dead(data) || check_finished(data))
        return (true);
    next_philo = philo->next;
    if (philo->id < next_philo->id)
    {
        pthread_mutex_lock(&philo->fork);
        display_move(philo, FORK);
        pthread_mutex_lock(&next_philo->fork);
        display_move(philo, FORK);
    }
    else
    {
        pthread_mutex_lock(&next_philo->fork);
        display_move(philo, FORK);
        pthread_mutex_lock(&philo->fork);
        display_move(philo, FORK);
    }
    if (data->nb_philosophers == 1)
    {
        pthread_mutex_unlock(&philo->fork);
        usleep(data->time_to_die * 1000);
        return (check_dead(data));
    }
    display_move(philo, EAT);
    philo->last_eat = get_time();
    philo->ate = true;
    philo->nb_meals++;
    long start = get_time();
    while (get_time() - start < data->time_to_eat)
    {
        if (check_dead(data) || check_finished(data))
        {
            pthread_mutex_unlock(&philo->fork);
            pthread_mutex_unlock(&next_philo->fork);
            return (true);
        }
        usleep(1000);
    }
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&next_philo->fork);
    return (false);
}

void join_threads(t_data *data)
{
    t_philo *temp;
    int i;
    
    if (!data || !data->philo)
        return;
    
    temp = data->philo;
    for (i = 0; i < data->nb_philosophers; i++)
    {
        pthread_join(temp->pid, NULL);
        temp = temp->next;
    }
}
