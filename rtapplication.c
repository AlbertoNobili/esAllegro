//-----------------------------------------------
//	SIMPLE DEMO WHERE EACH PERIODIC TASK
//	DISPLAYS A CHARACTER AT EVERY PERIOD
//-----------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <allegro.h>
#include <sched.h>
#include "ptask.h"

//-----------------------------------------------
//	GLOBAL CONSTANT
//-----------------------------------------------
#define	XWIN	640
#define	YWIN	480
#define	XBASE	40
#define	YBASE	30
#define	YINC	30
#define	BKG		0
//-----------------------------------------------
#define MAXT	10
#define	LEN		80
#define	PER		30
#define	PINC	20

//-----------------------------------------------
//	GLOBAL VARIABLES
//-----------------------------------------------
int		end = 0;
char	mes[MAXT][LEN+1];

void init()
{
char	s[LEN];

		alegro_init();
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
		clear_to_color(BKG);
		install_keyboard();
		ptask_init(SCHED_FIFO);
		sprintf(s, "Press SPACE to create a task");
		textout_ex(screen, font, s, 10, 10, 14, BKG);
}

int main()
{
int		i;
char	scan;

	init();
	do {
		scan = 0;
		if(keypressed()) scan = readkey() >> 8;
		if(scan == KEY_SPACE && i < MAXT) {
			task_create(i, hello, PER+i*PINC, PER*+i*PINC, 50, ACT);
			i++;
		}
	} while (scan != KEY_ESC);
	end = 1;
	for(i=0, i<=MAXT; i++) wait_for_task_end(i);
	allegro_exit();
	return 0;
}

void* hello(void* arg)
{
int		i, k = 0;
int		x, y;
char	buf[2];
	
	i = tesk_argument(arg);
	sprintf(mes[i], "i'm task %d, T = %d", i, task_period(i));
	while (!end) {
		x = XBASE + k*8;
		y = YBASE + i*YINC;
		sprintf(buf, "%c", mes[i][k]);
		textout_ex(screen, font, buf, x, y, 2+i, BKG);
		k++;
		if(mes[i][k] == '\0') {
			k = 0;
			textout_ex(screen, font, mes[i], XBASE, y, BKG, BKG);
		}
		wait_for_period(i);
	}
}
	
	
	
	
	
	
	
	
}
