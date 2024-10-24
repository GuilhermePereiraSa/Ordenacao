#include <stdio.h>

// Função para gerar vetores de tamanho n 
void generate_reversed(int n, const char* filename) {
    FILE *file = fopen(filename, "w");
    for (int i = n; i > 0; i--) {
        // fprintf para colocar em um certo file
        fprintf(file, "%d\n", i); // Vetor (ordenado) decrescente
    }
    fclose(file);
}

int main() {
    // Passando n como tamanho e onde deve ser preenchido
    generate_reversed(100, "tests/reversed/vector_100.txt");
    generate_reversed(1000, "tests/reversed/vector_1000.txt");
    generate_reversed(10000, "tests/reversed/vector_10000.txt");
    generate_reversed(100000, "tests/reversed/vector_100000.txt");
    return 0;
}
