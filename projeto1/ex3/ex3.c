// ==================================================
//  ex3.c
//
//  Autores: Franco Barpp Gomes - 2126613
//           Patricia Abe Turato - 2136007
//
//  Projeto Prático I
// ==================================================

// ------------------------------------------------------------------------------------
// Bibliotecas

#include <stdio.h>

// ------------------------------------------------------------------------------------
// Protótipos de função

int contagemBits(int caractere);

void opcaoDecodificar();

void opcaoCodificar();

int decodificarCaractere(int decimal);

int codificarCaractere(int caractere);

// ------------------------------------------------------------------------------------
// Main

int main ()
{

    char input;

    printf("Codificar (c) ou decodificar (d)? ");
    scanf("%c%*c", &input); // evita o problema do \n ser pego no próximo input

    if(input == 'c'){
        opcaoCodificar();
    }
    else if(input == 'd'){
        opcaoDecodificar();
    }
    else{
        printf("Opcao invalida");
    }

    return 0;

}

// ------------------------------------------------------------------------------------
// Funções

/*! Conta o numero de bits um de um caractere
    \param caractere caractere da mensagem
    \return numero de bits um de um caractere
*/

int contagemBits(int caractere){

    int soma = 0;

    for(int i=0; i<8; i++){
        soma += (caractere & (1 << i)) >> i;
    }
    return soma;
}

// ----------------------------------------------------------------------------

/*! Menu de codificaçao de mensagem
*/

void opcaoCodificar(){

    int caractere;

    while ((caractere = getchar())!= '\n')
    {
        if(contagemBits(caractere)%2 != 0)
            caractere = codificarCaractere(caractere);
        printf("%d ", caractere);
    }
}

// ----------------------------------------------------------------------------

/*! Codifica um caractere inserido
    \param caractere caractere de uma mensagem
    \return caractere codificado
*/

int codificarCaractere(int caractere) {
    return caractere + 128; //torna o bit da posiçao 7 1
}

// ----------------------------------------------------------------------------

/*! Decodifica um caractere inserido
    \param caractere caractere de uma mensagem
    \return caractere decodificado
*/

int decodificarCaractere(int caractere) {
    return caractere - 128;
}

// ----------------------------------------------------------------------------

/*! Menu de decodificaçao
*/

void opcaoDecodificar(){
    int input=0;

    while(input!='.'){
        scanf("%d", &input);
        if(contagemBits(input)%2!=0){
            printf("*");
        }
        else{
            if(input>=128){
                input=decodificarCaractere(input);
            }
            printf("%c", input);
        }

    }
}

// ----------------------------------------------------------------------------
