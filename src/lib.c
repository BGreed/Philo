/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:46:13 by braugust          #+#    #+#             */
/*   Updated: 2025/04/19 12:06:13 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_lstaddback(t_philo **lst, t_philo *new)
{
	t_philo	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

t_philo	*ft_lstnew(int id)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return (NULL);
	// if (pthread_mutex_init(&(new_node->fork), NULL) != 0)
	// 	return (NULL);
	new_node->id = id;
	new_node->ate = false;
	new_node->slept = false;
	new_node->nb_meals = 0;
	new_node->last_eat = get_time();
	if (pthread_mutex_init(&(new_node->fork), NULL) != 0)
		return (free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

void	join_lst(t_philo **head)
{
	t_philo	*temp;

	if (!head || !(*head))
		return ;
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = *head;
}

void	cut_circle(t_data *data)
{
	t_philo	*temp;

	if (!data || !data->philo)
		return ;
	temp = data->philo;
	while (temp->next != data->philo)
		temp = temp->next;
	temp->next = NULL;
}

bool check_dead(t_data *data)
{
    t_philo *temp;
    long current_time;
    static bool someone_died = false;
    
    if (someone_died)
        return (true);
    
    pthread_mutex_lock(&data->smn_died);
    current_time = get_time();
    temp = data->philo;
    for (int i = 0; i < data->nb_philosophers; i++)
    {
        if ((current_time - temp->last_eat) > data->time_to_die)
        {
            printf("%ld %d %s\n", current_time - data->start_time, temp->id, DIED);
            someone_died = true;
            pthread_mutex_unlock(&data->smn_died);
            return (true);
        }
        temp = temp->next;
    }
    pthread_mutex_unlock(&data->smn_died);
    return (false);
}

bool	ft_sleep(t_philo *philo, t_data *data)
{
	display_move(philo, SLEEP);
	if (wait_or_check_dead(data->time_to_sleep, data))
		return (true);
	philo->slept = true;
	return (false);
}

bool wait_or_check_dead(long ms, t_data *data)
{
    long start;

    start = get_time();
    while (get_time() - start < ms)
    {
        if (check_dead(data))
            return (true);
        usleep(1000);
    }
	if (should_end(data))
		return (true);
    return (false);
}

bool ft_think(t_philo *philo, t_data *data)
{
    if (check_dead(data))
        return (true);
    
    display_move(philo, THINK);
    usleep(1000);
    return (false);
}

bool check_finished(t_data *data)
{
    t_philo *temp;
    int count;

    if (!data || data->nb_must_eat == -1)
        return (false);
    
    pthread_mutex_lock(&data->all_finished);
    count = 0;
    temp = data->philo;
    for (int i = 0; i < data->nb_philosophers; i++)
    {
        if (temp->nb_meals >= data->nb_must_eat)
            count++;
        temp = temp->next;
    }
    
    bool result = false;
    if (count == data->nb_philosophers)
        result = true;
    
    pthread_mutex_unlock(&data->all_finished);
    return (result);
}