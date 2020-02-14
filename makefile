rta: rtapplication.o task.o time.o
	gcc -o rta rtapplication.o time.o task.o `allegro-config --libs` -lpthread -lrt

rtapplication.o: rtapplication.c task.h constant.h
	gcc -c rtapplication.c `allegro-config --libs`
	
task.o: task.c task.h
	gcc -c task.c -lpthread -lrt

time.o: time.c time.h
	gcc -c time.c
	
clean: 
	rm -r rta *.o
