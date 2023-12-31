/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:46:32 by usuario42         #+#    #+#             */
/*   Updated: 2023/10/17 14:04:38 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_leaks(void)
{
	system("leaks -q philo");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_check_args(ac, av))
		return (1);
	ft_init_data(ac, av, &data);
	if (ft_check_times(&data) == 1)
		return (1);
	if (data.philos == 0)
	{
		ft_werror(RED"No philos no dinner\n"RESET, 2);
		return (-1);
	}
	ft_init_philos(&data);
	ft_init_mutex(&data);
	ft_init_threads(&data);
	//atexit(ft_leaks);
	return (0);
}
