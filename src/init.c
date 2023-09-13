/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:48:03 by usuario42         #+#    #+#             */
/*   Updated: 2023/09/13 12:10:54 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
/*iniciamos los datos de la struct data con los tiempos que 
nos meten por parametros*/
void	ft_init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->philos = atoi(av[1]);
	data->forks = data->philos;
	data->t_die = atoi(av[2]);
	data->t_eat = atoi(av[3]);
	data->t_sleep = atoi(av[4]);
	if (ac == 6)
		data->eat_times = atoi(av[5]);
	else
		data->eat_times = 0;
	data->dead = 0;
	data->fork = malloc(sizeof(int) * data->forks + 1);
	if (!data->fork)
	{
		ft_werror("Error: malloc\n", 2);
		return ;
	}
	while (i++ < data->forks)
	{
		data->fork[i] = 0;
		printf(ORANGE"fork[%d] creado\n", i);
	}
	printf(BLUE"philos: %d\nt_die: %d\nt_eat: %d\nt_sleep: %d\neat_times: %d\n"RESET, data->philos, data->t_die, data->t_eat, data->t_sleep, data->eat_times);
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
	{
		ft_werror("Error: malloc\n", 2);
		return ;
	}
	while (++i < data->philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_times = 0;
		data->philo->last_eat = 0;
		data->philo[i].data = data;
		printf(GREEN"philo[%d].id: %d creado\n"RESET, i, data->philo[i].id);
	}
}
/*iniciamos un array de mutex uno por cada fork con la intencion de mutear 
los forks antes que algun filo acceda, he visto dos formas de mutear, 
al fork o al philo, de momento me decanto por el fork y ver como va funcionando*/

void	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	printf("iniciando mutex");
	while (++i)
	{
		philo[i].fork_l = malloc(sizeof(pthread_mutex_t) * philo->data->forks + 1);
		if (!philo[i].fork_l)
		{
			ft_werror("Error: malloc\n", 2);
			return ;
		}
		philo[i].fork_r = malloc(sizeof(pthread_mutex_t) * philo->data->forks + 1);
		if (!philo[i].fork_r)
		{
			ft_werror("Error: malloc\n", 2);
			return ;
		}
		if (pthread_mutex_init(&philo->fork_l[i], NULL) != 0)
		{
			ft_werror("Error: mutex init\n", 2);
			return;
		}
		printf(BLUE"mutex fork_l[%d] creado\n", i);
		if (pthread_mutex_init(&philo->fork_r[i], NULL) != 0)
		{
			ft_werror("Error: mutex init\n", 2);
			return ;
		}
		printf(BLUE"mutex fork_r[%d] creado\n"RESET, i);
	}
}
/*una vez tenemos los philos y los forks creamos los hilos, a tener en cuenta
 que un philo no es mas que una estructura con info sobre el philo y el hilo o 
thread es el subproceso que cambiara los valores de los datos nuestra struct*/

void	ft_init_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos)
	{
		if(pthread_create(&data->philo[i].thread, NULL, (void*)&ft_routine, &data->philo[i]) != 0)
			return (ft_werror("Error: pthread_create\n", 2));
		usleep(500);
	}
}