/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:46:32 by usuario42         #+#    #+#             */
/*   Updated: 2023/09/22 17:11:20 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*chequeamos que los arg son correctos sean numeros y haya 5 o 6 args*/
int	ft_check_args(int ac, char **av)
{
	int	i;
	int	c;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		ft_werror("Error: Número de args invalido\n", 2);
		return (1);
	}
	while (av[i])
	{
		c = -1;
		while (av[i][++c])
		{
			if (!(av[i][c] >= '0' && av[i][c] <= '9'))
			{
				ft_werror("Error: Solo carácteres numéricos\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

/*nuestra rutina o trabajo que realizaran los philos
 durante la ejecucion del programa*/
void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("philo %d recibido\n", philo->id);
	while (philo->data->dead == 0)
	{
		if ((philo)->id % 2)
		{
			ft_sleep(philo);
			ft_think(philo);
			ft_eat(philo);
		}
		else
		{
			ft_eat(philo);
			ft_sleep(philo);
			ft_think(philo);
		}
	}
	return (NULL);
}

void	ft_join(t_data *data)
{
	int	i;

	i = -1;
	pthread_join(data->monitor, NULL);
	while (++i < data->philos)
	{
		pthread_join(data->philo[i].thread, NULL);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ft_check_args(ac, av))
		return (1);
	printf("Todo correcto\n");
	data = malloc(sizeof(t_data));
	ft_init_data(ac, av, data);
	ft_init_philos(data);
	ft_init_mutex(data);
	ft_init_threads(data);
	ft_join(data);
	return (0);
}
