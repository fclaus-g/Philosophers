/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:12:12 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/17 11:19:30 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(10);
	while (ft_checkend(philo->data) == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	*ft_only_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->fork[0]);
	ft_print_action("taken a fork\n", philo, philo->id);
	pthread_mutex_unlock(&philo->data->fork[0]);
	ft_usleep(philo->data->t_die);
	ft_print_action("is died\n", philo, philo->id);
	return (NULL);
}
