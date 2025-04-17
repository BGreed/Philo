/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:46:13 by braugust          #+#    #+#             */
/*   Updated: 2025/04/17 19:24:12 by braugust         ###   ########.fr       */
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

bool	check_dead(t_data *data)
{
	long	current_time;
	t_philo	*temp;

	if (!data || !data->philo)
		return (false);
	current_time = get_time();
	temp = data->philo;
	while (1)
	{
		if ((current_time - temp->last_eat) > data->time_to_die)
		{
			pthread_mutex_lock(&data->smn_died);
			printf("%ld %d %s\n", current_time, temp->id, DIED);
			pthread_mutex_unlock(&data->smn_died);
			return (true);
		}
		temp = temp->next;
		if (temp == data->philo)
			break ;
	}
	return (false);
}


bool	ft_sleep(t_philo *philo, t_data *data)
{
	long	start;

	display_move(philo, SLEEP);
	start = get_time();
	while (get_time() - start < data->time_to_sleep)
	{
		if (check_dead(data))
			return (true);
		usleep(1000);
	}
	philo->slept = true;
	return (false);
}
