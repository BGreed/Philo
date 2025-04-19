/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:31 by braugust          #+#    #+#             */
/*   Updated: 2025/04/19 02:57:08 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int init_simulation(t_data *data)
{
    t_philo *head;
    t_philo *tmp;
    int      i;
    int      err;

    if (philo_init(data))
        return (1);
    head = data->philo;
    tmp  = head;
    data->start_time = get_time();
    i = 0;
    while (i < data->nb_philosophers)
    {
        err = pthread_create(&tmp->pid, NULL, routine, tmp);
        if (err != 0)
            return (printf("Error: pthread_create failed\n"), 1);
        pthread_detach(tmp->pid);
        tmp = tmp->next;
        i++;
    }
    return (0);
}

void print_death_once(t_philo *philo, t_data *data)
{
    pthread_mutex_lock(&data->smn_died);
    if (!data->died)
    {
        long death_time = philo->last_eat + data->time_to_die;
        long ts         = death_time - data->start_time;
        printf("%ld %d %s\n", ts, philo->id, DIED);
        data->died = true;
    }
    pthread_mutex_unlock(&data->smn_died);
}


bool should_end(t_data *data)
{
    if (data->died)
        return (true);
    if (data->nb_must_eat > 0 && check_finished(data))
        return (true);
    return (false);
}
