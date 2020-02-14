#include "task.h"

struct task_par	tp[MAXT];
pthread_t		tid[MAXT];

int task_create( void* (*task)(void*), int i, int period, int drel, int prio)
{
pthread_attr_t 		myatt;
struct sched_param	mypar;
int					tret;

	if (i > MAXT) return -1;
	
	tp[i].arg = i;
	tp[i].period = period; 
	tp[i].deadline = drel;
	tp[i].priority = prio;
	tp[i].dmiss = 0;

	pthread_attr_init(&myatt);
	pthread_attr_setinheritsched(&myatt, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&myatt, SCHED_RR);
	mypar.sched_priority = prio;
	pthread_attr_setschedparam(&myatt, &mypar);
	
	tret = pthread_create(&tid[i], &myatt, task, (void*)(&tp[i]));
	return tret;
}

int get_task_index(void* arg)
{
struct task_par* tpar;
	
	tpar = (struct task_par*)arg;
	return tpar->arg;
}

int get_task_period(void* arg)
{
struct task_par* tpar;
	
	tpar = (struct task_par*)arg;
	return tpar->period;
}

void set_activation (int i)
{
struct timespec t;
		
	clock_gettime(CLOCK_MONOTONIC, &t);
	time_copy(&(tp[i].at), t);
	time_copy(&(tp[i].dl), t);
	time_add_ms(&(tp[i].at), tp[i].period);
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
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &(tp[i].at), NULL);
	time_add_ms(&(tp[i].at), tp[i].period);
	time_add_ms(&(tp[i].dl), tp[i].period);
}

//--------------------------
// Scheme of a periodic task:
//
//	void* task(void* arg)
//	{
//	<local variables>
//	int ti;
//
//		ti = get_task_index(arg);
//		set_activation(ti);
//		while (1) {
//			<task body>
//			if(deadline_miss(ti)) <do action>;
//			wait_for_activation(ti);
//		}	
//	}
//--------------------------
