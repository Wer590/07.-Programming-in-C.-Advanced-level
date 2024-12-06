all: prog
prog: main.o
	gcc.exe  -o snake.exe main.o C:/PDCurses-master/wincon/pdcurses.a -IC:/PDCurses-master
main.o: main.c
	gcc.exe -Wall -std=c99 -g -IC:/PDCurses-master/pdcurses -c main.c -o main.o 
clean:
	del *.o snake.exe