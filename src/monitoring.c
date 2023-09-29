/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:05:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/09/29 13:35:24 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_checkeats(t_data *data)
{
	if (data->eat_times != -1)
	{
		if (data->philo[0].eat_times == data->eat_times)
		{
			data->finished = 1;
			return (1);
		}
	}
	while (1)
	{
		if (data->finished == data->philos - 1)
			return (1);
	}
	return (0);
}
int	ft_checkdeath(t_data *data)
{
	int	i;
	// if (pthread_mutex_init(&data->muteat, NULL) != 0)
	// 	return (ft_werror("Error mutexmon\n", 2), 0);
	printf(RED"CHECKDEATH data->dead = %d\n"RESET, data->dead);
	while (1)
	{
		i = 0;
		while (i < data->philos)
		{
			if (pthread_mutex_lock(&data->philo[i].muteat) != 0)
				return (ft_werror("Error lock mutexmon", 2), 0);
			printf(RED"CHECKDEATH get time - last eat = %ld t_die = %d, total = %ld\n"RESET, ft_get_time() - data->philo[i].last_eat, data->t_die, ft_get_time() - data->philo[i].last_eat);
			if ((ft_get_time() - data->philo[i].last_eat ) >= data->t_die)
			{
				data->dead = 1;
				return (1);
			}
			if (pthread_mutex_unlock(&data->philo[i].muteat) != 0)
				return (ft_werror("Error unlock mutexmon", 2), 0);
			i++;
		}
	}
	return (0);
}

/*
	*ft_monitoring viniendo de 
	*pthread_create(&data->monitor, NULL, (void *)&ft_monitoring, &data)
	*recibe doble puntero de arg (**arg) para acceder a los datos
	de la estructura de forma correcta de otra manera los datos recibidos 
	serian direcciones de memoria
*/
void	ft_monitoring(void **arg)
{
	t_data	*data;
	//int		i;

	data = (t_data *)(*arg);
	while (1)
	{
		if (ft_checkdeath(data))
		{
			printf(RED"ALERTA DE MUERTE\n"RESET);
			ft_end(data);
			//break;
		}
		if (ft_checkeats(data))
		{
			printf(RED"ALERTA DE COMIDA\n"RESET);
			ft_end(data);
			break;
		}
	}
	
}





