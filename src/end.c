/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:13:57 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/10 12:44:11 by fclaus-g         ###   ########.fr       */
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
	printf(RED"MUTEX DESTRUIDOS\n"RESET);
}
void	ft_free_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->forks)
	{
		free(&data->fork[i]);
		i++;
	}
	//free(&data->mutedead);
	//free(&data->mutexmon);
	//free(&data->print);
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
	//ft_destroy_mutex(data);
	ft_free_mutex(data);
	ft_free_philos(data);
}

int	ft_checkend(t_data *data)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&data->endlock);
	end = data->end;
	pthread_mutex_unlock(&data->endlock);
	return (end);
}