
# PHILOSOPHERS

## CONCEPTOS PARA ESTUDIAR
	
* __FORK__ -> Función que crea un proceso hijo dentro del programa que se
	diferencia de su proceso padre en su PID y en su PPID.(su PID es su nº de
	proceso y su PPID es el PID de su padre)
* __THREAD(hilo)__-> Es una tarea que puede ser ejecutada de manera paralela
	a otras tareas. Los hilos comparten el mismo espacio de direcciones y
	otros recursos que el proceso padre.
	Cada hilo tiene su propio identificador, pila de ejecución, 
	su puntero de instruccion y su propio conjunto de registros y comparte
	los recursos del proceso padre, como el espacio de direcciones,la memoria,
	los	descriptores de fichero y los manejadores de señales.
	El contexto de un hilo es mas pequeño que el de un proceso en recursos,
	por lo tanto es mas rapido crear y destruir hilos que procesos.
* __MULTITHREADIN(multihilo)__-> Es una técnica que permite a un programa
	realizar varias tareas de manera concurrente.
* __MUTEX(semaforo)(exclusion mutua)__-> Es un mecanismo de sincronización
	que permite asegurar que dos hilos no accedan simultáneamente a un mismo
	recurso compartido.
* __DATA RACE__-> Es una condición de carrera que ocurre cuando dos o más hilos
	están accediendo a una misma variable y al menos uno de ellos está
	modificando su valor.
* __DEADLOCK__ -> Es una situación en la que dos o más hilos están esperando
	eternamente a que se desbloqueen los recursos que el otro tiene bloqueados.
* __Funciones__
	
	* **gettimeofday** -> devuelve el tiempo actual en segundos y microsegundos.
		Se encuentra en la libreria *sys/time.h* y la función llena dos estructuras con detalles sobre la hora y el dia actual. 
		* La estructura *timeval* contiene las variables
			* *time_t tv_sec*-> contiene la cantidad de segundos desde el 1/1/1970.
			* *suseconds_t tv_usec*->Valor de microsegundos que la computadora conoce pero no esta incluido en 	el valor de t_time.
		* La estructura *tzp* contiene:
			* *int tz_minuteswest*-> num de minutos al oeste de GMT(meridiano de Greenwich) para la zona horaria actual del sistema.
			* *int tz_dsttime*-> num de horas para ajustar el horario de verano.
		Para hacer uso de ella se hace de la siguiente manera:
```C
	#include <sys/time.h> 
	
	int main(void)
	{
		struct timeval tv;
		struct	timezone tz;
		//Debemos declarar variables struct para almacenar la info de la función
		gettimeofday(&tv, &tz);
		printf("Seconds since 1970: %lu\n", tv.tv_sec);
		return (0);
	}
```
* **clock_gettime** calcula el tiempo transcurrido en un bloque de código en C, no esta permitida en este proyecto pero merece
	la pena mencionarla para futuros proyectos.

* **pthread_create** -> crea un hilo. Prototipo:
	**_int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg);_**
	(id del hilo, atributos del hilo, funcion que ejecutara el hilo, argumentos de la funcion) <se explica con mas detalle mas abajo>
	
* **pthread_detach** -> permite que el hilo se ejecute de manera independiente.   Prototipo:
	**_int pthread_detach(pthread_t thread);_**
		
* **pthread_join** -> espera a que el hilo termine. Prototipo:
	**_int pthread_join(pthread_t thread, void **retval);_**
	
* **pthread_mutex_init** -> inicializa un mutex. Prototipo:
	**_int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);_**
	(mutex, atributos del mutex). Si se pasa NULL como atributos se inicializa con los valores por defecto.
	
* **pthread_mutex_destroy** -> destruye un mutex. Prototipo:
	**_int pthread_mutex_destroy(pthread_mutex_t *mutex);_**
	
* **pthread_mutex_lock** -> bloquea un mutex. Prototipo:
	**_int pthread_mutex_lock(pthread_mutex_t *mutex);_**
	
* **pthread_mutex_unlock** -> desbloquea un mutex. Prototipo:
	**_int pthread_mutex_unlock(pthread_mutex_t *mutex);_** 
sem_close,
sem_post, sem_wait, sem_unlink

## RESUMEN DEL SUBJECT
	* N-filosofos estan en una mesa redonda y en el centro hay comida.
	* Los filosofos solo pueden comer, pensar o dormir, nunca dos cosas a la vez.
	* Hay tantos tenedores como filosofos.
	* Los filosofos usan 2 tenedores para comer.
	* Cuando un philo termina de comer suelta los tenedores y se duerme.
	* Si no comen en el tiempo establecido mueren de hambre.
	
### INSTRUCCIONES GENERALES

* ~~Variables globales~~ **prohibidas**.
	
* El programa debe aceptar 5 argv:
		
	* number_of_philos (es tb el nº de tenedores).
		
	* time_to_die(milisegundos)-> tiempo desde el inicio al 1º eat o de
	un eat a otro.
			
	* time_to_eat(ms) -> tiempo en el que tiene los dos tenedores ocupados.
			
	* time_to_sleep(ms) -> tiempo que duerme.
			
	* number_of_times_each_philo_must_eat (opcional) -> si todos los philos
	comen al menos ese nº de veces el programa para. Si no se especifica
	se detiene con la muerte de un philo.
		
* Cada philo es un thread y tendra asignado un num del 1 al number_of_philos.

* El philo 1 se sienta al lado del philo number_of_philos, cualquier otro 
	philo N se sentara entre el philo N-1 y el philo N+1.

### LOGS
- Se debe mostrar el momento en el que un philo coge un tenedor.
- Se debe mostrar el momento en el que un philo come.
- Se debe mostrar el momento en el que un philo duerme.
- Se debe mostrar el momento en el que un philo piensa.
- Se debe mostrar el momento en el que un philo muere.
- Todos los logs deben tener el formato: [timestamp_in_ms] [philo_id] message (died, is eating, etc..).
- El estado impreso en el log debe estar protegido por un mutex para que no se mezclen los mensajes.
- No puede haber mas de 10ms entre la muerte y el momento de imprimir el mensaje de muerte.
- El programa debe terminar despues de la muerte de un philo.
- No data race [se explica mas abajo]

## **USO DE SUBPROCESOS POSIX**
En C la libreria para trabajar con hilos o subprocesos es **<pthread.h>** (Posix THREAD) que incluye unas 70 funciones para trabajar con hilos (crear, recuperar, administrar datos, etc). **Para compilar un programa con esta libreria hay que usar siempre la flag -pthread**
	_gcc -pthread main.c_

# Crear un hilo
Se puede crear un hilo desde cualquier hilo del programa con **phread_create**

```C
int	phtread_create(pthread_t *restrict thread, 
					const pthread_attr_t *restrict attr,
					void *(start_routine)(void*),
					void *restrict arg);
```
* **thread**-> puntero a una variable de tipo pthread_t para almacenar el identificador del hilo que vamos a crear. Es una estructura con un int id. No se si incluye alguna info mas. ***revisar mas adelante***

* **attr**-> argumento que permite cambiar los atributos predeterminados del nuevo hilo cuando se crea.
En este proyecto lo declararemos **NULL** porque no daremos uso a esta funcion.

* **start_routine**-> funcion con la que el hilo comienza su ejecución. El prototipo de esta funcion debe ser **_void *nombre_de_función(void *arg)_** -> ((void *arg) recibe el argumento del siguiente argumento de la funcion pthread_create_). Cuando el hilo llegue al final de esta funcion habrá terminado todas sus tareas.

* **arg**-> puntero a un argumento para pasar a la función _start_routine_. Si queremos pasar varios parametros a la funcion debemos parar un puntero a una estructura.

Cuando pthread_create finaliza la función, la variable de subproceso que se le proporciona(pthread_t)
contendrá el id del subproceso creado. La funcion devuelve 0 si todo salió bien o un código de error en caso contrario.

# Recuperar un hilo o separarlo

Para bloquear la ejecución de un hilo mientras esperamos que otro hilo termine usamos *pthread_join*.
Esta función devuelve 0 si todo ha ido bien, si no un código de error.
Solo podemos esperar el final de un hilo específico.

´´´C
int	pthread_join(pthread_t thread, void **retval);
´´´
* **pthread**->el id del hilo que estamos esperando. El subproceso especificado aqui debe poder unirse
(no separarse);

* **retval**-> un puntero a una variable que puede contener el valor de la funcion de rutina de subproceso.
Si no necesitamos este valor -> **NULL**.

En algunos casos no hay que esperar a que finalicen ciertos hilos. Luego podemos desconectar el subproceso para indicarle al sistema que puede recuperar sus recursos cuando finalice el subproceso. Para esto 
usamos *pthread_detach* (generalmente justo despues de la creacion del hilo).
Retorna 0 si todo ha ido bien o un código de error.
Despues de desconectarlo otros subprocesos no tienen la opción de cerrar este proceso ni de esperar a recuperarlo con pthread_join.

```C
int	pthread_detach(pthread_t pthread);
```

Aquí solo metemos por parámetro el id del hilo.

# Más teoría...

## La memoria
Como se ha comentado al principio los hilos comparten la memoria de su proceso padre, y aunque cada hilo tenga su propia pila otros hilos pueden acceder al hilo a través de un puntero, los descriptores de almacenamiento dinámico y archivo abierto tambien se comparten entre hilos o subprocesos.
Esta memoria compartida hay que tenerla muy controlada porque es facil que haya errores de sincronización.

Por ejemplo: _si creamos un programa con dos hilos y un contador a 0 el cual los hilos tienen que aumentar el resultado que obtendriamos no sería fiable ya que se pueda dar el caso al funcionar en paralelo que ambos hilos cojan el valor del contador "a la vez" y lo incrementen una sola vez entre los dos. Otra cosa sería que un hilo no inicie hasta que acabe el anterior, ahí el acceso al contador seria ordenado y no tendría problemas._

## Carrera de datos

El hecho explicado en el ejemplo anterior es lo que nos llevaria a una **carrera de datos**, **data race** o **acceso concurrente** que explicado de otra manera sería: 
Una carrera de datos es un error de sincronización de hilos a la hora de ejecutarse un programa en el que varios hilos o subprocesos acceden a la misma area de memoria al mismo tiempo provocando errores en el procesamiento de datos.

Para activar una advertencia sobre data races en nuestro programa podremos compilarlo con las siguientes flags
```bash
gcc -fsanitize=thread -g main.c && ./a.out
```
Para solucionar los problemas de las data races tenemos mutex.

## Mutex ("MUTual EXclusion")

Es un bloqueo que regula el acceso a los datos y evita que los hilos accedan a la vez a los datos.
Un hilo bloquea e indiqua que el acceso a los datos esta "ocupado", el resto de hilos tendran que esperar a que el acceso a los datos se desbloquee y acceder a el por turnos.

### Usar un mutex

Con la libreria <pthread.h> tenemos acceso a mutex, y se usa declarando una variable de tipo mutex de la siguiente manera:
```C
pthread_mutex_t mutex
```
Y antes de usarlo hay que iniciar el mutex con la función **pthread_mutex_init** de esta manera:
```C
int	pthread_mutex_init(pthread_mutex_t *mutex,
						const pthread_mutexattr_t *mutexattr);
```
Sus parametros de entrada son los siguientes:
* **mutex**-> el puntero a una variable de tipo *pthread_muttex_t*, el mutex que queremos inicializar.
* **mutexattr**-> lo declaramos **NULL** porque en este proyecto no usaremos los atributos, pero sería 
un puntero a los atributos especificos para el mutex. [info ampliable en un futuro]
Estas funcion SIEMPRE retorna 0.

### Bloquear y desbloquear un mutex

Necesitamos bloquear y desbloquear los mutex para cortar o dar acceso a los datos y para ello tenemos estas funciones:
```C
int	pthread_mutex_lock(pthread_mutex_t *mutex);//bloquea
```
Si el mutex esta desbloqueado esta función bloquea, el hilo "toma el control" del mutex y la función finaliza.
Si el mutex esta bloqueado por otro hilo esta función suspende la llamada hasta que se desbloquee el mutex.

```C
int	pthread_mutex_unlock(pthread_mutex_t *mutex);//desbloquea
```
Esta función desbloquea el mutex suponiendo que el mutex esta bloqueado. **No comprueba si el mutex está bloqueado y que el hilo que lo invoca sea el que lo tenga bloqueado**. Por tanto si desbloqueamos un mutex que esta bloqueado por otro hilo obtendremos el error *"**lock order violation**""violación de orden de bloqueo"*

Las dos funciones retornan 0 en caso de OK o un código de error.

## Destruir un mutex

Cuando dejemos de necesitar un mutex hay que destruirlo debidamente con la función *pthread_mutex_destroy*:
```C
int	pthread_mutex_destroy(pthread_mutex_t *mutex);
```
Esta función **destruye un mutex desbloqueado** y libera los recursos que contiene.


### Fuentes 

* code(quoi) <https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/>