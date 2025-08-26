#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    long int N;
    printf("Digite o tamanho N dos vetores: ");
    scanf("%ld", &N);

    float *A = (float *)malloc(N * sizeof(float));
    float *B = (float *)malloc(N * sizeof(float));

    srand(time(NULL));

    for (long int i = 0; i < N; i++) {
        A[i] = (float)rand() / (float)RAND_MAX;
        B[i] = (float)rand() / (float)RAND_MAX;
    }

    float produto_interno = 0.0;
    for (long int i = 0; i < N; i++) {
        produto_interno += A[i] * B[i];
    }

    FILE *arquivo = fopen("teste.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return 1;
    }

    fwrite(&N, sizeof(long int), 1, arquivo);
    fwrite(A, sizeof(float), N, arquivo);
    fwrite(B, sizeof(float), N, arquivo);
    fwrite(&produto_interno, sizeof(float), 1, arquivo);
    fclose(arquivo);
    free(A);
    free(B);

    printf("Arquivo 'teste.bin' gerado com sucesso.\n");
    printf("Produto interno calculado: %f\n", produto_interno);

    return 0;
}