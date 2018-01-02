main.out: main.o stack.o list.o queue.o
	gcc -Wall -O2 main.o stack.o list.o queue.o -o main.out -g	
stack.o: stack.c stack.h
	gcc -Wall -O2 -c stack.c -g
queue.o: queue.c queue.h
	gcc -Wall -O2 -c queue.c -g
list.o: list.c list.h
	gcc -Wall -O2 -c list.c -g
clean:
	rm *.o *.out