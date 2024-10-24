all:
	gcc -o main -Wall -std=c99 main.c -I /sorts/sort.h
run: all
	./main
clean:
	rm -f main