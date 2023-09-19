/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:20:10 by usuario42         #+#    #+#             */
/*   Updated: 2023/09/19 13:44:11 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	printf("philo[%d] ha tomado el tenedor izquierdo\n", philo->id);
	pthread_mutex_lock(&philo->data->fork[philo->id]);
	printf("philo[%d] ha tomado el tenedor derecho\n", philo->id);
}
void	ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	printf("philo[%d] está comiendo\n", philo->id);
	ft_drop_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_action("está durmiendo", philo, philo->id);
	usleep(10000);
}

void	ft_think(t_philo *philo)
{
	printf("philo[%d] está pensando\n", philo->id);
	usleep(10000);
}
/*COMPROBAR BIEN LA MANO DEL PHILO*/
void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	printf("philo[%d] ha soltado el tenedor izquierdo\n", philo->id);
	pthread_mutex_unlock(&philo->data->fork[philo->id]);
	printf("philo[%d] ha soltado el tenedor derecho\n", philo->id);
}

void	ft_die(t_philo *philo)
{
	printf("philo[%d] ha muerto\n", philo->id);
}
