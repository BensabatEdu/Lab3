#!/bin/bash
# Salve como gerar_testes.sh

echo "Gerando arquivos de teste..."

tamanhos=(1000 10000 100000 1000000)

for n in "${tamanhos[@]}"; do
    echo "Gerando vetores de tamanho $n"
    echo "$n" | ./gerador > /dev/null 2>&1
    mv teste.bin "teste_${n}.bin"
    echo "Arquivo teste_${n}.bin criado"
done
