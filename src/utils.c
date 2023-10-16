/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:16:18 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/16 12:55:39 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_args(int ac, char **av)
{
	int	i;
	int	c;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		ft_werror(RED"Error: Número de args invalido\n"RESET, 2);
		return (1);
	}
	while (av[i])
	{
		c = -1;
		while (av[i][++c])
		{
			if (!(av[i][c] >= '0' && av[i][c] <= '9'))
			{
				ft_werror(RED"Error: Solo carácteres numéricos\n"RESET, 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	ft_join(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos)
		pthread_join(data->thread[i], NULL);
}

int	ft_atoi_ph(char *str)
{
	size_t	count;
	size_t	result;
	int		sign;

	count = 0;
	result = 0;
	sign = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == 32)
		count++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
			sign = -1;
		count++;
	}
	while (str[count] >= '0' && str[count] <= '9')
	{
		result = result * 10 + str[count] - 48;
		count++;
	}
	return (sign * result);
}

int	ft_check_times(t_data *data)
{
	if ((data->t_die < 60 || data->t_die > INT_MAX) \
		|| (data->t_eat < 60 || data->t_eat > INT_MAX) \
		|| (data->t_sleep < 60 || data->t_sleep > INT_MAX))
	{
		ft_werror(RED"Error time must be >= 60 and <= INT_MAX\n"RESET, 2);
		return (1);
	}
	else if (data->eat_times == 0)
	{
		ft_werror(RED"If number of eats is 0 no dinner\n"RESET, 2);
		return (1);
	}
	return (0);
}
