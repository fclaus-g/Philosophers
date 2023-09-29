/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:18:09 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/09/27 13:44:26 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_werror(char *str, int out)
{
	int	c;

	c = 0;
	while (str[c])
		c++;
	write(out, str, c);
}

void	ft_print_action(char *str, t_philo *philo, int id)
{
	time_t	time;

	pthread_mutex_lock(&philo->data->print);
	time = ft_timedif(philo->data->start_time, ft_get_time());
	printf("[%ld]--philo[%d]--%s\n", time, id, str);
	pthread_mutex_unlock(&philo->data->print);
}
