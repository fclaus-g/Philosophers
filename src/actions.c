/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:20:10 by usuario42         #+#    #+#             */
/*   Updated: 2023/10/17 11:18:59 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	ft_print_action("has taken a fork\n", philo, philo->id);
	pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	ft_print_action("has taken a fork\n", philo, philo->id);
}

void	ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	ft_print_action("is eating\n", philo, philo->id);
	if (pthread_mutex_lock(&philo->data->eatlock))
		return (ft_werror("Error eatlock  l ft_eat\n", 2));
	philo->last_eat = ft_get_time();
	philo->eat_times++;
	if (pthread_mutex_unlock(&philo->data->eatlock))
		return (ft_werror("Error eatlock u ft_eat\n", 2));
	ft_usleep(philo->data->t_eat);
	ft_drop_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_action("is sleeping\n", philo, philo->id);
	ft_usleep(philo->data->t_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print_action("is thinking\n", philo, philo->id);
}

void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
}
