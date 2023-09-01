/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario42 <usuario42@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:46:32 by usuario42         #+#    #+#             */
/*   Updated: 2023/08/10 17:44:04 by usuario42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*chequeamos que los arg son correctos sean numeros y haya 5 o 6 args*/
int	ft_check_args(int ac, char **av)
{
	int i;
	int c;

	i = 1;
	
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: Número de args invalido\n", 2);
		return(1);
	}
	while (av[i])
	{
		c = -1;
		while (av[i][++c])
		{
			if (ft_isdigit(av[i][c]) == 0)
			{
				ft_putstr_fd("Error: Formato de args inválido, solo carácteres numéricos\n", 2);
				return(1);
			}
		}
		i++;
	}
	return (0);
}



/*nuestra rutina o trabajo que realizaran los philos durante la ejecucion del programa*/
void	ft_routine(t_philo *philo)
{
	printf("thread[%d] creado\n", philo->id);
	if (philo->id % 2 == 0)
	{
		ft_sleep(philo);
		ft_think(philo);
		ft_eat(philo);
	}
	else
	{
	//	ft_take_forks(philo);
	 	ft_eat(philo); //AQUI HAY UN GAMBAZO SEG FAULT
	// 	ft_drop_forks(philo);
	 	ft_sleep(philo);
	 	usleep(1000000);
	}

}


int	main(int ac, char **av)
{
	t_data	*data;

	if (ft_check_args(ac, av))//chequeamos que los args sean correctos, 5 o 6 ac y todos numéricos
		return(1);
	printf("Todo correcto\n");
	data = malloc(sizeof(t_data));
	ft_init_data(ac, av, data);//guardamos los args en la estructura data
	ft_init_philos(data);//inicializamos los philos
	ft_init_mutex(data);//inicializamos los mutex
	ft_init_threads(data);//inicializamos los threads
	return(0);

}