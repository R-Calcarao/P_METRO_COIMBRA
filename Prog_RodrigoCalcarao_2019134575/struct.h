//
// Created by rodri on 14/04/2023.
//
#ifndef TP_STRUCT_H
#define TP_STRUCT_H
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


typedef struct info_p{
    char nome[15];
    char codigo[5]; // pq é alfanumérico
    int  n_linhas; // número de linhas a que pertence

}Paragens;

typedef Paragens* lista_P, Pparagem; // lista paragens

char* gera_cod(); // gera um cod random

Paragens regista_paragem(Paragens* all_paragens,int total_p); //regista-se a info de uma nova paragem, numa estrutura P

void adiciona_paragem(Paragens *P,int* total_p ); // adiciona a estrutura P,no fim do array de estruturas de todas as paragens

Paragens* elimina_paragem(Paragens *P, int* total_p);

void imprime_paragens(Paragens* P, int total_p); // imprime todas as paragens


typedef struct info_linha{
    int n_paragens; // numero de paragens que tem
    char nome[15]; // NOME DA LINHA
    char** array_paragens; // array dinamico guarda paragem por linha
    struct info_linha *prox;
}Linhas;

typedef Linhas* lista_L;

void Inicializa_L (lista_L* listaL); // atribui o valor NULL a lista_l

void Insere_L(lista_L* listaL, char* nome,char** array_paragens, int tam);// cria uma nova linha

void imprime_L(lista_L* listaL);//imprime as linhas

void preenche_aux_paragens(int total_p,char** aux_array_paragens,Paragens* all_paragens,int np);// preenche uma array dinamico auxiliar com as paragens
                                                                                                // que dejamos guardar na linha

void acrescentar_paragens_linha(lista_L* listaL,char** array_paragens, int tam); //acrescenta paragens a uma linha

void delete_paragens_linha(lista_L*aux, int np);// elimina paragens de uma linha

void atualizar_linha(int total_p, Paragens* all_paragens,lista_L* listaL);//esta função permite adicionar ou eleminar paragens a uma linha

lista_L* devolve_linha(char* nlinha,lista_L* listaL);  //verifica se a linha existe

void free_Linhas(lista_L* listaL);//liberta a memoria das Linhas

#endif //TP_STRUCT_H
