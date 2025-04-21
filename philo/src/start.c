/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:56:31 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 18:55:30 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	philo_init(t_data *data)
{
	int		i;
	t_philo	*new_philo;

	data->philo = NULL;
	if (pthread_mutex_init(&data->all_finished, NULL) != 0
		|| pthread_mutex_init(&data->smn_died, NULL) != 0)
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

int	list_length(t_philo *head)
{
	t_philo	*cur;
	int		n;

	cur = head;
	n = 0;
	if (!head)
		return (0);
	while (cur && (n == 0 || cur != head))
	{
		n++;
		cur = cur->next;
	}
	return (n);
}

void	launch_threads(t_data *data)
{
	t_philo	*cur;
	int		count;
	int		i;

	cur = data->philo;
	count = list_length(data->philo);
	i = 0;
	while (i < count)
	{
		if (pthread_create(&cur->pid, NULL, routine, cur) != 0)
			perror("pthread_create");
		cur = cur->next;
		i++;
	}
}

void	join_threads(t_data *data)
{
	t_philo	*cur;
	int		count;
	int		i;

	cur = data->philo;
	count = list_length(data->philo);
	i = 0;
	while (i < count)
	{
		pthread_join(cur->pid, NULL);
		cur = cur->next;
		i++;
	}
}

bool	wait_ms_or_terminate(long ms, t_data *data)
{
	long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		if (check_dead(data) || check_finished(data))
			return (true);
		usleep(1000);
	}
	return (false);
}
