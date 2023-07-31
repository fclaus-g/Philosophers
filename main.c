/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario42 <usuario42@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:46:32 by usuario42         #+#    #+#             */
/*   Updated: 2023/07/30 13:43:21 by usuario42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_save_args(int ac, char **av, t_table *table)
{
	table->philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->eat_times = ft_atoi(av[5]);
	else
		table->eat_times = -1;
	printf("philos: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\neat_times: %d\n", table->philos, table->time_to_die, table->time_to_eat, table->time_to_sleep, table->eat_times);
	free(table);
}

int	ft_check_args(int ac, char **av)
{
	int i;
	int c;

	i = 1;
	
	if (ac < 5 || ac > 6)
	{
		printf("Error: Número de args invalido\n");
		return(1);
	}
	while (av[i])
	{
		c = -1;
		while (av[i][++c])
		{
			if (ft_isdigit(av[i][c]) == 0)
			{
				printf("Error: Formato de args inválido, solo carácteres numéricos\n");
				return(1);
			}
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ft_check_args(ac, av))
		return(1);
	printf("Todo correcto\n");
	table = malloc(sizeof(t_table));
	ft_save_args(ac, av, table);
	return(0);

}