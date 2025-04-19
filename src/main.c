/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:24:14 by braugust          #+#    #+#             */
/*   Updated: 2025/04/19 03:07:46 by braugust         ###   ########.fr       */
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
    t_philo *node;

    data->philo = NULL;
    i = 0;
    while (i < data->nb_philosophers)
    {
        node = ft_lstnew(i + 1);
        if (!node)
            return (true);
        node->data = data;
        ft_lstaddback(&data->philo, node);
        i++;
    }
    join_lst(&data->philo);
    return (false);
}

bool	display_move(t_philo *philo, char *str)
{
	long	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->smn_died);
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->smn_died);
	return (false);
}

void	*routine(void *tmp)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)tmp;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(data->time_to_eat * 1000 / 2);
	while (1)
	{
		if (should_end(data))
            break;
		if (check_dead(data))
			break ;
		if (check_finished(data))
			break ;
		if (ft_eat(philo, data))
			break ;
		if (ft_sleep(philo, data))
			break ;
		if (ft_think(philo))
			break ;
	}
	return (NULL);
}

bool	monitoring(t_data *data)
{
	while (1)
	{
		if (check_dead(data))
			break ;
		if (check_finished(data))
			break ;
		data->philo = data->philo->next;
	}
	return (true);
}

void	free_philo(t_data *data)
{
	t_philo	*lst;
	t_philo	*temp;

	cut_circle(data);
	lst = data->philo;
	while (lst)
	{
		temp = lst->next;
		pthread_mutex_destroy(&(lst->fork));
		free(lst);
		lst = temp;
	}
	data->philo = NULL;
}

int main(int ac, char **av)
{
    static t_data data = {0};

	data.died = false;
    if (parse_args(ac, av, &data))
        return (1);
    pthread_mutex_init(&data.smn_died,   NULL);
    pthread_mutex_init(&data.all_finished, NULL);
    if (init_simulation(&data))
        return (1);
    while (!monitoring(&data))
        ;
    usleep(1000);
    free_philo(&data);
    pthread_mutex_destroy(&data.smn_died);
    pthread_mutex_destroy(&data.all_finished);
    return (0);
}
