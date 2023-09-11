#include "func_aux.h"
#include "struct.h"
#include <stdio.h>
#include "string.h"

/* lista de coisas a fazer:
 * calcular percurso
 * corrigir erros de segurança
 * ficheiro binário corrigir o binario das linhas
 *corrigir a leitura da 1 linha .txt
 *
 */

int main() {

    int total_p; // numero de paragens armazenadas
    lista_L L;
    Inicializa_L(&L);
    le_bin_l(&L);
    char *lista_arquivos[] = {"C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\linha1.txt",
                              "C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\linha2.txt",
                              "C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\linha3.txt",
                              "C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\linha4.txt",
                              "C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\linha5.txt"
    };
    int num_arquivos = sizeof(lista_arquivos) / sizeof(lista_arquivos[0]);
   // ler_varios_arquivos(lista_arquivos, num_arquivos,&L,&total_p);
    Paragens* all_paragens;
    all_paragens = malloc(sizeof(Paragens) * total_p);
/*
   total_p = 8;


    strcpy(all_paragens[0].nome, "porto" );
    strcpy(all_paragens[0].codigo, "P000" );
    all_paragens[0].n_linhas = 0;
    strcpy(all_paragens[1].nome, "lousa" );
    strcpy(all_paragens[1].codigo, "L000" );
    all_paragens[1].n_linhas = 0;
    strcpy(all_paragens[2].nome, "kairo" );
    strcpy(all_paragens[2].codigo, "K000" );
    all_paragens[2].n_linhas = 0;
    strcpy(all_paragens[3].nome, "faro" );
    strcpy(all_paragens[3].codigo, "f000" );
    all_paragens[3].n_linhas = 0;
    strcpy(all_paragens[4].nome, "aveiro" );
    strcpy(all_paragens[4].codigo, "a000" );
    all_paragens[4].n_linhas = 0;
    strcpy(all_paragens[5].nome, "lisboa" );
    strcpy(all_paragens[5].codigo, "K000" );
    all_paragens[5].n_linhas = 0;
    strcpy(all_paragens[6].nome, "braga" );
    strcpy(all_paragens[6].codigo, "b000" );
    all_paragens[6].n_linhas = 0;
    strcpy(all_paragens[7].nome, "leiria" );
    strcpy(all_paragens[7].codigo, "l092" );
    all_paragens[7].n_linhas = 0;

    //return 0;
*/
    all_paragens =  le_bin_p(&total_p);
    welcome(); // mensagem de apresentação
    menu1(all_paragens,total_p,&L);
    free_Linhas(&L);
    return 0;
}
