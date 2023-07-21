/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario42 <usuario42@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:46:32 by usuario42         #+#    #+#             */
/*   Updated: 2023/07/21 18:18:20 by usuario42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*funcion2(void *arg)
{
	int x = *((int*)arg) + 1;
	printf("Hilo creado con el valor %d\n", x);
	printf("Hilo en ejecucion...\n");
	return (NULL);
}
void	*funcion(void *arg)
{
	int x = *((int*)arg);
	printf("Hilo creado con el valor %d\n", x);
	printf("Hilo en ejecucion...\n");
	return (NULL);
}
int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	pthread_t hilo1;
	pthread_t hilo2;
	int	valor = 1;

	pthread_create(&hilo1, NULL, funcion, &valor);
	sleep(2);
	pthread_create(&hilo2, NULL, funcion2, &valor);
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);
	return(0);

}