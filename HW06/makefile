all: prog
prog: main.o
	gcc -o snake main.o C:\PDCurses-master\wincon\pdcurses.a
main.o: main.c
	gcc -Wall -std=c99 C:\PDCurses-master\wincon\pdcurses.a -c main.c -o main.o
clean:
	del *.o snake
