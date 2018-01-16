main.out: main.o list.o
	g++ -std=c11 -Wall -O2 main.o list.o -o main.out -g
main.o: main.cpp list.c list.h graph.h
	g++ -std=c++11 -Wall -O2 -c main.cpp -g
list.o: list.c list.h
	g++ -std=c++11 -Wall -O2 -c list.c -g
clean:
	rm *.o *.out
