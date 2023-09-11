//
// Created by rodri on 14/04/2023.
//
#include "struct.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "stdlib.h"


char* gera_cod(){
    char* cod = (char*) malloc(sizeof(char) * 5); //aloca memoria para o cod

    srand(time(NULL)); // inicializando a semente do gerador de números aleatórios com a hora atual

    cod[0] = (char)(rand() % 26 + 65); // Gera uma letra maiúscula aleatória (A-Z)
    cod[1] = (char)(rand() % 10 + 48); // Gera um dígito numérico aleatório (0-9)
    cod[2] = (char)(rand() % 10 + 48);
    cod[3] = (char)(rand() % 10 + 48);
    cod[4] = '\0'; // Termina a string com o caractere nulo
    return cod;
}

Paragens regista_paragem(Paragens* all_paragens, int total_p){
    Paragens P; //nova estrutura
    char *cod;

    printf("Nome: ");
    fflush(stdin);
    scanf("%s", P.nome);
    int i = 0;
    int flag = 0;
    do{                                  //gera cod, até gerar um cod que ainda não exista
        flag = 0;
        cod = gera_cod();
        for( i = 0;i < total_p ;i++){
            if(strcmp(all_paragens[i].codigo, cod) == 0){
                flag = 1; // significa que existe um mesmo cod
            }
        }
    }while(flag == 1);
    strcpy(P.codigo, cod);     // copia o valor de cod para a varivael codigo da nova estrutura P
    P.n_linhas = 0;
    return P;
}

void adiciona_paragem(Paragens* all_paragens,int* total_p){
    Paragens * aux;

    aux = (Paragens*)realloc(all_paragens,sizeof (Paragens) * ((*total_p) +1)); // realocação da memoria para ter espaço para a nova estrutura P
    if(aux != NULL){
        all_paragens = aux;
        all_paragens[*total_p] = regista_paragem(all_paragens,*total_p); // a ultima posição do array de todas as paragens passa a ser a nova estrutura P
        (*total_p)++;
    }
}

Paragens* elimina_paragem(Paragens *P, int* total_p){
    char elimina_st[4]; //codigo de paragem a eleminar
    int i;
    Paragens* aux, tmp;

    printf("Indique o codigo da paragem que deseja apagar: ");
    fflush(stdin);
    scanf("%s", &elimina_st);
    for( i = 0; i < *total_p && strcmp(elimina_st, P[i].codigo) != 0; i++); // serve para saber o indice onde se encontra a paragem
    if(P[i].n_linhas == 0){                             // verifica se a paragem pertence a alguma linha
        if(i == *total_p) printf("\n!!Paragem não Existe!!\n"); // se i estiver fora do array
        else if(*total_p == 1){  // se só tiver uma paragem apaga a estrutura P
            free(P);
            *total_p = 0;
            return NULL;
        }else{
            tmp = P[i];
            P[i] = P [*total_p - 1];
            aux = realloc(P,sizeof (Paragens) * ((*total_p) -1)); // realocação da memoria com o novo tam -= 1;
            if(aux != NULL){
                P = aux;
                (*total_p) --;
            }else{
                P[i]= tmp;
            }
        }
    }else {
        printf("Esta paragem nao pode ser eleminada pois ja pertence a uma linha!\n");
    }
    return P;
}

void imprime_paragens(Paragens* P, int total_p){
    for(int i = 0; i < total_p; i++){
        printf("\nParagem: %s\n", P[i].nome );
        printf("Codigo: %s\n", P[i].codigo );
        printf("Linhas: %d\n", P[i].n_linhas );
    }
}

void Inicializa_L (lista_L* listaL){
    *listaL = NULL;
};

void Insere_L(lista_L* listaL, char* nome_linha,char** aux_array_paragens, int tam){
    if  (*listaL == NULL)
        {
            *listaL = (lista_L) malloc(sizeof (Linhas));
            if(*listaL == NULL) return; // caso falhe a alocar memoria
            strcpy((*listaL)->nome, nome_linha);
            (*listaL)->n_paragens = tam;

            (*listaL)->array_paragens = (char**)malloc(sizeof(char*) * tam);

            for(int i= 0;i < tam; i++ ){
                (**listaL).array_paragens[i] = (char*)malloc(sizeof(char*) * 100);
            }
            for(int j= 0;j < tam; j++){
                strcpy((**listaL).array_paragens[j] , aux_array_paragens[j]);
            }
            (**listaL).prox = NULL;
    }else{
        Insere_L(&(**listaL).prox, nome_linha,aux_array_paragens,tam);
    }
};

void imprime_L(lista_L* listaL){

    if(*listaL == NULL){
        printf("fim\n");
        return;
    }else{
        printf("\nNome da Linha: %s",(*listaL)->nome);
        printf("\n\tParagens: ");
        for (int i=0; i<(*listaL)->n_paragens; i++){
            printf("%s, ",(*listaL)->array_paragens[i]);
        }
        imprime_L(&(*listaL)->prox);
    }
};

void preenche_aux_paragens(int total_p,char** aux_array_paragens, Paragens* all_paragens, int np){ // guarda na aux as paragens a adicionar

  int flag;
    for (int i = 0; i < np; i++) {
        do {
            flag = 0;
            printf("nome da paragem: ");
            fflush(stdin);
            scanf("%s", aux_array_paragens[i]);

            for (int j = 0; j < total_p; ++j) { // verifica se existe no array dinamico paragens
                if(strcmp(aux_array_paragens[i], all_paragens[j].nome) == 0){ // verifica se sao iguais se forem sai do ciclo
                    //printf("%s", all_paragens[j].codigo);
                    printf("\nAdicionado com sucesso!\n");
                    all_paragens[j].n_linhas+= 1;
                    flag = 1;
                    break;
                }
            }
        } while (flag == 0);
    }
};

void acrescentar_paragens_linha(lista_L* listaL,char** novas_paragens, int tam){ // acrescenta paragens a linhas que já tem paragens
        char** aux;

        aux = (char**) realloc( (*listaL)->array_paragens,sizeof (char**) * ((*listaL)->n_paragens) + tam); // realoca memoria para as novas paragens que vao ser adicionadas
        (*listaL)->array_paragens = aux;
        for(int i= 0;i < tam; i++ ){
            (**listaL).array_paragens[(*listaL) -> n_paragens + i] = (char*)malloc(sizeof(char*) * 100); // aloca espaço para as novas paragens
        }
        for(int i = 0; i < tam;i++){
            strcpy((**listaL).array_paragens[(*listaL) -> n_paragens + i] , novas_paragens[i]); // guarda as novas paragens no array paragens
        };
        (*listaL) -> n_paragens = (*listaL) -> n_paragens + tam; // n_paragens passa a ser igual a n_paragens + as novas paragens
        (**listaL).prox = NULL;
};

void delete_paragens_linha(lista_L* aux, int np){ // elimina paragens de uma linha
    char nomeparagem[15];

    for (int j = 0; j <  np; j++) {
        int flag = 0;
        do{
            printf("Indique qual a paragem que quer apagar:");
            fflush(stdin);
            scanf("%s",&nomeparagem);

            int i= 0;
            for( ;i < (*aux)->n_paragens && strcmp((*aux)->array_paragens[i],nomeparagem) !=0  ; i++);// serve para saber o indice onde se encontra a paragem
            if (i < (*aux)->n_paragens){
                flag = 1;
            }
            for( ;i < (*aux)->n_paragens - 1; i++){
                strcpy((*aux)->array_paragens[i] , (*aux)->array_paragens[i + 1]); // passamos os  restantes valores uma casa para a esquerda -> o atual fica igual ao seguinte
            }
        }while(flag == 0);
        (*aux)->n_paragens -= 1;
    }
    char** aux_array = (char**) realloc( ((*aux))->array_paragens,sizeof (char**) * ((*aux)->n_paragens) - np);// realocação de memoria para o novo tam do array
    (*aux)->array_paragens = aux_array;
};

void atualizar_linha(int total_p, Paragens* all_paragens,lista_L* listaL){ //esta função permite adicionar ou eleminar paragens a uma linha
    char nlinha[10];

    printf("Indique qual a linha que quer atualizar:");
    fflush(stdin);
    scanf("%s",&nlinha);

    lista_L* aux;
    int np;

    aux = devolve_linha(nlinha,listaL);  // verifica se a linha existe
    if(*aux != NULL) {
        int atualiza;
        do {
            printf("1.Deseja adicionar uma paragem?\n\t\t ou\n2. Eliminar uma paragem?");
            printf("\n-->");
            fflush(stdin);
            scanf("%d",&atualiza);
        }while(atualiza < 1 || atualiza > 2);
        char **aux_array_paragens; //variavel auxiliar
        if (atualiza == 1){
            do{
                printf("quantas paragens deseja introduzir(max 5):");
                fflush(stdin);
                scanf("%d",&np);
                if(np < 0 || np > 5){
                    printf("Tem de adicionar entre 1 a 5 paragens :\n");
                    printf("|Indique|\n");
                }
            }while(np < 0 || np > 5);
            aux_array_paragens = (char**)malloc(sizeof(char*) * np); // aloco memoria para cada  numero de paragens

            for (int i = 0; i < np; i++){
                aux_array_paragens[i] = (char*)malloc(sizeof(char) * 100);  // aloco memoria para o conteudo de cada linha
            }
            preenche_aux_paragens(total_p,aux_array_paragens, all_paragens,np);
            acrescentar_paragens_linha(aux,aux_array_paragens,np);
            for (int k = 0; k < np; k++) {
                free(aux_array_paragens[k]);
            }
        }else if(atualiza == 2){
            int flag = 0;
            while(flag == 0 ){
                printf("quantas paragens deseja apagar:");
                fflush(stdin);
                scanf("%d",&np);
                if((*aux)->n_paragens < np){
                    printf( "Esta linha tem %d paragens, só pode apagar %d!!\n",(*aux)->n_paragens ,(*aux)->n_paragens -1);
                }else flag = 1;
            }
            delete_paragens_linha(aux,np);
        }

    }
};

lista_L* devolve_linha(char* nlinha,lista_L* listaL){ //verifica se a linha existe
    lista_L* aux = listaL;
    while(*aux != NULL){
        if(strcmp(nlinha,(*aux)->nome) == 0){
            return aux;
        }
        *aux = (*aux)->prox;
    }
    return NULL;
};

void free_Linhas(lista_L* listaL){//liberta a memoria das Linhas
    Paragens *Tmp = *listaL;
    //Paragens *Tmp1 = *listaL;
    int i;
    while (*listaL != NULL){
        i=0;
        while( i < (*listaL)->n_paragens ){
            free((*listaL)->array_paragens[i]);
        }
        free((*listaL)->array_paragens);

        *listaL = (*listaL)->prox;
        free(Tmp);
        Tmp = *listaL;


    }
};








