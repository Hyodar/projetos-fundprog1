
// ==================================================
//  ex2.c
//
//  Autores: Franco Barpp Gomes - 2126613
//           Patricia Abe Turato - 2136007
//
//  Projeto Prático I
// ==================================================

/*
------------------------------------------------------------------------------------
Explicação:

    Operador ternário:
        Os operadores ternários são usados para testes de condições lógicas, semelhante a um if/else.
        "printf((x & y)? "  " : "* ");", nesse caso, seria equivalente a:
            if(x&y) printf("  ");
            else printf("* ");

    & : Bitwise AND (AND bit a bit)
        Operação entre dados binários (um int, por exemplo) que faz a operação AND entre cada um dos bits dos operandos,
        resultando em outro número.
        
        Operação: 
            10110001 (base 2) = 177 (base 10)
          & 11110110 (base 2) = 246 (base 10)
            --------
            10110000 (base 2) = 176 (base 10)
            
            portanto, 177 & 246 = 176
            
        Nesse problema, o AND age como um determinador da alternância entre '*' e ' '.
        Por exemplo: na linha 11 do teste de mesa abaixo, como bin_y = 00000100, 
        seu & com um número começando como 0 e sendo incrementado vai evidentemente exibir 4 asteriscos inicialmente,
        pois até que o número da coluna tenha um bit 1 na posição 3, ele vai ter de ser incrementado 3 vezes.
        Após isso, ele vai exibir 4 grupos de espaços, considerando que, quando o bit da posição 3 do número da
        coluna é 1, até que o número em si vire 00001000 por incrementos de 1, seu & com a linha vai ser estritamente 
        positivo.
        Finalmente, pela mesma lógica, imprimirá mais 4 asteriscos.
        
        Estendendo esse raciocínio à todas as linhas, fica evidente que o uso do E bit-a-bit traz uma sequência de 
        '* ' e '  ' que mostra uma relação entre as potências de 2 que formam um binário e a ideia do triângulo 
        de Sierpinski (a divisão sucessiva de medidas por 2, formando sub-triângulos cada vez menores).
        Esse comportamento numérico, que interliga fractais e operações bit-a-bit, é motivo de interessantes 
        discussões mais aprofundadas, como visto em alguns trabalhos acadêmicos como esse: 
        http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.462.7787&rep=rep1&type=pdf
    
    << : Bitwise Left Shift
        Operação em um dado binário, que faz com que seu conteúdo seja movido para a esquerda pelo número de posições 
        desejado, mudando as casas dos bits e consequentemente o valor numérico do binário. 
        As casas adicionadas à direita para manter o número de casas constante são 0.
        
        Operação:
            117 (base 10) = 01110101 (base 2)
            117 << 1 = 11101010 = 234 (base 10)
            
            portanto, 117 << 1 = 234
            
        Nesse caso, o SIZE (1<<4) seria literalmente 2^4, pois o bit 1 foi deslocado 4 posições à direita.
        No fractal mostrado, as medidas das bases dos triângulos são sucessivamente divididas por 2. Considerando
        que as colunas são números inteiros, se torna inválida a possibilidade de que algum lado seja ímpar e sua
        decomposição em fatores primos seja potência de algo senão 2, pois:
            - potências de outros números, ao serem divididos por 2, levariam a um ímpar em algum momento
            - é impossível imprimir um asterisco na coluna 3.5, por exemplo
        O uso de SIZE (1 << n) é interessante, já que para qualquer n diferente de 0, SIZE será par e somente
        potência de 2, o que garante que conforme as medidas forem sendo divididas por 2 para a formação de 
        sub-triângulos (a ideia desse fractal), sempre serão potências de 2 e nunca chegarão nos problemas 
        mencionados até o menor lado ser 1, que seria o final do programa.
            
    Teste de mesa:
            
    linha   bin_y       
    0       00001111    _______________*
    1       00001110    ______________*_*_
    2       00001101    _____________*___*_
    3       00001100    ____________*_*_*_*_
    4       00001011    ___________*_______*_
    5       00001010    __________*_*_____*_*_
    6       00001001    _________*___*___*___*_
    7       00001000    ________*_*_*_*_*_*_*_*_
    8       00000111    _______*_______________*_
    9       00000110    ______*_*_____________*_*_
    10      00000101    _____*___*___________*___*_
    11      00000100    ____*_*_*_*_________*_*_*_*_
    12      00000011    ___*_______*_______*_______*_
    13      00000010    __*_*_____*_*_____*_*_____*_*_
    14      00000001    _*___*___*___*___*___*___*___*_
    15      00000000    *_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_
            
            
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE (1 << 4)

int main() {

    int x = 0;
    int y = 0;
    int i = 0;

    for(y = SIZE - 1; y >= 0; y--, putchar('\n')) {
        for(i = 0; i < y; i++){
            putchar(' ');
        }
        for(x = 0; x + y < SIZE; x++){
            printf((x & y)? "  " : "* ");
        }
    }

    return 0;
}
