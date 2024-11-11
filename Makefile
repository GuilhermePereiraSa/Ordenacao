all: main

main: main.c ./sorts/sort.c
	gcc main.c ./sorts/sort.c -o main -Wall -std=c99 -I./sorts

run: main
	./main

clean:
	rm -f main
