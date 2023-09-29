/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:20:10 by usuario42         #+#    #+#             */
/*   Updated: 2023/09/29 13:07:03 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	//printf(YELLOW"[timestamp]--philo[%d]--ha tomado el tededor derecho[%d]\n"RESET, philo->id, philo->r_fork);
	ft_print_action("ha tomado el tenedor derecho\n", philo, philo->id);
	// printf(RED"fork[%d]\n"RESET, philo->r_fork);
	pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	//printf(YELLOW"[timestamp]--philo[%d]--ha tomado el tededor izquierdo[%d]\n"RESET, philo->id, philo->l_fork);
	// printf(RED"fork[%d]\n"RESET, philo->l_fork);
	ft_print_action("ha tomado el tenedor izquierdo\n", philo, philo->id);
}

void	ft_eat(t_philo *philo)
{
	time_t	start;

	start = ft_get_time();
	ft_take_forks(philo);
	if (pthread_mutex_lock(&philo->muteat))
		return (ft_werror("Error muteat\n", 2));
	philo->eating = 1;
	philo->eat_times++;
	philo->last_eat = start - philo->data->start_time;
	printf(GREEN"philo[%d] start_times = %ld\n"RESET, philo->id, philo->last_eat);
	if (pthread_mutex_unlock(&philo->muteat))
		return (ft_werror("Error muteat\n", 2));
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
	ft_usleep(philo->data->t_eat - philo->data->t_sleep);
}
/*COMPROBAR BIEN LA MANO DEL PHILO*/
void	ft_drop_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->muteat))
		return (ft_werror("Error muteat\n", 2));
	philo->eating = 0;
	if (pthread_mutex_unlock(&philo->muteat))
		return (ft_werror("Error muteat\n", 2));
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
	ft_print_action("ha soltado el tenedor izquierdo\n", philo, philo->id);
	pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
	ft_print_action("ha soltado el tenedor derecho\n", philo, philo->id);
}

void	ft_die(t_philo *philo)
{
	ft_print_action("ha muerto\n", philo, philo->id);
	//philo->data->dead = 1;
}
