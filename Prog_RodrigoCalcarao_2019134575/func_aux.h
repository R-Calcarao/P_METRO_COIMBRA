//
// Created by rodri on 14/04/2023.
//

#ifndef TP_FUNC_AUX_H
#define TP_FUNC_AUX_H
#include "struct.h"
void ler_varios_arquivos(char **lista_arquivos, int num_arquivos, lista_L* listaL, int* total_p); //função lê varios ficheiros.txt

void welcome(); // mensagem de boas-vindas ao utlizador

int menu1(Paragens* all_paragens, int total_p,lista_L* L); // menu principal

void menu_paragem(Paragens* all_paragens, int total_p); // menu paragem

void menu_linha(Paragens* all_paragens, int total_p,lista_L* L); // menu linha

void menu_percurso(lista_L* L); // calcula percurso

void guarda_bin_p(Paragens* all_paragens, int total_p); // escreve a info num fich binario de todas as paragens

void guarda_bin_l(lista_L* L); // escreve num fich binario a informação de cada linha

Paragens* le_bin_p(int* total_p); // le fich binaraio de paragens

void le_bin_l(lista_L* L); // le fich binario de linhas

#endif //TP_FUNC_AUX_H

