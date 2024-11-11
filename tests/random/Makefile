all: generate

generate: generate_random.c
	gcc generate_random.c -Wall -std=c99 -o generate

run: generate
	./generate

clean:
	rm -f generate \
		set_1/vector_100.txt set_1/vector_1000.txt set_1/vector_10000.txt set_1/vector_100000.txt \
		set_2/vector_100.txt set_2/vector_1000.txt set_2/vector_10000.txt set_2/vector_100000.txt \
		set_3/vector_100.txt set_3/vector_1000.txt set_3/vector_10000.txt set_3/vector_100000.txt \
		set_4/vector_100.txt set_4/vector_1000.txt set_4/vector_10000.txt set_4/vector_100000.txt \
		set_5/vector_100.txt set_5/vector_1000.txt set_5/vector_10000.txt set_5/vector_100000.txt
