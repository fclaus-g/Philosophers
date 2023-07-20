/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicio_proyecto.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario42 <usuario42@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:17:01 by usuario42         #+#    #+#             */
/*   Updated: 2023/07/20 12:50:21 by usuario42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*PHILOSOPHERS*/

/*CONCEPTOS PARA ESTUDIAR
	-Thread (hilo)
	-Multithreading (multihilo)
	-Mutex(semaforo)(exclusion mutua)
	-data race
	-Deadlock
	-Funciones
		*gettimeofday
		*pthread_create
		*pthread_detach
		*pthread_join
		*pthread_mutex_init
		*pthread_mutex_destroy
		*pthread_mutex_lock
		*pthread_mutex_unlock*/

/*RESUMEN DEL SUBJECT
	- N-filosofos estan en una mesa redonda y en el centro hay comida.
	- Los filosofos solo pueden comer, pensar o dormir, nunca dos cosas a la vez.
	- Hay tantos tenedores como filosofos.
	- Los filosofos usan 2 tenedores para comer.
	- Cuando un philo termina de comer suelta los tenedores y se duerme.
	- Si no comen en el tiempo establecido mueren de hambre.
	
	INSTRUCCIONES GENERALES
		- Variables globales prohibidas.
		- El programa debe aceptar 5 argv:
			
			*number_of_philos (es tb el nº de tenedores).
			
			*time_to_die(milisegundos)-> tiempo desde el inicio al 1º eat o de
				un eat a otro.
			
			*time_to_eat(ms) -> tiempo en el que tiene los dos tenedores ocupados.
			
			*time_to_sleep(ms) -> tiempo que duerme.
			
			*number_of_times_each_philo_must_eat (opcional) -> si todos los philos
				comen al menos ese nº de veces el programa para. Si no se especifica
				se detiene con la muerte de un philo.
		
		- Cada philo es un thread y tendra asignado un num del 1 al number_of_philos.
		- El philo 1 se sienta al lado del philo number_of_philos, cualquier otro 
			philo N se sentara entre el philo N-1 y el philo N+1.

	LOGS
		- Se debe mostrar el momento en el que un philo coge un tenedor.
		- Se debe mostrar el momento en el que un philo come.
		- Se debe mostrar el momento en el que un philo duerme.
		- Se debe mostrar el momento en el que un philo piensa.
		- Se debe mostrar el momento en el que un philo muere.
		- Todos los logs deben tener el formato: [timestamp_in_ms] [philo_id] message (died, is eating, etc..).
		- El estado impreso en el log debe estar protegido por un mutex para que no se mezclen los mensajes.
		- No puede haber mas de 10ms entre la muerte y el momento de imprimir el mensaje de muerte.
		- El programa debe terminar despues de la muerte de un philo.
		- No data race
		*/