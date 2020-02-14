//-----------------------------------------------
//	SIMPLE DEMO WHERE EACH PERIODIC TASK
//	DISPLAYS A CHARACTER AT EVERY PERIOD
//-----------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <allegro.h>
#include <sched.h>
#include "task.h"
#include "constant.h"

//-----------------------------------------------
//	GLOBAL VARIABLES
//-----------------------------------------------
int						end = 0;
char					mes[MAXT][LEN+1];
 
void init()
{
char	s[LEN];

		allegro_init();
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
		clear_to_color(screen, BKG);
		install_keyboard();
		// ptask_init(SCHED_FIFO);  ??????
		sprintf(s, "Press SPACE to create a task");
		textout_ex(screen, font, s, 10, 10, 14, BKG);
}

void* hello(void* arg)
{
int		i, k = 0;
int		x, y;
char	buf[2];
	
	i = get_task_index(arg);
	set_activation(i);
	printf("task period %d\n", get_task_period(arg));
	sprintf(mes[i], "I'm task %d, T = %d ", i, get_task_period(arg));
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
		wait_for_activation(i);
	}
}

void wait_for_task_end(int i)
{
	pthread_join(tid[i], NULL);
}

int main()
{
int ret;
int		i;
char	scan;

	init();
	do {
		scan = 0;
		if(keypressed()) {
			printf("Hai premuto un tasto\n");
			scan = readkey() >> 8;
		} 
		if(scan == KEY_SPACE && i < MAXT) {
			printf("Creo un nuovo task %d di periodo %d\n", i, PER+i*PINC);
			ret = task_create(hello, i, PER+i*PINC, PER+i*PINC, 50);
			printf("task_create() ha ritornato %d\n", ret);
			// nelle slides usava un ulteriore argomento: ACT
			i++;
		}
	} while (scan != KEY_ESC);
	end = 1;
	for(i=0; i<=MAXT; i++) wait_for_task_end(i);
	allegro_exit();
	return 0;
}

	
	

