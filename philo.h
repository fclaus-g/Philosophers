/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario42 <usuario42@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:47:24 by usuario42         #+#    #+#             */
/*   Updated: 2023/07/30 13:39:26 by usuario42        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>//cabecera para gettimeofday
/*Creamos una estructura mesa que va a contener todos los datos generales referentes al programa*/
typedef struct s_table
{
	int				philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	int				dead;

}					t_table;
/*Creamos una struct con los datos que va a manejar cada philo*/
typedef struct s_philo
{
	int				id;
	int				eat_times;
	int				dead;
	int				left_fork;
	int				right_fork;
}					t_philo;


int	ft_check_args(int ac, char **av);
#endif