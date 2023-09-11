//
// Created by rodri on 14/04/2023.
//
#include "stdio.h"
#include <stdlib.h>
#include "struct.h"
#include "func_aux.h"

void ler_varios_arquivos(char **lista_arquivos, int num_arquivos, lista_L* listaL , int* total_p) {
    lista_L* aux ;
    lista_L *tmp ;

    tmp = (lista_L*) malloc(sizeof (Linhas)); // aloca memoria para a lista

    char fnome_paragens[256];
    char  cod_paragem[5];
    FILE *arquivo;

    for (int i = 0; i < num_arquivos; i++) {
        arquivo = fopen(lista_arquivos[i], "r");
        if (arquivo != NULL) {
            char linha[15];
            printf("\n");
            int count = 0;

            for (char c = getc(arquivo); c != EOF; c = getc(arquivo)){
                if (c == '\n') // incrementa se encontrar um \n
                    count = count + 1;
            }
            rewind(arquivo); // volta para o inicio do ficheiro
            fscanf(arquivo,"Linha %s",linha);

            strcpy((*tmp)->nome,linha);
            printf("%s\n",(*tmp)->nome);
            int j = 0;
            /*
            while (fscanf(arquivo, "%s #%s",fnome_paragens,cod_paragem) != NULL) { // nome da linha esta guardada em linha

                printf("ola1");

                //(*tmp)->array_paragens[j] = (char*) malloc(sizeof(char) * 50);
                printf("ola2");
                printf("%s\n",fnome_paragens);
                // strcpy((*tmp)->array_paragens[j],fnome_paragens); // copia o nome da paragem para o array de paragens da lista ligada linha
                j++;
                printf("ola3");

            }
            */
            (*tmp)->array_paragens = (char**) malloc(sizeof(char*) * count); //numero de paragens que queremos guardar
            char flinha[256];
            while (fgets(flinha, 256, arquivo) != NULL) {
                // Remove the trailing newline character, if present
                flinha[strcspn(flinha, "\n")] = '\0';
                // Find the position of the '#' delimiter
                char *delimiter = strtok(flinha, "#");
                if (delimiter != NULL) {
                    strncpy(fnome_paragens,  delimiter, sizeof(fnome_paragens) );

                    //fnome_paragens[delimiter - flinha] = '\0';

                    delimiter = strtok(NULL, "#");
                    if (delimiter != NULL) {
                        strncpy(cod_paragem, delimiter, sizeof(cod_paragem));
                        cod_paragem[4] = '\0';
                        printf("Val1: %s\n", fnome_paragens);
                        (*tmp)->array_paragens[j] = (char*) malloc(sizeof(char) * 50);
                        strcpy((*tmp)->array_paragens[j],fnome_paragens); // copia o nome da paragem para o array de paragens da lista ligada linha
                        printf("Val2: %s\n", cod_paragem);
                        (*total_p) += (*total_p);
                    }

                }
            }
            fclose(arquivo);
            (*tmp)->prox = NULL;
        } else {
            printf("Erro ao abrir o arquivo %s\n", lista_arquivos[i]);
        }
        if (*listaL == NULL){
            listaL = tmp; // se  a lista L tiver vazia passamos o valor de tmp para a lista l, passando o tmp para dentro da lista  assumindo a 1 opção
            aux = listaL;
        }else{
            (*aux)->prox = (*tmp);
            *aux = (*aux)->prox;
        }
        printf("%s\n",(*aux)->nome);
    }
};




void welcome(){
    printf("\n\n        !Bem-vindo ao Metro Mondego!      ");
    printf("\n __________________________________________\n");
    printf("|                                          |\n");
    printf("|          _____              ___          |\n");
    printf("|  _||__|__|_||_\\__        [Coimbra]       |\n");
    printf("| (   _    _      _  \\         |           |\n");
    printf("|=`-(_)--(_)-|__||__|- >[]-----|--------[]-|\n");
    printf("|__________________________________________|\n");
};

int menu1( Paragens* all_paragens, int total_p,lista_L* L) {
    int o;
    while (o != 9){
        do {
            printf("\n----------------------------");
            printf("\n     | MENU PRINCIPAL|    ");
            printf("\n----------------------------\n");
            printf("\n1 - Paragens");
            printf("\n2 - Linhas");
            printf("\n3 - Calcular Percurso");
            printf("\n9 - Sair\n");
            printf("\n-->");
            fflush(stdout);
            scanf("%d", &o);
            if (o < 1 || (o > 3 && o != 9)) {
                printf("\n---------------------------------------------------");
                printf("\n| Opcao inexistente! Por favor, tente outra vez.|\n");
                printf("---------------------------------------------------\n");
                while (getchar() != '\n') {} // apagar buffer para evitar loop
            }
        } while (o < 1 || (o > 3 && o != 9));

        switch (o) {

            case 1:
                menu_paragem( &(*all_paragens), total_p);
                break;
            case 2:
                menu_linha(&(*all_paragens),  total_p,L);
                break;
            case 3:
                menu_percurso(L);
                break;
            case 9:
                guarda_bin_p(all_paragens,total_p);
                guarda_bin_l(L);
                printf("Boa viagem, ate ja!");
                exit(0);
        }
    }
};

void menu_paragem(Paragens* all_paragens, int total_p){
    int o;
    while(o != 8){
        do {
            printf("\n-------------------------");
            printf("\n   | MENU PARAGEM|");
            printf("\n-------------------------\n");
            printf("\n Pretende:");
            printf("\n1 - Visualizar Paragens");
            printf("\n2 - Registar Paragem");
            printf("\n3 - Eliminar Paragem");
            printf("\n8 - Voltar");
            printf("\n-->");
            fflush(stdout);
            scanf("%d", &o);
            if (o < 1 || (o > 3 && o != 8)) {
                printf("\n---------------------------------------------------");
                printf("\n| Opcao inexistente! Por favor, tente outra vez.|\n");
                printf("---------------------------------------------------\n");
                while (getchar() != '\n') {} // apagar buffer para evitar loop
            }
        } while (o < 1 || (o > 3 && o != 8));

        switch (o) {
            case 1:
                imprime_paragens(&(*all_paragens),total_p);
                break;
            case 2:
                adiciona_paragem(&(*all_paragens),&total_p);
                break;
            case 3:
            {
                elimina_paragem(&(*all_paragens),&total_p);
                imprime_paragens(&(*all_paragens),total_p);
                break;
            }
            case 8:
                printf("\n");
                return;
        };
    }
};

void menu_linha(Paragens* all_paragens, int total_p, lista_L* L) {
    int o;

    while (o != 0) {
        do {
            printf("\n-------------------------");
            printf("\n     | MENU LINHA|    ");
            printf("\n-------------------------\n");
            printf("Pretende:");
            printf("\n1 - Visualizar  Linhas");
            printf("\n2 - Adicionar Linhas");
            printf("\n3 - Atualizar Linhas");
            printf("\n8 - Voltar");
            printf("\n-->");
            fflush(stdout);
            scanf("%d", &o);
            if (o < 1 || (o > 3 && o != 8)) {
                printf("\n---------------------------------------------------");
                printf("\n| Opcao inexistente! Por favor, tente outra vez.|\n");
                printf("---------------------------------------------------\n");
                while (getchar() != '\n') {} // apagar buffer para evitar loop
            }
        } while (o < 1 || (o > 3 && o != 8));

        switch (o) {

            case 1: {
                imprime_L(L);
                break;
            }
            case 2: {
                int np ;//n de paragens que deseja introduzir
                char nlinha[10]; //nome da linha nova

                printf("nome da nova linha:");
                fflush(stdin);
                scanf("%s", &nlinha);

                char **aux_array_paragens; //variavel auxiliar
                printf("quantas paragens deseja introduzir:");
                fflush(stdin);
                scanf("%d",&np);
                aux_array_paragens = (char**)malloc(sizeof(char*) * np); // aloco memoria cada para o numero de paragens

                for (int i = 0; i < np; i++){
                    aux_array_paragens[i] = (char*)malloc(sizeof(char) * 100);  // aloco memoria para o conteudo de cada linha
                }
                preenche_aux_paragens(total_p, aux_array_paragens, all_paragens,np);
                //printf("%d",np);
                Insere_L( L, nlinha, aux_array_paragens, np);
                imprime_L(L);
                for (int k = 0; k < np; k++) {
                    free(aux_array_paragens[k]);
                }
                free(aux_array_paragens);
                break;
            }
            case 3: {
                atualizar_linha(total_p, all_paragens, L);
                imprime_L(L);
                break;
            }
            case 8:
                return;
        };
    };

};

void menu_percurso(lista_L* L){


    char partida[15];
    char partida2[15];
    char chegada[15];

    printf("Partida: ");
    scanf("%s", &partida);
    printf("Destino: ");
    scanf("%s", &chegada);

    lista_L* aux = L;

    int i = 0;
    int pflag = 0;
    int cflag = 0;
    int fc = 0;
    int fp = 0;
    while(*aux != NULL){
        printf("%s\n",(*aux)->nome);
        fp = 0;
        fc = 0;
        pflag = 0;
        cflag = 0;
        for(i= 0; i < (*aux)->n_paragens; i++){
            if(strcmp((*aux)->array_paragens[i],partida) == 0){
                pflag = 1;
                fp = i;
            }
            if(strcmp((*aux)->array_paragens[i],chegada) == 0){
                cflag = 1;
                fc = i;
            }
        }
        if(cflag == 1 && pflag == 1) {
            if(fp < fc) {
                for(int j = fp; j <= fc;j++){
                    printf(" => %s ", (*aux)->array_paragens[j]);
                }
                return;
            }else if(fp > fc){
                for(int j = fp; j >= fc; j--){
                    printf(" => %s ", (*aux)->array_paragens[j]);
                }
                return;
            }
        }
        *aux = (*aux)->prox;
    }



};

void guarda_bin_p(Paragens* all_paragens, int total_p){
    FILE* fp = fopen("C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\paragensmetro.bin","wb");
    if(fp == NULL){
        printf("Erro a abrir o ficheiro!\n");
        return;
    }
    fwrite(&total_p, sizeof(int),1,fp);
    fwrite(all_paragens, sizeof(Paragens), total_p, fp);
    fclose(fp);
};

void guarda_bin_l(lista_L* L){
    FILE* fp = fopen("C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\linhasmetro2.bin","ab");
    if(fp == NULL){
        printf("Erro a abrir o ficheiro!\n");
        return;
    }
    lista_L*  aux = L;

    printf("entraste?\n");
    while( *aux!= NULL ){
        printf("entrei\n");
        fwrite((*aux)->nome, sizeof(char ),15,fp);
        fwrite(&(*aux)->n_paragens, sizeof(int),1,fp);
        for(int i= 0; i < (*aux)->n_paragens; i++){
            fwrite((*aux)->array_paragens[i], sizeof(char ),20,fp);
        }
        *aux = (*aux)->prox;
    }
    fclose(fp);
};
Paragens* le_bin_p( int* total_p){
    FILE* fp = fopen("C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\paragensmetro.bin","rb");
    if(fp == NULL){
        printf("Erro a abrir o ficheiro!\n");
        return NULL;
    }

    fread(total_p, sizeof(int),1,fp);

    // Alocar memória para o array de estruturas
    Paragens * all_paragens = (Paragens *)malloc(sizeof(Paragens) * (*total_p));

    // Ler os dados do arquivo para o array
    fread(all_paragens, sizeof(Paragens), *total_p, fp);

    fclose(fp);
    return all_paragens;
};

void le_bin_l(lista_L* L){
    FILE* fp = fopen("C:\\Users\\rodri\\Documents\\isec\\2\\P\\TP\\linhasmetro2.bin","rb");
    if(fp == NULL){
        printf("Erro a abrir o ficheiro!\n");
        return;
    }
    lista_L* aux = L ;
    lista_L tmp;
    while (!feof(fp)) {

        tmp =  (lista_L) malloc(sizeof(Linhas));
       if (tmp == NULL) {
            printf("Erro ao alocar memória!\n");
           break;
        }
        printf("Erro1!\n");

        int result = fread((tmp)->nome, sizeof(char), 15, fp);
        if (result != 15) {
            free(tmp);
            break;
        }
        fread(&(tmp)->n_paragens, sizeof(int), 1, fp);

        printf("%d", (tmp)->n_paragens);
        printf("Erro1!\n");
        (tmp)->array_paragens = (char**) malloc(sizeof(char*)* (tmp)->n_paragens);
        printf("Erro1!\n");
        for(int i = 0; i < (tmp)->n_paragens ;i++){
            (tmp)->array_paragens[i] = (char*) malloc(sizeof (char) * 20);
            fread((tmp)->array_paragens[i], sizeof(char), 20, fp);
        }
        printf("Erro1!\n");
        //fread(&tmp, sizeof(tmp),1,fp);
        printf("Erro2!\n");
        (tmp)->prox = NULL;
        printf("Erro3!\n");
        if(*L == NULL){
            *L = tmp;
            (*aux) = *L;
            printf("Erro4!\n");
        }else{
            printf("Erro5!\n");
            (*aux)->prox = tmp;
            printf("Erro6!\n");
            *aux = (*aux)->prox;
        }
    }
};
