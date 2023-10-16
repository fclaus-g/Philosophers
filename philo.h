/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:47:24 by usuario42         #+#    #+#             */
/*   Updated: 2023/10/16 21:14:23 by fclaus-g         ###   ########.fr       */
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
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_times;
	time_t			last_eat;
	int				l_fork;
	int				r_fork;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				philos;
	int				forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_times;
	int				finished;
	int				dead;
	int				end;
	time_t			start_time;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_t		monitor;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eatlock;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	endlock;
	pthread_mutex_t	printlock;
}					t_data;

/*utils.c*/
int		ft_atoi_ph(char *str);
int		ft_check_args(int ac, char **av);
void	ft_join(t_data *data);
int		ft_check_times(t_data *data);
void	ft_one_error(t_data *data);

/*init.c*/
void	ft_init_data(int ac, char **av, t_data *data);
void	ft_init_philos(t_data *data);
void	ft_init_mutex(t_data *data);
void	ft_init_threads(t_data *data);
void	ft_check_one(t_data *data);

/*monitoring*/
void	ft_monitoring(void	*arg);
int		ft_checkdeath(t_data *data);
int		ft_checkeats(t_data *data);
int		ft_philo_died(t_philo *philo);

/*check_n_set.c*/
void	ft_setend(t_data *data);
void	ft_philoate(t_philo *philo);
int		ft_check_finished(t_data *data);
int		ft_philo_died(t_philo *philo);
int		ft_checkend(t_data *data);

/*routine.c*/
void	*ft_routine(void *arg);
void	*ft_only_one(void *arg);

/*action.c*/
void	ft_take_forks(t_philo *philos);
void	ft_eat(t_philo *philos);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_drop_forks(t_philo *philo);

/*print.c*/
void	ft_werror(char *str, int out);
void	ft_print_action(char *str, t_philo *philo, int id);

/*time.c*/
time_t	ft_get_time(void);
int		ft_usleep(size_t mseconds);

/*end.c*/
void	ft_end(t_data *data);
void	ft_destroy_mutex(t_data *data);

#endif