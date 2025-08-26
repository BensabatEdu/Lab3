#!/bin/bash
# Salve como executar_testes_simples.sh

echo "Executando experimentos..."
echo "Processadores disponíveis: $(nproc)"
echo ""

tamanhos=(1000 10000 100000 1000000)
threads=(1 2 4)
repeticoes=5

echo "Tamanho | Threads | Tempo Médio | Erro Médio"
echo "=============================================="

for n in "${tamanhos[@]}"; do
    for t in "${threads[@]}"; do
        echo "--- N=$n, T=$t ---"
        
        tempos=()
        erros=()
        
        for ((i=1; i<=repeticoes; i++)); do
            resultado=$(./concorrente $t "teste_${n}.bin")
            
            # Mostrar resultado completo para debug
            echo "Execução $i:"
            echo "$resultado"
            echo "---"
            
            # Extrair valores manualmente
            tempo=$(echo "$resultado" | grep "Tempo:" | awk '{print $2}')
            erro=$(echo "$resultado" | grep "Erro:" | awk '{print $2}')
            
            if [ -n "$tempo" ] && [ -n "$erro" ]; then
                tempos+=($tempo)
                erros+=($erro)
            fi
        done
        
        # Calcular médias manualmente (sem bc)
        if [ ${#tempos[@]} -gt 0 ]; then
            tempo_medio=$(echo "${tempos[@]}" | tr ' ' '\n' | awk '{sum+=$1} END {print sum/NR}')
            erro_medio=$(echo "${erros[@]}" | tr ' ' '\n' | awk '{sum+=$1} END {print sum/NR}')
            
            echo "$n | $t | $tempo_medio | $erro_medio"
        fi
        
        echo ""
    done
done
