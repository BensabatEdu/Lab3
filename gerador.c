#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    long int N;
    printf("Digite o tamanho N dos vetores: ");
    scanf("%ld", &N);

    // Alocar memória para os vetores A e B
    float *A = (float *)malloc(N * sizeof(float));
    float *B = (float *)malloc(N * sizeof(float));

    // Inicializar o gerador de números aleatórios com uma semente baseada no tempo
    srand(time(NULL));

    // Preencher os vetores A e B com valores aleatórios entre 0 e 1
    for (long int i = 0; i < N; i++) {
        A[i] = (float)rand() / (float)RAND_MAX;
        B[i] = (float)rand() / (float)RAND_MAX;
    }

    // Calcular o produto interno sequencialmente
    float produto_interno = 0.0;
    for (long int i = 0; i < N; i++) {
        produto_interno += A[i] * B[i];
    }

    // Abrir arquivo binário para escrita
    FILE *arquivo = fopen("teste.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return 1;
    }

    // Escrever N no arquivo
    fwrite(&N, sizeof(long int), 1, arquivo);

    // Escrever o vetor A
    fwrite(A, sizeof(float), N, arquivo);

    // Escrever o vetor B
    fwrite(B, sizeof(float), N, arquivo);

    // Escrever o resultado do produto interno
    fwrite(&produto_interno, sizeof(float), 1, arquivo);

    // Fechar o arquivo
    fclose(arquivo);

    // Liberar memória alocada
    free(A);
    free(B);

    printf("Arquivo 'teste.bin' gerado com sucesso.\n");
    printf("Produto interno calculado: %f\n", produto_interno);

    return 0;
}