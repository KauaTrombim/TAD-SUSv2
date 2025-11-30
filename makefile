all: paciente.o main.o
	gcc paciente.o main.o -o main -std=c99 -Wall

#ReRun, ajuda no desenvolvimento
rrun: clean all run

paciente.o:
	gcc -c ./TADs/codes/paciente.c -o ./TADs/codes/paciente.o -std=c99 -Wall

main.o:
	gcc -c main.c -o main.o -std=c99 -Wall

run:
	./main

clean:
	rm *.o