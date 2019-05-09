
// ==================================================
//  ex4.c
//
//  Autores: Franco Barpp Gomes - 2126613
//           Patricia Abe Turato - 2136007
//
//  Projeto Prático I
// ==================================================


// ------------------------------------------------------------------------------------
// Bibliotecas

#include <stdio.h>
#include <math.h>

// ------------------------------------------------------------------------------------
// Constantes

#define MASTERCARD 0
#define VISA 1
#define AMEX 2
#define DINERS 3
#define DISCOVER 4
#define ENROUTE 5
#define JCB 6
#define OPERADORA_DESCONHECIDA -1

#define MAX_TAMANHO 16
#define MIN_TAMANHO 13

#define ERRO_CARACTERE " Caracteres invalidos"
#define ERRO_MAX_TAMANHO " Numero muito longo"
#define ERRO_MIN_TAMANHO " Numero muito curto"
#define ERRO_OPERADORA " Operadora desconhecida"

// ------------------------------------------------------------------------------------
// Protótipos de função

int checarOperadora(unsigned long long int cartao, int tamanho);

int algoritmoDeLuhn(unsigned long long int cartao, int tamanho);

void imprimirOperadora(int operadora);

int isLetra(char caractere);

// ------------------------------------------------------------------------------------
// Main

int main()
{
    char caractere;
    int digito;
    unsigned long long int cartao = 0;
    int tamanho = 0;

    int operadora;

    int erroCaractere = 0;

    printf("Insira o numero de cartao: ");
    while((caractere = getchar()) != '\n' ){
        if(isLetra(caractere)) erroCaractere = 1;

        digito = caractere - '0';

        cartao *= 10;
        cartao += digito;

        tamanho++;
        printf("%c", caractere);
    }


    if(erroCaractere) {
        printf(ERRO_CARACTERE);
        return 0;
    }

    if(tamanho > MAX_TAMANHO) {
        printf(ERRO_MAX_TAMANHO);
        return 0;
    }

    if(tamanho < MIN_TAMANHO) {
        printf(ERRO_MIN_TAMANHO);
        return 0;
    }

    operadora = checarOperadora(cartao, tamanho);

    if(operadora == OPERADORA_DESCONHECIDA){
        printf(ERRO_OPERADORA);
        return 0;
    }

    imprimirOperadora(operadora);

    if(algoritmoDeLuhn(cartao, tamanho)){
        printf(", valido");
    } else {
        printf(", invalido");
    }

    return 0;

}

// ------------------------------------------------------------------------------------
// Funções


/*! Checa qual eh a operadora do cartao com base no seu tamanho e prefixo
    \param cartao numero do cartao
    \param tamanho tamanho do numero do cartao
    \return 0 a 6 como vinculo a uma operadora ou -1 para operadora desconhecida
*/

int checarOperadora(unsigned long long int cartao, int tamanho) {

    int prefixo = cartao/pow(10, tamanho-4); // primeiros 4 digitos

    switch(tamanho) {
        case 13:
            if(prefixo/1000 == 4) return VISA;
        case 14:
            if(prefixo/100 == 30) return DINERS;
            if(prefixo/100 == 36) return DINERS;
            if(prefixo/100 == 38) return DINERS;
        case 15:
            if(prefixo/100 == 34) return AMEX;
            if(prefixo/100 == 37) return AMEX;
            if(prefixo == 2014) return ENROUTE;
            if(prefixo == 2149) return ENROUTE;
            if(prefixo == 2131) return JCB;
            if(prefixo == 1800) return JCB;
        case 16:
            if(prefixo/100 >= 51 && prefixo/100 <= 55) return MASTERCARD;
            if(prefixo/1000 == 4) return VISA;
            if(prefixo == 6011) return DISCOVER;
            if(prefixo/1000 == 3) return JCB;
    }

    return OPERADORA_DESCONHECIDA;

}

// ----------------------------------------------------------------------------

/*! Verifica a validade do numero de cartao pelo algoritmo de Luhn
    \param cartao numero do cartao
    \param tamanho tamanho do numero do cartao
    \return 1 para valido, 0 para invalido
*/

int algoritmoDeLuhn(unsigned long long int cartao, int tamanho) {

    int soma = 0;
    int n;

    for(int i=0; i<tamanho; i++){
        n = cartao%10;

        if(i%2 == 1){
            n *= 2;
            if(n > 9){
                n = n/10 + n%10;
            }
        }

        soma += n;
        cartao /= 10;
    }

    return !(soma%10);

}

// ----------------------------------------------------------------------------

/*! Imprime o nome da operadora
    \param operadora numero da operadora
*/

void imprimirOperadora(int operadora) {

    switch(operadora) {
        case MASTERCARD: printf(" Mastercard"); return;
        case VISA: printf(" Visa"); return;
        case AMEX: printf(" Amex"); return;
        case DINERS: printf(" Diners"); return;
        case DISCOVER: printf(" Discover"); return;
        case ENROUTE: printf(" enRoute"); return;
        case JCB: printf(" JCB"); return;
    }

}

// ----------------------------------------------------------------------------

/*! Checa se o caractere eh um numeral
    \param caractere caractere a ser checado
*/

int isLetra(char caractere) {
    return (caractere < '0' || caractere > '9');
}

