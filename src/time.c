/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:09:12 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/10/16 12:56:16 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

time_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_werror(RED"Error time"RESET, 2);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t mseconds)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < mseconds)
	{
		usleep (50);
	}
	return (0);
}
