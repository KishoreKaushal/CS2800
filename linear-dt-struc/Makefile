main.out: main.o list.o stack.o queue.o
	gcc -std=c11 -Wall -O2 main.o list.o stack.o queue.o -o main.out -g
main.o: main.c list.h list.c stack.h stack.c queue.h queue.c
	gcc -std=c11 -Wall -O2 -c main.c -g
queue.o: queue.c queue.h list.c list.h
	gcc -std=c11 -Wall -O2 -c queue.c -g
stack.o: stack.c stack.h list.c list.h
	gcc -std=c11 -Wall -O2 -c stack.c -g
list.o: list.c list.h
	gcc -std=c11 -Wall -O2 -c list.c -g
clean:
	rm *.o *.out