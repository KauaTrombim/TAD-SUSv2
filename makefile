CC = gcc
CFLAGS = -std=c99 -Wall
OBJS = main.o paciente.o avl.o heap.o historico.o
all: $(OBJS)
	$(CC) $(OBJS) -o main $(CFLAGS)

rrun: clean all run

main.o: main.c ./TADs/headers/paciente.h ./TADs/headers/avl.h
	$(CC) -c main.c -o main.o $(CFLAGS)

paciente.o: ./TADs/codes/paciente.c ./TADs/headers/paciente.h
	$(CC) -c ./TADs/codes/paciente.c -o paciente.o $(CFLAGS)

avl.o: ./TADs/codes/avl.c ./TADs/headers/avl.h
	$(CC) -c ./TADs/codes/avl.c -o avl.o $(CFLAGS)

heap.o: ./TADs/codes/heap.c ./TADs/headers/heap.h ./TADs/headers/paciente.h
	$(CC) -c ./TADs/codes/heap.c -o heap.o $(CFLAGS)

historico.o: ./TADs/codes/historico.c ./TADs/headers/historico.h
	$(CC) -c ./TADs/codes/historico.c -o historico.o $(CFLAGS)

run:
	./main

clean:
	rm -f *.o main