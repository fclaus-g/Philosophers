/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:18:09 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/16 13:05:07 by fclaus-g         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->data->printlock);
	time = ft_get_time() - philo->data->start_time;
	if (ft_checkend(philo->data) == 0)
		printf("[%ld] %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->data->printlock);
}
