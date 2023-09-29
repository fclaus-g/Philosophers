/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:13:57 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/09/29 11:18:34 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->forks)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].muteat);
		i++;
	}
	pthread_mutex_destroy(&data->mutedead);
	pthread_mutex_destroy(&data->mutexmon);
}

void	ft_free_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		free(&data->philo[i]);
		i++;
	}
}


void	ft_end(t_data *data)
{
	ft_destroy_mutex(data);
	ft_free_philos(data);
	free(data);
}
