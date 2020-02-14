#include "time.h"
// --------------------------------
//In the POSIX standar, time is represented through 
//the following structure:
//	struct timespec {
//		time_t tv_sec;	/* seconds */
//		long tv_nsec;	/* nanoseconds */	
//	}
//Where time_t is usually a 32-bit integer
//---------------------------------

//This function copies a source time variable ts in a 
//destination variable pointed by td:
void time_copy(struct timespec* td, struct timespec ts)
{
	td->tv_sec = ts.tv_sec;
	td->tv_nsec = ts.tv_nsec;
}

//This function adds a value ms expressed in milliseconds 
//to the time variable pointed by t:
void time_add_ms(struct timespec* t, int ms)
{
	t->tv_sec += ms/1000;
	t->tv_nsec += (ms%1000)*10^6;
	if (t->tv_nsec > 10^9) {
		t->tv_nsec -= 10^9;
		t->tv_sec += 1;
	}
}

//This function compares two time variables t1 and t2
//and returns 0 if they are equal, 1 if t1 > t2, -1 if t1 < t2:
int time_cmp(struct timespec t1, struct timespec t2)
{
	if (t1.tv_sec > t2.tv_sec) return 1;
	if (t2.tv_sec > t1.tv_sec) return -1;
	if (t1.tv_nsec > t2.tv_nsec) return 1;
	if (t2.tv_nsec > t1.tv_nsec) return -1;
	return 0;
}

//-------------------------------------------------------
//Funzioni disponibili:
//	1)	int clock_getres(clockid_t clk_id, struct timespec* res)
//	It copies in *res the resolution of the clock specified by 
//	clk:id. Such a resolution depends on the specific implementation 
//	and cannot be changed
//
//	2)	int clock_gettime(clockid_t clk_id, struct timespec* t)
//	It copies in *t the value of the clock specified by clk_id
//
//	3)	int clock_settime(clockid_t clk_id, struct timespec* t)
//	Sets the clock specified by clk_id to the value pointed by t. 
//	The value is truncated if it is nt multiple of the resolution
//
//	4)int clock_nanosleep(clockid_t clk_id, int flag, const struct timespec* t, struct timespec* rem)
//	Suspends the execution of the calling thread until the clock 
//	clk_id reaches the time specified by t. If flag = 0, time t is 
//	interpreted as relative to the current time; if flag = TIMER_ABS,
//	time t is interpreted as absolute. If the thread is awaken before 
//	the requested time, the remaining time is stored in rem. 
//
//Types of clock: CLOCK_REALTIME, CLOCK_MONOTONIC
// ------------------------------------------------------
