/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:28:03 by fclaus-g          #+#    #+#             */
/*   Updated: 2023/09/18 09:40:34 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#define RED "\033[0;31m"
#define YEL "\033[0;33m"
#define END "\033[0m"

void	*ft_rutina1(void *data)
{
	int datos;
	pthread_mutex_t sh;

	pthread_mutex_init(&sh, NULL);
	datos = *((int*)data);
	printf(YEL"hilo en ejecución\n datos:%d\n"END, datos);
	while (datos >= 50)
	{
		printf(YEL"hilo en ejecución\n datos:%d\n"END, datos);
		pthread_mutex_lock(&sh);
		printf(RED"sh bloqueado"END);
		datos--;
		usleep(1000);
	}
	pthread_mutex_unlock(&sh);
	printf(RED"sh desbloqueado"END);

	return (0);
}
void	*ft_rutina2(void *data)
{
	int datos;
	datos = *((int*)data);
	printf(RED"hilo2 en ejecucion\n"END);
	while (datos <= 50)
	{
		printf(RED"hilo2 en ejecución\n datos:%d\n"END, datos);
		datos++;
		usleep(1000000);
	}	
	return (0);
}
time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(void)
{
	pthread_t	hilo1;
	pthread_t	hilo2;
	int 		prueba;
	long int start;
	long int cont;
	start = get_time_in_ms();
	prueba = 50;
	if (pthread_create(&hilo1, NULL, &ft_rutina1, &prueba) != 0)
		return (-1);
	if (pthread_create(&hilo2, NULL, &ft_rutina2, &prueba) != 0)
		return (-2);

	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);
	cont = get_time_in_ms();
	printf(YEL"%ld, %ld, milisegundos desde el inicio\n", cont, cont - start);
}


