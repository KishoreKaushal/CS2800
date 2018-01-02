main.out: main.o list.o graph.o
	gcc -Wall -O2 main.o list.o graph.o -o main.out -g
main.o: main.c list.h graph.h list.c graph.c
	gcc -Wall -O2 -c main.c -g
graph.o: graph.c graph.h list.c list.h
	gcc -Wall -O2 -c graph.c -g
list.o: list.c list.h
	gcc -Wall -O2 -c list.c -g
clean:
	rm *.o *.out