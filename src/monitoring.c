/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:05:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/16 13:28:04 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_checkeats(t_data *data)
{
	int	i;

	i = 0;
	if (data->eat_times != -1)
	{
		while (i < data->philos)
		{
			ft_philoate(&data->philo[i]);
			i++;
		}
		if (ft_check_finished(data) == 0)
			return (1);
	}
	return (0);
}

int	ft_checkdeath(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (ft_philo_died(&data->philo[i]))
		{
			ft_print_action("is died", &data->philo[i], data->philo[i].id);
			return (1);
		}
		i++;
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
void	ft_monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)(arg);
	while (1)
	{
		if (ft_checkdeath(data))
		{
			ft_setend(data);
			break ;
		}
		if (ft_checkeats(data))
		{
			ft_usleep(10);
			ft_setend(data);
			break ;
		}
	}	
}
