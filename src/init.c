/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:48:03 by usuario42         #+#    #+#             */
/*   Updated: 2023/10/04 10:42:19 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
/*iniciamos los datos de la struct data con los tiempos que 
nos meten por parametros*/
void	ft_init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->philos = ft_atoi_ph(av[1]);
	data->forks = data->philos;
	data->t_die = ft_atoi_ph(av[2]);
	data->t_eat = ft_atoi_ph(av[3]);
	data->t_sleep = ft_atoi_ph(av[4]);
	//data->t_think = data->t_die - (data->t_eat + data->t_sleep);
	if (ac == 6)
		data->eat_times = ft_atoi_ph(av[5]);
	else
		data->eat_times = -1;
	data->finished = 0;
	data->dead = 0;
	data->start_time = ft_get_time();
	printf(ORANGE"start time [%ld]\n"RESET, data->start_time);
	printf(ORANGE"ft_now [%ld]\n"RESET, ft_now(data));
	//printf(BLUE"philos: %d\nt_die: %d\nt_eat: %d\nt_sleep: %d\neat_times: %d\n t_THINK :%d\n"RESET, data->philos, data->t_die, data->t_eat, data->t_sleep, data->eat_times, data->t_think);
}
/*iniciamos los philos con un bucle asignandole los datos a cada uno 
de ellos asi tendremos un array de philo[x] donde x es el numero de 
filosofos que gestionaremos.
El id de los philos comenzará en 1.
Al asignar los fork (i + 1) % data->philos: nos dará como resultado
que el ultimo philo coja el fork 0 cerrando asi el círculo 
*/

void	ft_init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->philos + 1);
	if (!data->philo)
		return (ft_werror("Error: malloc\n", 2));
	while (++i < data->philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_times = 0;
		data->philo[i].last_eat = ft_get_time();
		data->philo[i].eating = 0;
		data->philo[i].data = data;
		data->philo[i].r_fork = i;
		if (data->philos > 1)
		{
			if (i == data->philos - 1)
				data->philo[i].l_fork = 0;
			else
				data->philo[i].l_fork = i + 1;
		}
		printf(GREEN"philo[%d].id: %d creado\nr_fork[%d] l_fork[%d]\n"RESET, i, data->philo[i].id, data->philo[i].r_fork, data->philo[i].l_fork);
	
	}
}
/*iniciamos un array de mutex uno por cada fork con la intencion de mutear 
los forks antes que algun filo acceda*/

void	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	if(pthread_mutex_init(&data->mutedead, NULL) != 0)
		return (ft_werror("Error mutexdead\n", 2));
	if (pthread_mutex_init(&(data)->print, NULL) != 0)
		return (ft_werror("Error mutex print\n", 2));
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philos);
	while (++i < data->forks)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (ft_werror("Error Mutex Init", 2));
		if (pthread_mutex_init(&data->philo[i].muteat, NULL))
			return (ft_werror("Error Muteat Init", 2));
		printf(BLUE"mutex %d creado\n"RESET, i);
	}
}

/*una vez tenemos los philos y los forks creamos los hilos, a tener en cuenta
 que un philo no es mas que una estructura con info sobre el philo y el hilo o 
thread es el subproceso que cambiara los valores de los datos nuestra struct*/

void	ft_init_threads(t_data *data)
{
	int			i;

	i = -1;
	data->monitor = malloc(sizeof(pthread_t));
	if (!data->monitor)
		return (ft_werror("Error malloc monitor\n", 2));
	if (pthread_create(&data->monitor, NULL, (void *)&ft_monitoring, &data) != 0)
		return (ft_werror("Error monitor create\n", 2));
	while (++i < data->philos)
	{
		data->philo[i].thread = malloc(sizeof(pthread_t));
		if (!data->philo[i].thread)
			return ;
		if (pthread_create(&data->philo[i].thread, NULL, (void *)&ft_routine, &data->philo[i]) != 0)
			return (ft_werror("Error: pthread_create\n", 2));
		printf(ORANGE"PHILO Nº%d enviado al hilo %d\n"RESET, i, i);
		printf(RED"thread[%d] creado\n"RESET, i);
	}
}
