all: graph.o main.o
	gcc graph.o main.o -o main -std=c99 -Wall -lm

verifica: graph.o main.o
	gcc -g -fsanitize=address graph.o main.o -o main -std=c99 -Wall -lm

run:
	./main

graph.o:
	gcc -c graph.c

main.o:
	gcc -c main.c

clean:
	rm a.out
	rm *.o
	rm main

