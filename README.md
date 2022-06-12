# Simulador de Compilador

Classicamente, um compilador traduz um programa de uma linguagem textual facilmente entendida por um ser humano para uma linguagem de máquina, específica para um processador e sistema operacional.

Existem algumas etapas no processo de compilação: na análise léxica o compilador verifica se escrevemos algum símbolo (caractere) que não pertence à linguagem; na análise sintática verifica-se se a estrutura do programa segue a sintaxe da linguagem; e na análise
semântica são checadas se os comandos podem ser executados. No final destas análises é
gerado um código intermediário, mais próximo da linguagem objeto e que ainda permite
uma manipulação mais fácil do que o código de máquina.

## Expecificações
Programa em C que recebe expressões alfa-numéricas no padrão de notação pós-fixada, 
valida essas expressões e gera o correspondente código intermediário em um arquivo de saída.

O vocabulário permitido nas expressões de entrada
é:
    
    • Operadores: {+, -, *, /}
    • Operandos: letras maiúsculas [A ... Z]

Ou seja, seu programa, que simulará um compilador deverá validar expressões compostas
apenas por esses caracteres. Seis operações podem ser geradas na saída:
    
    • LDR <OP>: carregar/ler o valor de um operando <OP>;
    • STR <OP>: grava/salva o valor de um operando <OP>;
    • ADD <OP1> <OP2>: somar os valores de dois operandos;
    • SUB <OP1> <OP2>: subtrair os valores de dois operandos;
    • MUL <OP1> <OP2>: multiplicar os valores de dois operandos;
    • DIV <OP1> <OP2>: dividir os valores de dois operandos.

Se necessário você pode criar variáveis temporárias que irão armazenar resultados parciais
das operações. Por exemplo, depois de somados os valores de A e B você pode considerar o
resultado como a variável TEMP1. 


Os casos de teste e suas respectivas saídas estão no repositório.
