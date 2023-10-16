/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:13:57 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/16 09:42:33 by fclaus-g         ###   ########.fr       */
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
		i++;
	}
	pthread_mutex_destroy(&data->eatlock);
	pthread_mutex_destroy(&data->deadlock);
	pthread_mutex_destroy(&data->printlock);
	pthread_mutex_destroy(&data->endlock);
}

void	ft_end(t_data *data)
{
	ft_destroy_mutex(data);
	free(data->fork);
	free(data->thread);
	free(data->philo);
}
