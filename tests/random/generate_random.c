#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função de gerar inteiros aleatórios
void generate_random(int n, const char* filename) {
    FILE *file = fopen(filename, "w");
    srand(time(NULL)); // Semente para valores aleatórios
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", rand() % 10000); // Vetor aleatório de até 10.000
    }
    fclose(file);
}

int main() {
    char path[50];

    // Indo para a função de gerar inteiros
    for (int set = 1; set <= 5; set++) {
        snprintf(path, sizeof(path), "tests/random/set_%d/vector_100.txt", set);
        generate_random(100, path);

        snprintf(path, sizeof(path), "tests/random/set_%d/vector_1000.txt", set);
        generate_random(1000, path);

        snprintf(path, sizeof(path), "tests/random/set_%d/vector_10000.txt", set);
        generate_random(10000, path);

        snprintf(path, sizeof(path), "tests/random/set_%d/vector_100000.txt", set);
        generate_random(100000, path);
    }
    return 0;
}
