# main.out: main.o
# 	g++ -std=c11 -Wall -O2 main.o -o main.out -g
main.out: main.cpp vector.h graph.h
	g++ -std=c++11 -Wall -O2  main.cpp -o main.out -g
# vector.o: vector.h list.h
# 	g++ -std=c++11 -Wall -O2 -c list.c -g
clean:
	rm *.o *.out
