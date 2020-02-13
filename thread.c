/*Per usare la libreria ptherad:*/
#include <pthread.h>
gcc es.c -o es -lpthread -lrt

/* Creazione thread */
int pthread_create(thread_t* id, pthread_attr_t* attr, void* (*body)(void*), void* arg))

thread_t pthread_self()

/* Terminazione thread */
int pthread_equal(pthread_t id1, pthread_t id2))
void prhtread_exit(void* retval) //se un padre termina con pthread_exti() i figli non vengono terminati
int pthread_cancel(pthread_t th)
int prhtread_join(pthread_t th, void** retval)
int pthread_detach(pthread_t th)

/*Thread attributes*/
int pthread_attr_init(pthread_attr_t* attr)
int pthread_attr_destroy(pthread_attr_t* attr))
//Per essere joinable/detached	PTHREAD_CREATE_DETACHED
int pthread_attr_setdetachstate(pthread_attr_t* attr, int state)
int pthread_attr_getdetachstate(const pthread_attr_t* attr, int* state)
//Per impostare la dimensione dello stack
int pthread_attr_setstacksize(pthread_attr_t* attr, int state)
int pthread_attr_getstacksize(const pthread_attr_t* attr, int* state)
//Per impostare il livello di priorità
int pthread_attr_setschedparam(pthread_attr_t* attr, struct sched_param state)
int pthread_attr_getschedparam(const pthread_attr_t* attr, struct sched_param* state)
struct sched_param {
	int sched_priority;
}
//Per dire che useremo un diverso scheduler
int pthread_attr_setinheritsched(pthread_attr_t* attr, int state)
int pthread_attr_getinheritsched(const pthread_attr_t* attr, int* state)
//Per specificare lo scheduler che useremo SCHED_OTHER SCHED_FIFO SCHED_RR SCHED_DEADLINE
int pthread_attr_setschedpolicy(pthread_attr_t* attr, int state)
int pthread_attr_getschedpolicy(const pthread_attr_t* attr, int* state)

/* Ottenere il Round-Robin quantum */
#include <sched.h>
int sched_rr_get_interval(pid_t pid, struct timespec* tp)

/* ESEMPIO */
int main()
{
pthread_attr_t		myatt;
struct sched_param	mypar;
pthread_t 			tid1, tid2;
void* 				retval;
int 				err;

	pthread_attr_init(&myattr);
	
	pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&myatt, SCHED_FIFO);
	
	mypar.sched_priority = 23;
	pthread_attr_setsched_param(&myattr, &mypar);
	
	err = pthread_create(&tid, &myattr, task, NULL);
	
	pthread_join(tid, &retval);
	pthread_attr_destroy(&mypar);
}


/* Time management */
struct timespec {
	time_t	tv_sec;
	long	tv_nsec;
}
//Non sono disponibili funzioni per fare operazioni sulle variabili temporali
//FUnzioni disponibili:
int clock_getres(clockid_t clk_id, struct timespec* res)
int clock_gettime(clockid_t clk_id, struct timespec* t)
int clock_settime(clockid_t clk_id, struct timespec* t)
int clock_nanosleep(clockid_t clk_id, int flag, const struct timespec* t, struct timespec* rem)

/* Real time parameters */
struct task_par {
	int		arg;			// task argument 
	long	wcet; 			// in microseconds
	int 	period;			// in microseconds
	int 	deadline;		// relative (ms)
	int 	priority;		// in [0, 99]
	int		dmiss;			// # of misses
	struct	timespec at;	// next activation time
	struct	timespec dl;	// absolute deadline
};

/* Task abstraction */

int task_create( void* (*task)(void*), int i, int period, int drel, int prio)
{
pthread_attr_t 		myatt;
struct sched_param	mypar;
int					tret;

	if (i > NT) return -1;
	
	tp[i].arg = i;
	tp[i].period = period]; 
	tp[i].deadline = drel;
	tp[i].priority = prio;
	tp[i].dmiss = 0;

	pthread_attr_init[myatt];
	pthread_attr_sethineritsched(&myattr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&myattr, SCHED_RR);
	mypar.sched_priority = prio;
	pthread_attr_setschedparam(&myattr, &mypar);
	
	tret = pthread_create(&tid, &myatt, task, (void*)(&tp[i]));
	return tret;
}

/* Scheme of a periodic task */
void* task(void* arg)
{
<local variables>
int ti;

	ti = get_task_index(arg);
	set_activation(ti);
	while (1) {
		<task body>
		if(deadline_miss(ti)) <do action>;
		wait_for_activation(ti);
	}	
}

int get_task_index(void* arg)
{
struct task_par* tpar;
	tpar = (struct task_par*)arg;
	return tpar->arg;
}

void set_activation (int i)
{
struct timespec t;
		
	clock_gettime(CLOCK_MONOTONIC, &t);
	time_copy(&(tp[i].at), t);
	time_copy(&(tp[i].dl), t);
	time_add_ms(&(tp[i].al), tp[i].period);
	time_add_ms(&(tp[i].dl), tp[i].deadline);
}

int deadline_miss(int i)
{
struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	if (time_cmp(now, tp[i].dl) > 0){
		tp[i].dmiss++;
		return 1;
	}
	return 0;
}

void wait_for_activation(int i)
{
	clock_nanosleep(CLOCK_MONOTONIC, TIME_ABSTIME, &(tp[i].at), NULL);
	time_add_ms(&(tp[i].at), tp[i].period);
	time_add_ms(&(tp[i].dl), tp[i].period);
}

/* Semaphores */
#include <semaphore.h>

int sem_init(sem_t* sem, int pshared, unsigned int v);
int sem_wait(sem_t* sem);
int sem_post(sem_t* sem);
int sem_destroy(sem_t* sem);
int sem_getvalue(sem_t* sem, int* pval);

/* Mutex */
pthread_mutex_t mux;
pthread_mutexattr_t matt;

//1: inizializzazione diretta
mux = PTHREAD_MUTEX_INITIALIZER;
//2: inizializzazione mediante valori default
pthread_mutex_init(&mux, NULL);
//3: inizializzazione mediante attributi
pthread_mutexattr_init(&matt);
pthread_mutexattr_setprotocol(&matt, PROTOCOLLO); ***
pthread_mutex_init(&mux, &matt);
pthread_mutexattr_destroy(&matt);

*** PROTOCOLLO in {PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, PTHREAD_PRIO_PROTECT}
*** se si sceglie PTHREAD_PRIO_PROTECT  si deve chiamare la funzione 
*** pthread_mutexattr_setpriorityceiling(&matt, CEILING) dove CEILING è la più alta priorità tra i thread che usano il mutex

//funzioni sui mutex:
pthread_mutex_lock(&mux);
pthread_mutex_unlock(&mux);
pthread_mutex_destroy(&mux);









