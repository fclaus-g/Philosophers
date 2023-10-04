/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:05:41 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/04 13:32:45 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_checkeats(t_data *data)
{
	int	i;
	//int eats;

	while (1)
	{
		
		if (data->eat_times != -1)
		{
			i = 0;
			while (i < data->philos)
			{
				pthread_mutex_lock(&data->philo[i].muteat);
				if (data->philo[i].eat_times == data->eat_times)
				{
					printf(YELLOW"i = %d\n", i);
					printf(ORANGE"COMIDA COMPLETA philo %d, times %d \n", data->philo[i].id, data->eat_times);
					data->finished++;
				}
				pthread_mutex_unlock(&data->philo[i].muteat);
				i++;
			}
		}
		pthread_mutex_lock(&data->philo[i].muteat);
		if (data->finished == data->philos)
		{
			printf(YELLOW"COMIDA COMPLETA philo %d, times %d \n"RESET, data->finished, data->eat_times);
			return (pthread_mutex_unlock(&data->philo[i].muteat), 1);
		}	
	}
	return (0);
}

int	ft_philo_died(t_philo *philo)
{
	time_t ate;
	time_t dietime;

	pthread_mutex_lock(&philo->muteat);
	ate = philo->last_eat;
	dietime = philo->data->t_die;
	pthread_mutex_unlock(&philo->muteat);
	//printf("%d, %ld ,%d\n", philo->id, last_eat, philo->eat_times);
	if ((ft_get_time() - ate) >= dietime + philo->data->start_time && philo->eating == 0)
	{
		printf(RED"last eat = %ld ate= %ld now = %ld resta = %ld\n", philo->last_eat, ate, ft_get_time(), ft_get_time() - philo->last_eat);
		return (1);
	}
	return (0);
}

int	ft_checkdeath(t_data *data)
{
	int	i;
	// if (pthread_mutex_init(&data->muteat, NULL) != 0)
	// 	return (ft_werror("Error mutexmon\n", 2), 0);
	//printf(RED"CHECKDEATH data->dead = %d\n"RESET, data->dead);
	while (1)
	{
		i = 0;
		while (i < data->philos)
		{
			
			//printf(RED"CHECKDEATH philo id = %d last eat = %ld now =%ld t_die = %d\n"RESET, data->philo[i].id, ft_get_time() - data->philo[i].last_eat, ft_get_time(), data->t_die);
			//if ((ft_get_time() - data->philo[i].last_eat) >= data->t_die)
			//pthread_mutex_lock(&data->mutexmon);
			if (ft_philo_died(&data->philo[i]) && data->philo[i].eating == 0)
			{
				if (pthread_mutex_lock(&data->mutedead) != 0)
					return (ft_werror("Error lock muteat", 2), 0);
				data->dead = 1;
				ft_die(&data->philo[i]);
				ft_print_action("MUERTO", &data->philo[i], data->philo[i].id);
				if (pthread_mutex_unlock(&data->mutedead) != 0)
					return (ft_werror("Error unlock mutexmon", 2), 0);
				return (1);
			}
			//pthread_mutex_unlock(&data->mutexmon);
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
			//printf(RED"ALERTA DE MUERTE\n"RESET);
			ft_end(data);
			//break;
		}
		else if (ft_checkeats(data))
		{
			printf(RED"ALERTA DE COMIDA\n"RESET);
			ft_end(data);
			exit (1);
		}
		
	}
	
}





