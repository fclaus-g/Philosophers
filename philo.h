/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:47:24 by usuario42         #+#    #+#             */
/*   Updated: 2023/09/18 12:28:00 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define ORANGE "\033[0;38;5;208m"
# define RESET "\033[0m"

# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>//cabecera para gettimeofday
/*nombramos la struct para que t_philo la reconozca*/
typedef struct s_data	t_data;
/*Creamos una struct con los datos que va a manejar cada philo*/
typedef struct s_philo
{
	int				id;
	int				eat_times;
	int				last_eat;
	t_data			*data;
	pthread_t		thread;
}					t_philo;

/*Creamos una estructura data que va a contener todos los datos generales referentes al programa*/
typedef struct s_data
{
	int				philos;
	int				forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_times;
	int				dead;
	t_philo			*philo;//creamos un puntero a una estructura philo para poder crear un array de philos
	pthread_t		*monitor;
	pthread_mutex_t	*fork;
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

int		ft_check_args(int ac, char **av);
void	*ft_routine(void *philo);
void	ft_werror(char *str, int out);
time_t	ft_get_time(void);
#endif