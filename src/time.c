/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:09:12 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/09/21 10:34:38 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

time_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_werror("Error time", 2);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	ft_timedif(time_t before, time_t now)
{
	return (now - before);
}

int	ft_usleep(size_t mseconds)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < mseconds)
		usleep (500);
	return (0);
}