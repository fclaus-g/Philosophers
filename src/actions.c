/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:20:10 by usuario42         #+#    #+#             */
/*   Updated: 2023/09/13 12:12:16 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l[philo->id]);
	printf("philo[%d] ha tomado el tenedor izquierdo\n", philo->id);
	pthread_mutex_lock(&philo->fork_r[philo->id]);
	printf("philo[%d] ha tomado el tenedor derecho\n", philo->id);
}
void ft_eat(t_philo *philo)
{

	ft_take_forks(philo);
	printf("philo[%d] está comiendo\n", philo->id);
	ft_drop_forks(philo);
}

void ft_sleep(t_philo *philo)
{
	printf("philo[%d] está durmiendo\n", philo->id);
	usleep(1000000);
}
void	ft_think(t_philo *philo)
{
	printf("philo[%d] está pensando\n", philo->id);
	usleep(1000000);
}

void	ft_drop_forks(t_philo *philo)
{
	//pthread_mutex_unlock(&philo->mutex_fork_l[philo->left_fork]);
	printf("philo[%d] ha soltado el tenedor izquierdo\n", philo->id);
	//pthread_mutex_unlock(&philo->mutex_fork_r[philo->right_fork]);
	printf("philo[%d] ha soltado el tenedor derecho\n", philo->id);
}
void ft_die(t_philo *philo)
{
	printf("philo[%d] ha muerto\n", philo->id);
}
