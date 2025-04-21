/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:31 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 15:00:08 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int list_length(t_philo *head)
{
    t_philo *cur = head;
    int      n   = 0;

    if (!head)
        return 0;
    while (cur && (n == 0 || cur != head))
    {
        n++;
        cur = cur->next;
    }
    return n;
}

void launch_threads(t_data *data)
{
    t_philo *cur   = data->philo;
    int      count = list_length(data->philo);
    int      i     = 0;

    while (i < count)
    {
        if (pthread_create(&cur->pid, NULL, routine, cur) != 0)
            perror("pthread_create");
        cur = cur->next;
        i++;
    }
}

void join_threads(t_data *data)
{
    t_philo *cur   = data->philo;
    int      count = list_length(data->philo);
    int      i     = 0;

    while (i < count)
    {
        pthread_join(cur->pid, NULL);
        cur = cur->next;
        i++;
    }
}

bool wait_ms_or_terminate(long ms, t_data *data)
{
    long start = get_time();

    while (get_time() - start < ms)
    {
        if (check_dead(data) || check_finished(data))
            return true;
        usleep(1000);
    }
    return false;
}
