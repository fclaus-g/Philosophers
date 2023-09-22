/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:05:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/09/22 18:04:01 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_monitoring(void *arg)
{
	t_data	*data;
	int	i;

	data = (t_data *)arg;
	data->mutexmon = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data->mutexmon, NULL) != 0)
		ft_werror("Error mutex monitor", 2);
	while (1)
	{
		i = -1;
		while (++i < data->philos)
		{
			if (data->philo[i].last_eat - ft_get_time() > data->t_die)
			{
				data->dead = 1;
				ft_print_action("MUERTO MORIO\n", &data->philo[i], data->philo[i].id);
				break ;
			}
		}
	}
	pthread_mutex_destroy(data->mutexmon);
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


