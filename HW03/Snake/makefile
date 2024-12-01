all: prog
prog: main.o
	gcc.exe  -o snake.exe main.o C:/pdcurses/wincon/pdcurses.a -ID:\pdcurses
main.o: main.c
	gcc.exe -Wall -std=c99 -g -Ic:/pdcurses/curses -c main.c -o main.o
clean:
	del *.o snake.exe