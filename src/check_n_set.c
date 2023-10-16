/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:51:54 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/16 13:27:48 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_setend(t_data *data)
{
	pthread_mutex_lock(&data->endlock);
	data->end = 1;
	pthread_mutex_unlock(&data->endlock);
}

void	ft_philoate(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eatlock);
	if (philo->eat_times == philo->data->eat_times + 1)
		philo->data->finished++;
	pthread_mutex_unlock(&philo->data->eatlock);
}

int	ft_check_finished(t_data *data)
{
	int	check;

	pthread_mutex_lock(&data->eatlock);
	check = data->philos - data->finished;
	pthread_mutex_unlock(&data->eatlock);
	return (check);
}

int	ft_philo_died(t_philo *philo)
{
	time_t	ate;
	time_t	dietime;

	pthread_mutex_lock(&philo->data->eatlock);
	ate = philo->last_eat;
	dietime = philo->data->t_die;
	pthread_mutex_unlock(&philo->data->eatlock);
	if (ft_get_time() - ate >= dietime)
		return (1);
	return (0);
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
