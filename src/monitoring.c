/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:05:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/09/19 13:37:33 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_monitoring(void *arg)
{
	t_data	*data;
	int		c;

	data = (t_data *)arg;
	c = 0;
	while (c < data->philos)
	{
		if (data->dead == 1)
			ft_end(data);
		if ((data->philo[c].eat_times == data->eat_times) && c == data->philos)
			ft_end(data);//PENDIENTE DE REVISAR
	}
	return (NULL);
}


void	ft_end(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		free(&data->philo[i].thread);
		free(&data->philo[i]);
	}
}


