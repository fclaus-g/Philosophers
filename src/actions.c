/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:20:10 by usuario42         #+#    #+#             */
/*   Updated: 2023/09/21 13:23:59 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	ft_print_action("ha tomado el tenedor derecho\n", philo, philo->id);
	pthread_mutex_lock(&philo->data->fork[philo->id]);
	ft_print_action("ha tomado el tenedor izquierdo\n", philo, philo->id);
}

void	ft_eat(t_philo *philo)
{
	time_t	start;

	start = ft_get_time();
	ft_take_forks(philo);
	philo->eating = 1;
	philo->eat_times++;
	philo->last_eat = start;
	ft_print_action("está comiendo\n", philo, philo->id);
	ft_usleep(philo->data->t_eat);
	ft_drop_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_action("está durmiendo", philo, philo->id);
	ft_usleep(philo->data->t_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print_action("esta pensando", philo, philo->id);
	ft_usleep(100);
}
/*COMPROBAR BIEN LA MANO DEL PHILO*/
void	ft_drop_forks(t_philo *philo)
{
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	ft_print_action("ha soltado el tenedor izquierdo\n", philo, philo->id);
	pthread_mutex_unlock(&philo->data->fork[philo->id]);
	ft_print_action("ha soltado el tenedor derecho\n", philo, philo->id);
}

void	ft_die(t_philo *philo)
{
	ft_print_action("ha muerto\n", philo, philo->id);
	philo->data->dead = 1;
}
