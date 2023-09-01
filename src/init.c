/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario42 <usuario42@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:48:03 by usuario42         #+#    #+#             */
/*   Updated: 2023/08/08 12:50:09 by usuario42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
/*iniciamos los datos de la struct data con los tiempos que nos meten por parametros*/
void	ft_init_data(int ac, char **av, t_data *data)
{
	data->philos = ft_atoi(av[1]);
	data->forks = data->philos;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->eat_times = ft_atoi(av[5]);
	else
		data->eat_times = 0;
	data->dead = 0;
	printf(BLUE"philos: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\neat_times: %d\n", data->philos, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->eat_times);
}
/*iniciamos los philos con un bucle asignandole lod datos a cada uno de ellos asi tendremos
un array de philo[x] donde x es el numero de filosofos que gestionaremos*/
void	ft_init_philos(t_data *data)
{
	int i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->philos + 1);//lo mismo hay que añadir +1
	if (!data->philo)
	{
		ft_putstr_fd("Error: malloc\n", 2);
		return ;
	}
	while (++i < data->philos)
	{
		data->philo[i].id = i + 1;//el id empieza en 1 
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->philos;//el modulo nos permite que el último philo coja el primer tenedor
		data->philo[i].eat_times = 0;
		data->philo[i].dead = 0;
		printf(GREEN"philo[%d].id: %d creado\n", i, data->philo[i].id);
		printf(YELLOW"left_fork = %d\n right_fork = %d\n", data->philo[i].left_fork, data->philo[i].right_fork);
	}
}
/*iniciamos un array de mutex uno por cada fork con la intencion de mutear los forks antes 
que algun filo acceda, he visto dos formas de mutear, al fork o al philo, de momento me decanto
por el fork y ver como va funcionando*/
void	ft_init_mutex(t_data *data)
{
	int i;

	i = -1;
	data->forkmutex = malloc(sizeof(pthread_mutex_t) * data->forks + 1);
	if (!data->forkmutex)
	{
		ft_putstr_fd("Error: malloc\n", 2);
		return ;
	}
	while (++i < data->forks)
	{
		if (pthread_mutex_init(&data->forkmutex[i], NULL) != 0)
		{
			ft_putstr_fd("Error: mutex init\n", 2);
			return ;
		}
		printf(BLUE"forkmutex[%d] creado\n", i);
	}
}
/*una vez tenemos los philos y los forks creamos los hilos, 
a tener en cuenta que un philo no es mas que una estructura con info sobre el philo y el hilo o 
thread es el subproceso que cambiara los valores de los datos nuestra struct*/
void ft_init_threads(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philos)
	{
		if(pthread_create(&data->philo[i].thread, NULL, (void*)&ft_routine, &data->philo[i]) != 0)
			return(ft_putstr_fd("Error: pthread_create\n", 2));
		usleep(500);
	}
}