/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:31 by braugust          #+#    #+#             */
/*   Updated: 2025/04/19 18:01:02 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool should_end(t_data *data)
{
    if (data->died)
        return (true);
    if (data->nb_must_eat > 0 && check_finished(data))
        return (true);
    return (false);
}

void waiter(t_philo *philo)
{
    long last_meal;
    long time_to_die;

    pthread_mutex_lock(&philo->key_mutex);
    last_meal = philo->last_eat;
    pthread_mutex_unlock(&philo->key_mutex);
    time_to_die = philo->data->time_to_die;
    while ((get_time() - last_meal) < time_to_die - 10)
        usleep(100);
}
