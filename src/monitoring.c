/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:05:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/09/22 13:20:11 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_monitoring(void *arg)
{
	t_data	data;
	int		i;

	data = *(t_data *)arg;
	while (data.dead == 0)
	{
		i = -1;
		while (++i < data.philos)
		{
			pthread_mutex_lock(data.philo[i].print);
			printf("last eat philo[%d] = %d, tiempo actual = %ld\n", i, data.philo[i].last_eat, ft_get_time());
			pthread_mutex_unlock(data.philo[i].print);
			if (ft_timedif(data.philo[i].last_eat, ft_get_time()) > data.t_die)
			{
				data.dead = 1;
				printf(RED"ALGUIEN HA MUERTO\n"RESET);
				
				//ft_end(data);
				exit(1);
			}
			ft_print_action("ha muerto\n", &data.philo[i], data.philo[i].id);
			if (data.philo[i].eat_times == data.eat_times)
			{
				data.finished++;
			}	
		}
	}
	return (NULL);
}


void	ft_end(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		//pthread_mutex_destroy(&data->fork[i]);
		//free(&data->philo[i].thread);
		free(&data->philo[i]);
	}
	free(data);
}


