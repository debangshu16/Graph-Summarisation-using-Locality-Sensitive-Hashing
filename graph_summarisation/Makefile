# -*- MakeFile -*-

exec: main.o graph_functions.o lsh.o supernodes.o utilities.o test.o
	gcc main.o graph_functions.o lsh.o supernodes.o utilities.o test.o -o exec -lm 

%.o: %.c functions.h
	gcc -c -g $<

test:test.c
clear:
	rm *.o exec
