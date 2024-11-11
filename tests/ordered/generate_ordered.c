#include <stdio.h>
#include <stdlib.h>

// Função para gerar inteiros aleatórios de tamanho n
void generate_ordered(int n, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(0);
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", i); // Vetor crescente, basta passarmos um for
    }
    fclose(file);
}

int main() {
    // Indo para a função gerar ordenadamente crescente vetores de n length
    generate_ordered(100, "vector_100.txt");
    generate_ordered(1000, "vector_1000.txt");
    generate_ordered(10000, "vector_10000.txt");
    generate_ordered(100000, "vector_100000.txt");
    return 0;
}
