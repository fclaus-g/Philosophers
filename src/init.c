/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:48:03 by usuario42         #+#    #+#             */
/*   Updated: 2023/10/17 14:03:21 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
/*iniciamos los datos de la struct data con los tiempos que 
nos meten por parametros*/
void	ft_init_data(int ac, char **av, t_data *data)
{
	data->philos = ft_atoi_ph(av[1]);
	data->forks = data->philos;
	data->t_die = ft_atoi_ph(av[2]);
	data->t_eat = ft_atoi_ph(av[3]);
	data->t_sleep = ft_atoi_ph(av[4]);
	if (ac == 6)
		data->eat_times = ft_atoi_ph(av[5]);
	else
		data->eat_times = -1;
	data->finished = 0;
	data->dead = 0;
	data->end = 0;
	data->start_time = ft_get_time();
}

void	ft_init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->philos);
	if (!data->philo)
		return (ft_werror("Error: malloc\n", 2));
	while (++i < data->philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_times = 0;
		data->philo[i].last_eat = ft_get_time();
		data->philo[i].r_fork = i;
		if (data->philos > 1)
		{
			if (i == data->philos - 1)
				data->philo[i].l_fork = 0;
			else
				data->philo[i].l_fork = i + 1;
		}
		data->philo[i].data = data;
	}
}

void	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philos);
	while (++i < data->forks)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (ft_werror("Error Mutex Init", 2));
	}
	if (pthread_mutex_init(&data->eatlock, NULL) != 0)
		return (ft_werror("Error eatlock init\n", 2));
	if (pthread_mutex_init(&data->deadlock, NULL) != 0)
		return (ft_werror("Error deadlock init\n", 2));
	if (pthread_mutex_init(&data->endlock, NULL) != 0)
		return (ft_werror("Error endlock init\n", 2));
	if (pthread_mutex_init(&data->printlock, NULL) != 0)
		return (ft_werror("Error printlock init\n", 2));
}

void	ft_init_threads(t_data *data)
{
	pthread_t	monitor;

	data->thread = malloc(sizeof(pthread_t) * data->philos);
	if (!data->thread)
		return ;
	if (pthread_create(&monitor, NULL, (void *)&ft_monitoring, \
		(void *)data) != 0)
		return (ft_werror("Error monitor create\n", 2));
	if (data->philos == 1)
	{
		ft_check_one(data);
	}	
	else
	{	
		ft_run_threads(data);
		ft_join(data);
	}
	pthread_join(monitor, NULL);
	ft_end(data);
}

void	ft_check_one(t_data *data)
{
	if (pthread_create(&data->thread[0], NULL, (void *)&ft_only_one, \
		&data->philo[0]) != 0)
		return (ft_werror("Error: pthread create one philo\n", 2));
	ft_join(data);
}
