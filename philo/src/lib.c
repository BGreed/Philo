/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:46:13 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 18:54:40 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int		n;
	int		result;
	size_t	i;

	i = 0;
	n = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if (n < 0)
		return (-result);
	else
		return (result);
}

void	ft_lstaddback(t_philo **lst, t_philo *new)
{
	t_philo	*cur;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		cur = *lst;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

t_philo	*ft_lstnew(int id)
{
	t_philo	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->id = id;
	new->ate = false;
	new->slept = false;
	new->nb_meals = 0;
	new->last_eat = get_time();
	if (pthread_mutex_init(&new->fork, NULL) != 0
		|| pthread_mutex_init(&new->key_mutex, NULL) != 0)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
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
