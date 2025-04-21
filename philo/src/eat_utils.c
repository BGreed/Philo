/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:01:34 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 20:02:08 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	handle_single_philosopher(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->fork);
	display_move(philo, FORK);
	wait_ms_or_terminate(data->time_to_die, data);
	pthread_mutex_unlock(&philo->fork);
	return (true);
}

bool	perform_eating(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
		eat_even_philosopher(philo);
	else
		eat_odd_philosopher(philo);
	return (finalize_eating(philo, data));
}

void	eat_even_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	display_move(philo, FORK);
	pthread_mutex_lock(&philo->next->fork);
	display_move(philo, FORK);
}

void	eat_odd_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	display_move(philo, FORK);
	pthread_mutex_lock(&philo->fork);
	display_move(philo, FORK);
}
