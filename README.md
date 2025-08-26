# Lab3

## Códigos importantes
- `gerador.c` 
- `concorrente.c` 
- `gerar_testes.sh` 
- `executar_testes_simples.sh` -

Como Executar

# Compilar
gcc gerador.c -o gerador -lm
gcc concorrente.c -o concorrente -lpthread -lm

# Gerar testes
./gerar_testes.sh

# Executar experimentos
./executar_testes_simples.sh
