#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>  // Para struct timeval

// Definir CLOCK_MONOTONIC se não estiver definido
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

// Estrutura para passar argumentos para as threads
typedef struct {
    long int inicio;
    long int fim;
    float *A;
    float *B;
    float resultado_parcial;
} ThreadArgs;

// Função que cada thread executará
void *calcula_parcial(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    float soma = 0.0;
    
    for (long int i = args->inicio; i < args->fim; i++) {
        soma += args->A[i] * args->B[i];
    }
    
    args->resultado_parcial = soma;
    pthread_exit(NULL);
}

// Função alternativa para medir tempo
double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <num_threads> <arquivo_binario>\n", argv[0]);
        return 1;
    }

    int T = atoi(argv[1]);
    char *filename = argv[2];

    // Abrir arquivo binário para leitura
    FILE *arquivo = fopen(filename, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return 1;
    }

    // Ler N
    long int N;
    fread(&N, sizeof(long int), 1, arquivo);

    // Alocar memória para os vetores
    float *A = (float *)malloc(N * sizeof(float));
    float *B = (float *)malloc(N * sizeof(float));
    
    // Ler vetores A e B
    fread(A, sizeof(float), N, arquivo);
    fread(B, sizeof(float), N, arquivo);
    
    // Ler valor de referência (sequencial)
    float vs;
    fread(&vs, sizeof(float), 1, arquivo);
    fclose(arquivo);

    // Preparar estruturas para threads
    pthread_t threads[T];
    ThreadArgs args[T];
    
    // Dividir o trabalho entre threads
    long int blocos = N / T;
    long int resto = N % T;
    long int inicio = 0;
    
    for (int i = 0; i < T; i++) {
        args[i].A = A;
        args[i].B = B;
        args[i].inicio = inicio;
        args[i].fim = inicio + blocos;
        
        // Distribuir o resto entre as threads
        if (i < resto) {
            args[i].fim++;
        }
        
        inicio = args[i].fim;
    }

    // Medir tempo de início
    double start_time = get_time();

    // Criar threads
    for (int i = 0; i < T; i++) {
        pthread_create(&threads[i], NULL, calcula_parcial, (void *)&args[i]);
    }

    // Aguardar threads finalizarem
    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    // Somar resultados parciais
    float vc = 0.0;
    for (int i = 0; i < T; i++) {
        vc += args[i].resultado_parcial;
    }

    // Medir tempo de fim
    double end_time = get_time();
    double tempo = end_time - start_time;

    // Calcular erro relativo
    float erro_relativo = fabsf((vs - vc) / vs);

    // Exibir resultados
    printf("N: %ld\n", N);
    printf("Threads: %d\n", T);
    printf("Tempo: %f segundos\n", tempo);
    printf("VS: %f\n", vs);
    printf("VC: %f\n", vc);
    printf("Erro: %e\n", erro_relativo);

    // Liberar memória
    free(A);
    free(B);

    return 0;
}