all: generate

generate: generate_reversed.c
	gcc generate_reversed.c -Wall -std=c99 -o generate

run: generate
	./generate

clean:
	rm -f generate vector_100.txt vector_1000.txt vector_10000.txt vector_100000.txt
