/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:24:14 by braugust          #+#    #+#             */
/*   Updated: 2025/04/15 18:35:06 by braugust         ###   ########.fr       */
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



bool	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->philo)
	{
		ft_lstaddback(data->philo, ft_lstnew(i));
		i++;
	}
	join_lst();
}

bool	display_move(t_philo *philo, char *str)
{	
	printf("%d %s",philo->id, str);
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	// check if pair ou impair
	while (1)
	{
		if (check_dead())
			break ;
		if (check_finished())
			break ;
		if (eat())
			break ;
		if (sleep())
			break ;
		if (think())
			break ;
	}
}
bool	monitoring(t_data *data)
{
	while (1)
	{
		if (check_dead())
			break ;
		if (check_finished())
			break ;
		data->philo = data->philo->next;
	}
	return 1
}

void	free_philo(t_data *data)
{
	cut_circle();
	while (lst)
	{
		// free node
		// destroy mutex
		lst = lst->new;
	}
	return (0);
}

int	main(int ac, char **av)
{
	static t_data	data = {0};

	if (parse_args(ac, av, &data))
		return (1);
	if (philo_init(&data))
		return (1);
	while (1)
	{
		if (monitoring(&data))
			break ;
	}
	free_philo();
}
