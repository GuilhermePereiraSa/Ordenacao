#include <stdio.h>
#include <stdlib.h>

// Função para gerar vetores de tamanho n 
void generate_reversed(int n, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(0);
    }
    for (int i = n; i > 0; i--) {
        // fprintf para colocar em um certo file
        fprintf(file, "%d\n", i); // Vetor (ordenado) decrescente
    }
    fclose(file);
}

int main() {
    // Passando n como tamanho e onde deve ser preenchido
    generate_reversed(100, "vector_100.txt");
    generate_reversed(1000, "vector_1000.txt");
    generate_reversed(10000, "vector_10000.txt");
    generate_reversed(100000, "vector_100000.txt");
    return 0;
}
