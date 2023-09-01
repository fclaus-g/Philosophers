# Explicaciones varias

## Pasos a seguir
1. Parseo datos de entrada.
2. Almacenamiento de datos en struct con los tiempos de eat, sleep, die y el num de veces que deben comer.
3. Creacion de datos, philos, forks, threads y mutexes.
	Para esta parte tenemos que tener en cuenta nuestras struct y como estan comunicadas entre si, es algo que a la hora de programar no estoy viendo claro pero lo aclararé en breve.
	* _La struct principal_ *data
	```C
	typedef struct s_data
	{
		int numero de philos;
		int time_to_die;
		int time_to_eat;
		int time_to_sleep;
		int times_must_eat;
		int dead;
		t_philo	*philo;//detro de la struct tendremos un array de philos con el indice [i]
		pthread_mutex_t fork_mutex;//crearemos un mutex por cada tenedor en un array de mutex
	}t_data 
	typedef struct s_philo
	{
	int				id;//id del philo sera el valor de su indice
	int				left_fork;//dentro de philo guardamos el tenedor izq y 
	int				right_fork;//el derecho, no se si seria mas optimo guardarlo en *data
	int				eat_times;
	int				dead;
	pthread_t		thread;//el subproceso o hilo que iniciaremos con este philo[i]
					t_philo;
	}
	```