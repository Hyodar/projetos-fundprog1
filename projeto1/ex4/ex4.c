
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
#define TAMANHO_INVALIDO -1

#define ERRO_CARACTERE " Caracteres invalidos"
#define ERRO_MAX_TAMANHO " Numero muito longo"
#define ERRO_MIN_TAMANHO " Numero muito curto"
#define ERRO_OPERADORA " Operadora desconhecida"
#define ERRO_CARTAO_NAO_INSERIDO "Cartao nao inserido"

// ------------------------------------------------------------------------------------
// Protótipos de função

void processarCartao(unsigned long long int cartao, int tamanho, int erroCaractere);

int checarOperadora(unsigned long long int cartao, int tamanho);

int algoritmoDeLuhn(unsigned long long int cartao, int tamanho);

void imprimirOperadora(int operadora);

int verificarTamanho(int tamanho);

int isLetra(char caractere);

// ------------------------------------------------------------------------------------
// Main

int main()
{
    char caractere;
    int digito;
    unsigned long long int cartao = 0;
    int tamanho = 0;

    int erroCaractere = 0;

    printf("Insira o numero de cartao: ");
    while((caractere = getchar()) != '\n'){
        if(isLetra(caractere)) erroCaractere = 1;

        digito = caractere - '0';

        cartao *= 10;
        cartao += digito;

        tamanho++;
        printf("%c", caractere);
    }

    processarCartao(cartao, tamanho, erroCaractere);

    return 0;

}

// ------------------------------------------------------------------------------------
// Funções


/*! Processa as informações do cartão e identifica erros
    \param cartao numero do cartao
    \param tamanho tamanho do numero do cartao
    \param erroCaractere indica se foi lido um caractere nao numerico
*/

void processarCartao(unsigned long long int cartao, int tamanho, int erroCaractere){
    
    int operadora;
    
    if(erroCaractere) {
        printf(ERRO_CARACTERE);
        return;
    }

    if(verificarTamanho(tamanho) == TAMANHO_INVALIDO) {
        return;
    }

    operadora = checarOperadora(cartao, tamanho);

    if(operadora == OPERADORA_DESCONHECIDA){
        printf(ERRO_OPERADORA);
        return;
    }

    imprimirOperadora(operadora);

    if(algoritmoDeLuhn(cartao, tamanho)){
        printf(", valido");
    } else {
        printf(", invalido");
    }
}

// ----------------------------------------------------------------------------

/*! Vericia se o tamanho do cartão é válido
    \param tamanho tamanho do numero do cartao
*/

int verificarTamanho(int tamanho){
    
    if(tamanho == 0) {
        printf(ERRO_CARTAO_NAO_INSERIDO);
        return TAMANHO_INVALIDO;
    }
    
    if(tamanho > MAX_TAMANHO) {
        printf(ERRO_MAX_TAMANHO);
        return TAMANHO_INVALIDO;
    }
    
    if(tamanho < MIN_TAMANHO) {
        printf(ERRO_MIN_TAMANHO);
        return TAMANHO_INVALIDO;
    }
    
    return tamanho;
}

// ----------------------------------------------------------------------------

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
            break;
        case 14:
            if(prefixo/100 == 30) return DINERS;
            if(prefixo/100 == 36) return DINERS;
            if(prefixo/100 == 38) return DINERS;
            break;
        case 15:
            if(prefixo/100 == 34) return AMEX;
            if(prefixo/100 == 37) return AMEX;
            if(prefixo == 2014) return ENROUTE;
            if(prefixo == 2149) return ENROUTE;
            if(prefixo == 2131) return JCB;
            if(prefixo == 1800) return JCB;
            break;
        case 16:
            if(prefixo/100 >= 51 && prefixo/100 <= 55) return MASTERCARD;
            if(prefixo/1000 == 4) return VISA;
            if(prefixo == 6011) return DISCOVER;
            if(prefixo/1000 == 3) return JCB;
            break;
    }

    return OPERADORA_DESCONHECIDA;

}

// ----------------------------------------------------------------------------

/*! Verifica a validade do numero de cartao pelo algoritmo de Luhn
    \param cartao numero do cartao
    \param tamanho tamanho do numero do cartao
    \return n>0 para valido, 0 para invalido
*/

int algoritmoDeLuhn(unsigned long long int cartao, int tamanho) {

    int soma = 0;
    int n;

    // digito por digito, se estiver em uma posicao impar (comecando do 0)
    // é dobrado e seus algarismos sao somados
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

    // retorna 0 se a soma nao for congruente a 0 em modulo 10
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

// ----------------------------------------------------------------------------
