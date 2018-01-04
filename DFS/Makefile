main.out: main.o list.o stack.o graph.o
	gcc -std=c11 -Wall -O2 main.o list.o stack.o graph.o -o main.out -g
main.o: main.c list.h list.c stack.h stack.c graph.h graph.c
	gcc -std=c11 -Wall -O2 -c main.c -g
graph.o: graph.h graph.c list.h list.c
	gcc -std=c11 -Wall -O2 -c graph.c -g
stack.o: stack.c stack.h list.c list.h
	gcc -std=c11 -Wall -O2 -c stack.c -g
list.o: list.c list.h
	gcc -std=c11 -Wall -O2 -c list.c -g
clean:
	rm *.o *.out