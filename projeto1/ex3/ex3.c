
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

int checarCorrompido(int binario);

void opcaoDecodificar();

void opcaoCodificar();

void decodificarCaractere(int decimal);

int codificarCaractere(int caractere);

// ------------------------------------------------------------------------------------
// Main

int main ()
{

    char input;

    printf("%d", contagemBits('.'));

    printf("Codificar (c) ou decodificar (d)? ");
    input = getchar(); // evita o problema do \n ser pego no próximo input

    if(input == 'c'){
        opcaoCodificar();
    }

    else if(input == 'd'){
        opcaoDecodificar();
    }
    else
        printf("Opcao invalida");

    return 0;

}

// ------------------------------------------------------------------------------------
// Funções

int contagemBits(int caractere){

    int soma = 0;

    for(int i=0; i<8; i++){
        soma += (caractere & (1 << i)) >> i;
    }
    return soma;
}

void opcaoCodificar(){

    int caractere;

    getchar();

    while ((caractere = getchar())!= '\n')
    {
        if(contagemBits(caractere)%2 != 0)
            caractere = codificarCaractere(caractere);
        printf("%d ", caractere);
    }
}

int codificarCaractere(int caractere) {
    return caractere + 128;
}

int decodificarCaractere(int caractere) {
    return caractere - 128;
}

void opcaoDecodificar(){}
