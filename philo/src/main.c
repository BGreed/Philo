/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:24:14 by braugust          #+#    #+#             */
/*   Updated: 2025/04/21 20:00:02 by braugust         ###   ########.fr       */
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

bool	display_move(t_philo *philo, char *str)
{
	long	t;

	t = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->smn_died);
	if (!philo->data->died)
		printf("%ld %d %s\n", t, philo->id, str);
	pthread_mutex_unlock(&philo->data->smn_died);
	return (false);
}

bool	monitoring(t_data *data)
{
	while (!check_dead(data) && !check_finished(data))
		usleep(1000);
	return (true);
}

int	main(int ac, char **av)
{
	static t_data	data = {0};

	if (parse_args(ac, av, &data))
		return (1);
	data.start_time = get_time();
	if (!philo_init(&data))
		return (free_philo(&data), 1);
	launch_threads(&data);
	monitoring(&data);
	join_threads(&data);
	free_philo(&data);
	return (0);
}
