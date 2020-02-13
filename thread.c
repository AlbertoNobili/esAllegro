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
 




