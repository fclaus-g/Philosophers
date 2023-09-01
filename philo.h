/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario42 <usuario42@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:47:24 by usuario42         #+#    #+#             */
/*   Updated: 2023/08/09 19:27:01 by usuario42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>//cabecera para gettimeofday
/*Creamos una struct con los datos que va a manejar cada philo*/
typedef struct s_philo
{
	int				id;
	int				left_fork;//dentro de cada philo guardamos el id de los tenedores que va a usar
	int				right_fork;//el iquierdo y el derecho
	int				eat_times;
	int				dead;
	pthread_t		thread;
	pthread_mutex_t	*mutex_fork_l;//creamos un puntero a un mutex para poder crear un array de mutex
	pthread_mutex_t *mutex_fork_r;//en teoria mutearemos los tenedores cuando intenten cogerlos los philos
}					t_philo;

/*Creamos una estructura mesa que va a contener todos los datos generales referentes al programa*/
typedef struct s_data
{
	int				philos;
	int				forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	int				dead;
	t_philo			*philo;//creamos un puntero a una estructura philo para poder crear un array de philos
	pthread_mutex_t	*yaveremos;
}					t_data;

/*init.c*/
void	ft_init_data(int ac, char **av, t_data *data);
void	ft_init_philos(t_data *data);
void	ft_init_threads(t_data *data);
void	ft_init_mutex(t_data *data);

/*action.c*/
void	ft_take_forks(t_philo *philos);
void	ft_eat(t_philo *philos);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_drop_forks(t_philo *philo);
void	ft_die(t_philo *philo);

int	ft_check_args(int ac, char **av);
void	ft_routine(t_philo *philo);
#endif