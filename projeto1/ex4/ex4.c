
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
#define SEM_OPERADORA -1

#define MAX_TAMANHO 16
#define MIN_TAMANHO 13

// ------------------------------------------------------------------------------------
// Protótipos de função

int checarOperadora(unsigned long long int cartao, int tamanho);

int algoritmoDeLuhn(unsigned long long int cartao, int tamanho);

void imprimirOperadora(int operadora);

// ------------------------------------------------------------------------------------
// Main

void main()
{
    char caractere;
    int digito;
    unsigned long long int cartao = 0;
    int tamanho = 0;

    int operadora;

    int erroCaractere = 0;

    while((caractere = getchar()) != '\n' ){

        if(caractere < '0' || caractere > '9') erroCaractere = 1;

        digito = caractere - '0';

        cartao *= 10;
        cartao += digito;

        tamanho++;
        printf("%c", caractere);
    }


    if(erroCaractere) {
        printf(" Caracteres invalidos");
        return;
    }

    if(tamanho > MAX_TAMANHO) {
        printf(" Numero muito longo");
        return;
    }

    if(tamanho < MIN_TAMANHO) {
        printf(" Numero muito curto");
        return;
    }

    operadora = checarOperadora(cartao, tamanho);

    if(operadora == SEM_OPERADORA){
        printf(" Operadora desconhecida");
        return;
    }

    imprimirOperadora(operadora);

    if(algoritmoDeLuhn(cartao, tamanho)){
        printf(", valido");
    } else {
        printf(", invalido");
    }

    return;

}

// ------------------------------------------------------------------------------------
// Funções

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

    return SEM_OPERADORA;

}

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
