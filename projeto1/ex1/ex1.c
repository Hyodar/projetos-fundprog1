
// ==================================================
//  ex1.c
//
//  Autores: Franco Barpp Gomes - 2126613
//           Patricia Abe Turato - <TODO: COLOCAR MATRICULA>
//
//  Projeto Prático I
// ==================================================

#include <stdio.h>

// constantes do comprimento do nome de cada mês pra evitar repetições de strlen()
#define LEN_JANEIRO 7
#define LEN_FEVEREIRO 9
#define LEN_MARCO 5
#define LEN_ABRIL 5
#define LEN_MAIO 4
#define LEN_JUNHO 5
#define LEN_JULHO 5
#define LEN_AGOSTO 6
#define LEN_SETEMBRO 8
#define LEN_OUTUBRO 7
#define LEN_NOVEMBRO 8
#define LEN_DEZEMBRO 8

// constante do comprimento da linha de cabeçalho (DOM SEG...)
#define LEN_CABECALHO 28

// ------------------------------------------------------------------------------------
// Protótipos de função

void imprimirCabecalho(int mes, int ano);

int imprimirConteudo(int mes, int ano, int diaSemana);

int imprimirMes(int mes, int ano, int diaSemana);

void imprimirCalendario(int ano);

int isBissexto(int ano);

int diasMes(int mes, int ano);

int primeiroDiaAno(int ano);

void centralizarCabecalho(int mes);

void printEspacos(int n);

// ------------------------------------------------------------------------------------
// Main

int main(){
    int ano;
    
    printf("Insira o ano do calendário: ");
    scanf("%d", &ano);
    
    imprimirCalendario(ano);
    
    return 0;
}

// ------------------------------------------------------------------------------------
// Declaração de funções

void imprimirCabecalho(int mes, int ano) {

    printf("\n\n");
    centralizarCabecalho(mes); // centraliza o cabeçalho superior
    
    switch(mes) {
        case 0:
            printf("Janeiro de %d", ano);
            break;
        case 1:
            printf("Fevereiro de %d", ano);
            break;
        case 2:
            printf("Marco de %d", ano);
            break;
        case 3:
            printf("Abril de %d", ano);
            break;
        case 4:
            printf("Maio de %d", ano);
            break;
        case 5:
            printf("Junho de %d", ano);
            break;
        case 6:
            printf("Julho de %d", ano);
            break;
        case 7:
            printf("Agosto de %d", ano);
            break;
        case 8:
            printf("Setembro de %d", ano);
            break;
        case 9:
            printf("Outubro de %d", ano);
            break;
        case 10:
            printf("Novembro de %d", ano);
            break;
        case 11:
            printf("Dezembro de %d", ano);
            break;
    }

    printf("\n DOM SEG TER QUA QUI SEX SAB\n");

}

int imprimirConteudo(int mes, int ano, int diaSemana) {

    int nDias = diasMes(mes, ano);

    printEspacos(4*diaSemana); // enche de espaços onde seriam os dias do outro mês

    for(int i=1; i<=nDias; i++) {
        diaSemana = diaSemana%7;

        if(diaSemana == 0 && i>1) printf("\n");

        printf("%3d ", i);

        diaSemana++;
    }

    return diaSemana%7;

}

int imprimirMes(int mes, int ano, int diaSemana) {

    imprimirCabecalho(mes, ano);
    int diaSemanaProx = imprimirConteudo(mes, ano, diaSemana);

    return diaSemanaProx;

}

int isBissexto(int ano){
    return ano%4==0 && (ano%100!=0 || ano%400==0);
}

int diasMes(int mes, int ano){

    if(mes == 1) {
        if(isBissexto(ano)) return 29;
        return 28;
    }

    else if(mes <= 6){
        if(mes % 2 == 0) return 31;
        return 30;
    }

    else{
        if(mes % 2 == 0) return 30;
        return 31;
    }

}

int primeiroDiaAno(int ano) {

    // TODO: explicar congruencia de zeller e explicar pq +1 da certo

    int k = ano % 100;
    int j = ano / 100;

    int diaSemana = 1 + 52/10 + k + k/4 + j/4 + 5*j;
    diaSemana = diaSemana % 7;

    return diaSemana+1;

}

void imprimirCalendario(int ano) {
    
    printf("\n         CALENDARIO:         ");

    int primeiroDia = primeiroDiaAno(ano);

    for(int i=0; i<12; i++){
        primeiroDia = imprimirMes(i, ano, primeiroDia); // atualiza o primeiro dia da semana de cada mês sem necessidade de usar a congruencia de zeller dnv
    }

}

void centralizarCabecalho(int mes) {
    
    int nEspacos;
    int tamanhoMes;
    int tamanhoLinha = LEN_CABECALHO; // pega o tamanho total da linha
    
    // pega o tamanho do nome do mês
    switch(mes){
       case 0: tamanhoMes = LEN_JANEIRO; break;
       case 1: tamanhoMes = LEN_FEVEREIRO; break;
       case 2: tamanhoMes = LEN_MARCO; break;
       case 3: tamanhoMes = LEN_ABRIL; break;
       case 4: tamanhoMes = LEN_MAIO; break;
       case 5: tamanhoMes = LEN_JUNHO; break;
       case 6: tamanhoMes = LEN_JULHO; break;
       case 7: tamanhoMes = LEN_AGOSTO; break;
       case 8: tamanhoMes = LEN_SETEMBRO; break;
       case 9: tamanhoMes = LEN_OUTUBRO; break;
       case 10: tamanhoMes = LEN_NOVEMBRO; break;
       case 11: tamanhoMes = LEN_DEZEMBRO; break;
    }
    
    // pra que o texto esteja centralizado, o tamanho dele (contando os espaços) deve ser igual ao tamanho da linha
    // logo, o numero de espaços deve ser igual ao tamanho livre (tamanhoLinha - tamanhoEscrito) dividido por dois (tem dois lados)
    // como só precisa printar de um lado, printa só o número de espaços antes
    
    // 8 -> strlen("de AAAA")
    nEspacos = (tamanhoLinha - (tamanhoMes + 8))/2; 
    
    printEspacos(nEspacos);
    
}

void printEspacos(int n) {
    for(int i=0;i<n;i++){
        putchar(' ');
    }
}