/**
 * @file FuncGestores.c
 * @author your name (you@domain.com)
 * @brief Ficheiro que vai manipular os dados dos Gestores
 * @version EAD - Projeto Prático (Fase 1) (LESI-PL)
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#include "Header.h"


/**
 * @brief Função de Inserção de Gestores
 * 
 * @param listM 
 * @param userNameG 
 * @param passwordG 
 * @param locationG 
 * @return true 
 * @return false 
 */
bool AddManager(struct manager** listM, char userNameG[50], char passwordG[30], char locationG[30])
{
    int count;
    count = 0;
    bool b, b2;
    b = b2 = false; 
    struct manager* new_new_manager = *listM;
    struct manager* new_manager = (struct manager*)malloc(sizeof(struct manager));

    while (new_new_manager != NULL) {
        count++;
        new_new_manager = new_new_manager->next;
    }

    strcpy(new_manager->userName, userNameG);
    strcpy(new_manager->password, passwordG);
    strcpy(new_manager->location, locationG);
    new_manager->id = count;
    
    //Mete o next apontador na cabeça da lista;
    new_manager->next = *listM;
    
    //Mete a cabeça da lista a apontar para o novo cliente;
    *listM = new_manager;

    b = AddManagerFile(listM);
    b2 = AddManagerFileBin(listM);
    if (b == b2 == true)return true;
    else{ return false; }
}


/**
 * @brief Função de Remoção de Gestores;
 * 
 * @param listT 
 * @param id 
 * @return true 
 * @return false 
 */
bool RemoveManager(struct manager** listM, int id) {

    struct manager* new;
    new = *listM;
    int i = 0;
    FILE* fp;
    fp=fopen("DadosGestores.txt", "w");
    
    int aux = ReadFileManager2(listM);

    while(new != NULL && new->id != id){
        fprintf(fp,"%d;%s;%s;%s;\n", new->id, new->userName, new->password, new->location);
        new=new->next;
    }
        
    fclose(fp);
    
    int b2 = ReadFileManager2(listM);
    if (i != 0 && b2 == aux-1)return true;
    else{ return false; }
    
}


/**
 * @brief Função de Alteração de Gestores;
 * 
 * @param listM 
 * @param id_New 
 * @param newPassword 
 * @param newUserName 
 * @param newLocation 
 * @return true 
 * @return false 
 */
bool AlterManager(struct manager** listM,int id_New,char newPassword[20], char newUserName[20], char newLocation[50]) {

    int newId = id_New;
    struct manager* new;
    new = *listM;
    int i = 0;

    while(new != NULL){
        if(new->id == newId){
        strcpy(new->userName, newUserName);
        strcpy(new->password, newPassword);
        strcpy(new->location, newLocation);
        new->id = id_New;
        new=new->next;
        i++;
        }
    }
    bool b = AddManagerFile(listM);
    if (i != 0)return true;
    else{ return false; }
}


//-------------------Manipulação de ficheiros de texto ou binários---------------------

/**
 * @brief Função para inserir dados no ficheiro de Texto "DadosGestores.txt"
 * 
 * @param listM 
 */
bool AddManagerFile(struct manager** listM)
{
    FILE* fp;
    fp=fopen("DadosGestores.txt", "w");
    struct manager*new=*listM;

    if(fp==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }
    else{

        while(new!=NULL){

        fprintf(fp,"%d;%s;%s;%s;\n", new->id, new->userName, new->password, new->location);
        new=new->next;

        }
        fclose(fp);
        return true;
    }
    
}

/**
 * @brief Função para inserir dados no ficheiro de Texto "DadosGestoresBinario.txt" 
 * 
 * @param listM 
 */
bool AddManagerFileBin(struct manager** listM)
{
    FILE* fp;
    fp=fopen("DadosGestoresBinario.txt", "wb");
    struct manager*new=*listM;
    
    if(fp==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }
    else
    {
        while(new!=NULL){

            fwrite((&new->id,&new->userName,&new->password,&new->location), sizeof(struct manager), 1 , fp);
            new=new->next;

        }
        fclose(fp);
        return true;
    }
}


/**
 * @brief Função que lê o ficheiro "DadosGestores.txt" e guarda esses dados numa lista dedicada para o efeito;
 * 
 * @param listM 
 * @return true 
 * @return false 
 */
bool ReadFileManager(struct manager** listM){

    FILE* file;
    file=fopen("DadosGestores.txt","r");

    struct manager* previous = NULL;

    char line[100];
    char *token;

    if(file==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }

    while(fgets(line,sizeof(line),file)!=NULL){

        struct manager *new = malloc(sizeof(struct manager));
        
        token=strtok(line,";");
        new->id=atoi(token);     

        token=strtok(NULL,";");
        strcpy(new->userName, token);

        token=strtok(NULL,";");
        strcpy(new->password, token);

        token=strtok(NULL,";");
        strcpy(new->location, token);

        new->next=NULL;

        if(previous==NULL){
            *listM = new; // coloca o primeiro nodo 
        }else{
            previous->next=new;// liga o nodo anterior ao atual
        }
        previous=new;// atualiza o elemento anterior
    }
    
    fclose(file);
    return true;
}


/**
 * @brief Lê o número de elementos do ficheiro;
 * 
 * @param listM 
 * @return true 
 * @return false 
 */
int ReadFileManager2(struct manager** listM){

    FILE* file;
    file=fopen("DadosGestores.txt","r");
    int i = 0;
    struct manager* previous = NULL;

    char line[100];
    char *token;

    if(file==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }

    while(fgets(line,sizeof(line),file)!=NULL){

        struct manager *new = malloc(sizeof(struct manager));
        
        token=strtok(line,";");
        new->id=atoi(token);     

        token=strtok(NULL,";");
        strcpy(new->userName, token);

        token=strtok(NULL,";");
        strcpy(new->password, token);

        token=strtok(NULL,";");
        strcpy(new->location, token);

        new->next=NULL;

        if(previous==NULL){
            *listM = new; // coloca o primeiro nodo 
        }else{
            previous->next=new;// liga o nodo anterior ao atual
        }
        previous=new;// atualiza o elemento anterior
        i++;
    }
    
    fclose(file);
    return i;
}
