#include <pthread.h>
#include <stdlib.h>
#include "time.h"
#include "constant.h"

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

extern struct task_par	tp[];
extern pthread_t		tid[];

int task_create( void* (*task)(void*), int i, int period, int drel, int prio);
int get_task_index(void* arg);
int get_task_period(void* arg);
void set_activation (int i);
int deadline_miss(int i);
void wait_for_activation(int i);
