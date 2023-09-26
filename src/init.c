/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:48:03 by usuario42         #+#    #+#             */
/*   Updated: 2023/09/26 10:47:31 by fclaus-g         ###   ########.fr       */
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
	if (ac == 6)
		data->eat_times = ft_atoi_ph(av[5]);
	else
		data->eat_times = -1;
	data->finished = 0;
	data->dead = 0;
	data->start_time = ft_get_time();
	printf(ORANGE"start time [%ld]\n"RESET, data->start_time);
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
		return (ft_werror("Error: malloc\n", 2));
	while (++i < data->philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_times = 0;
		data->philo[i].last_eat = 0;
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
los forks antes que algun filo acceda, he visto dos formas de mutear, 
al fork o al philo, de momento me decanto por el fork y ver como va funcionando*/

void	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philos);
	while (++i < data->forks)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (ft_werror("Error Mutex Init", 2));
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
