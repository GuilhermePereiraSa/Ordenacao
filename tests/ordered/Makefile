all: generate

generate: generate_ordered.c
	gcc generate_ordered.c -Wall -std=c99 -o generate

run: generate
	./generate

clean:
	rm -f generate vector_100.txt vector_1000.txt vector_10000.txt vector_100000.txt
