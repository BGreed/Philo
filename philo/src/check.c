/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:52:39 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 19:21:10 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_one_dead(t_philo *cur, long current_time, t_data *data)
{
	pthread_mutex_lock(&cur->key_mutex);
	if (current_time - cur->last_eat > data->time_to_die)
	{
		pthread_mutex_unlock(&cur->key_mutex);
		pthread_mutex_lock(&data->smn_died);
		if (!data->died)
		{
			data->died = true;
			printf("%ld %d %s\n", current_time - data->start_time, cur->id,
				DIED);
		}
		pthread_mutex_unlock(&data->smn_died);
		return (true);
	}
	pthread_mutex_unlock(&cur->key_mutex);
	return (false);
}

bool	check_dead(t_data *data)
{
	long	current_time;
	t_philo	*cur;

	if (!data || !data->philo)
		return (false);
	if (data->died)
		return (true);
	current_time = get_time();
	cur = data->philo;
	while (1)
	{
		if (check_one_dead(cur, current_time, data))
			return (true);
		cur = cur->next;
		if (cur == data->philo)
			break ;
	}
	return (data->died);
}

bool	check_finished(t_data *data)
{
	t_philo	*cur;
	int		count;
	int		target;

	count = 0;
	target = data->nb_must_eat;
	if (target < 0)
		return (false);
	cur = data->philo;
	while (cur)
	{
		pthread_mutex_lock(&cur->key_mutex);
		if (cur->nb_meals >= target)
			count++;
		pthread_mutex_unlock(&cur->key_mutex);
		cur = cur->next;
		if (cur == data->philo)
			break ;
	}
	return (count == data->nb_philosophers);
}
