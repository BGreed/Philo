/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:24:14 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 14:59:59 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool philo_init(t_data *data)
{
    int      i;
    t_philo *new_philo;

    data->philo = NULL;
    if (pthread_mutex_init(&data->all_finished, NULL) != 0
    || pthread_mutex_init(&data->smn_died,     NULL) != 0)
    return (false);
    
    data->died = false;
    i = 1;
    while (i <= data->nb_philosophers)
    {
        new_philo = ft_lstnew(i);
        if (!new_philo)
            return (false);
        new_philo->data = data;
        ft_lstaddback(&data->philo, new_philo);
        i++;
    }

    join_lst(&data->philo);

    return (true);
}

bool display_move(t_philo *philo, char *str)
{
    long t = get_time() - philo->data->start_time;

    pthread_mutex_lock(&philo->data->smn_died);
    if (!philo->data->died)
        printf("%ld %d %s\n", t, philo->id, str);
    pthread_mutex_unlock(&philo->data->smn_died);

    return false;
}

void *routine(void *arg)
{
    t_philo *philo = arg;
    t_data  *data  = philo->data;

    if (philo->id % 2 == 0)
        usleep(data->time_to_eat * 1000 / 2);

    while (1)
    {
        if (data->nb_must_eat > 0)
        {
            pthread_mutex_lock(&philo->key_mutex);
            if (philo->nb_meals >= data->nb_must_eat)
            {
                pthread_mutex_unlock(&philo->key_mutex);
                break;
            }
            pthread_mutex_unlock(&philo->key_mutex);
        }

        if (check_dead(data))
            break;

        if (ft_eat(philo, data))
            break;

        if (ft_sleep(philo, data))
            break;

        if (ft_think(philo, data))
            break;
    }
    return NULL;
}

bool monitoring(t_data *data)
{
    while (!check_dead(data) && !check_finished(data))
        usleep(1000);
    return true;
}

void free_philo(t_data *data)
{
    t_philo *cur;
    t_philo *next;

    if (!data || !data->philo)
        return;

    cut_circle(data);

    cur = data->philo;
    while (cur)
    {
        next = cur->next;
        pthread_mutex_destroy(&cur->fork);
        pthread_mutex_destroy(&cur->key_mutex);
        free(cur);
        cur = next;
    }

    pthread_mutex_destroy(&data->all_finished);
    pthread_mutex_destroy(&data->smn_died);

    data->philo = NULL;
}

int main(int ac, char **av)
{
    t_data data = {0};

    if (parse_args(ac, av, &data))
        return (1);

    data.start_time = get_time();
    if (!philo_init(&data))
        return (free_philo(&data), 1);

    launch_threads(&data);

    monitoring(&data);

    join_threads(&data);

    free_philo(&data);
    return 0;
}
