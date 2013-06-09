main: main.o scan.o util.o
	gcc -o main main.o scan.o util.o
main.o: globals.h util.h scan.h
	gcc -c main.c
scan.o: globals.h util.h scan.h
	gcc -c scan.c
util.o: globals.h util.h
	gcc -c util.c

clean: 
	rm main.o scan.o util.o
