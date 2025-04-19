/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:24:14 by braugust          #+#    #+#             */
/*   Updated: 2025/04/19 20:38:07 by braugust         ###   ########.fr       */
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
    t_philo *temp;
    int i;

    i = 0;
    if (pthread_mutex_init(&data->all_finished, NULL) != 0 ||
        pthread_mutex_init(&data->smn_died, NULL) != 0)
        return (false);
    data->philo = NULL;
    while(i < data->nb_philosophers)
    {
        t_philo *new_philo = ft_lstnew(i + 1);
        if (!new_philo)
            return (false);
        new_philo->data = data;
        ft_lstaddback(&(data->philo), new_philo);
        i++;
    }
    join_lst(&(data->philo));
    temp = data->philo;
    i = 0;
    while (i < data->nb_philosophers)
    {
        if (pthread_create(&(temp->pid), NULL, routine, temp) != 0)
            return (false);
        temp = temp->next;
        i++;
    }
    
    return (true);
}

bool display_move(t_philo *philo, char *str)
{
    static bool someone_died = false;
    
    if (someone_died || check_dead(philo->data) || check_finished(philo->data))
        return (true);
    
    pthread_mutex_lock(&philo->data->smn_died);
    if (!someone_died)
    {
        printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, str);
    }
    pthread_mutex_unlock(&philo->data->smn_died);
    
    return (false);
}

void *routine(void *tmp)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *)tmp;
    data = philo->data;

    if (philo->id % 2 == 0)
        usleep(1000);  // Attente pour synchronisation initiale

    while (1)
    {
        // Vérifie si tous les philosophes ont mangé leur nombre de repas
        if (philo->nb_meals >= data->nb_must_eat && data->nb_must_eat > 0)
            break;  // Arrête le philosophe s'il a mangé suffisamment

        // Vérifie la mort ou si tous les philosophes ont fini de manger
        if (check_dead(data) || check_finished(data))
            break;

        // Continue le cycle de manger, dormir, penser
        if (ft_eat(philo, data))
            break;
        
        if (ft_sleep(philo, data))
            break;
        
        if (ft_think(philo, data))
            break;
    }
    return (NULL);
}

bool monitoring(t_data *data)
{
    while (1)
    {
        if (check_dead(data))
        {
            data->died = true;
            return (true);
        }
        if (check_finished(data))
        {
            data->died = true;
            return (true);
        }
        usleep(1000);
    }
    return (true);
}

void free_philo(t_data *data)
{
    t_philo *lst;
    t_philo *temp;
    
    if (!data || !data->philo)
        return;
    cut_circle(data);
    lst = data->philo;
    while (lst)
    {
        temp = lst->next;
        pthread_mutex_destroy(&lst->fork);
       pthread_mutex_destroy(&lst->key_mutex);
        free(lst);
        lst = temp;
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
    {
        free_philo(&data);
        return (1);
    }
    monitoring(&data);
    join_threads(&data);
    free_philo(&data);
    return (0);
}
