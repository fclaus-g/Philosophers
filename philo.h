/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:47:24 by usuario42         #+#    #+#             */
/*   Updated: 2023/10/05 11:18:40 by fclaus-g         ###   ########.fr       */
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

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>//cabecera para gettimeofday
/*nombramos la struct para que t_philo la reconozca*/
typedef struct s_data	t_data;
/**
 * @brief 
 * * las variables l_fork y r_fork no son mas que el índice
 * * de los forks no los forks en si. Los fork serian el 
 * * array de mutex
 */

typedef struct s_philo
{
	int				id;
	int				eat_times;
	time_t			last_eat;
	int				eating;
	int				l_fork;
	int				r_fork;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	muteat;
}					t_philo;

/*Creamos una estructura data que va a contener todos los datos generales referentes al programa*/
typedef struct s_data
{
	int				philos;
	int				forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	//int				t_think;
	int				eat_times;
	int				finished;
	int				dead;
	time_t			start_time;
	t_philo			*philo;//creamos un puntero a una estructura philo para poder crear un array de philos
	pthread_t		monitor;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutexmon;
	pthread_mutex_t	mutedead;
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
void	*ft_routine(void *arg);
void	ft_werror(char *str, int out);
time_t	ft_get_time(void);
void	ft_monitoring(void	**arg);
void	ft_end(t_data *data);
void	ft_print_action(char *str, t_philo *philo, int id);
time_t	ft_timedif(time_t before, time_t now);
int		ft_usleep(size_t mseconds);
void	ft_join(t_data *data);
int		ft_atoi_ph(char *str);
time_t	ft_now(t_data *data);
int		ft_checkdeath(t_data *data);
int		ft_philo_died(t_philo *philo);

#endif