/**
 * @file FuncClientes.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Tem as funções que manipulam os Clientes
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
 * @brief Função de Inserção de Clientes
 * 
 * @param listC 
 * @param userNameC 
 * @param passwordC 
 * @param locationC 
 * @param nifC 
 * @param cashC 
 */
bool AddClient(struct client** listC, char userNameC[50], char passwordC[30], char locationC[30], int nifC, int cashC)
{
    int count = 0;
    bool b, b2;
    b = b2 = false;
    struct client* new_new_client = *listC;
    struct client* new_client = (struct client*)malloc(sizeof(struct client));

    while (new_new_client != NULL) {
        count++;
        new_new_client = new_new_client->next;
    }

    strcpy(new_client->userName, userNameC);
    strcpy(new_client->password, passwordC);
    strcpy(new_client->location, locationC);
    new_client->cash = cashC;
    new_client->nif = nifC;
    new_client->id = count;

    //Mete o next apontador na cabeça da lista;
    new_client->next = *listC;

    //Mete a cabeça da lista a apontar para o novo cliente;
    *listC = new_client;

    b = AddClientFile(listC);
    b2 = AddClientFileBin(listC);
    if(b == b2 == true) return true;
    else{ return false; }

}

/**
 * @brief Função de Remoção de Clientes;
 * 
 * @param listT 
 * @param id 
 * @return true 
 * @return false 
 */
bool RemoveClient(struct client** listC, int id) {

    struct client* new;
    new = *listC;
    int i = 0;
    FILE* fp;
    fp=fopen("DadosClientes.txt", "w");
    
    int aux = ReadFileClient2(listC);

    while(new != NULL && new->id != id){
        fprintf(fp,"%d;%s;%s;%s;%d;%d;\n", new->id, new->userName, new->password, new->location, new->nif, new->cash);
        new=new->next;
    }
        
    fclose(fp);
    
    int b2 = ReadFileClient2(listC);
    if (i != 0 && b2 == aux-1)return true;
    else{ return false; }
    
}

/**
 * @brief Função de Alteração de Clientes;
 * 
 * @param listT 
 * @param id_New 
 * @param newUserNameC 
 * @param newPasswordC 
 * @param newLocationC 
 * @param newNifC 
 * @param newCashC 
 * @return true 
 * @return false 
 */
bool AlterClient(struct client** listC,int id_New,char newUserNameC[50], char newPasswordC[30], char newLocationC[30], int newNifC, int newCashC) {

    int newId = id_New;
    struct client* new;
    new = *listC;
    int i = 0;

    while(new != NULL){
        if(new->id == newId){
        strcpy(new->userName, newUserNameC);
        strcpy(new->password, newPasswordC);
        strcpy(new->location, newLocationC);
        new->cash = newCashC;
        new->nif = newNifC;
        new->id = id_New;
        i++;
        }
    }
    
    bool b = AddClientFile(listC);
    if (i != 0)return true;
    else{ return false; }
}


//-------------------Manipulação de ficheiros de texto ou binários---------------------

/** 
 * @brief Função para inserir dados no ficheiro de Texto "DadosClientes.txt
 * 
 * @param listC 
 * @return true 
 * @return false 
 */
bool AddClientFile(struct client** listC)
{
    FILE* fp;
    fp=fopen("DadosClientes.txt", "w");
    struct client *new = *listC;

    if(fp==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }
    else{

        while(new!=NULL){

        fprintf(fp,"%d;%s;%s;%s;%d;%d;\n", new->id, new->userName, new->password, new->location, new->nif, new->cash);
        new=new->next;

        }
        fclose(fp);
        return true;
    }
    
}


/**
 * @brief Função para inserir dados no ficheiro de Texto "DadosClientesBinario.txt"
 * 
 * @param listC 
 * @return true 
 * @return false 
 */
bool AddClientFileBin(struct client** listC)
{
    FILE* fp;
    fp=fopen("DadosClientesBinario.txt", "wb");
    struct client*new=*listC;

    if(fp==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }
    else{

        while(new!=NULL){

        fwrite((&new->id,&new->userName,&new->password,&new->location, &new->nif, &new->cash), sizeof(struct client), 1 , fp);
        new=new->next;

        }

        fclose(fp);
        return true;
    }
    
}

/**
 * @brief Função que lê o ficheiro "DadosClientes.txt" e guarda esses dados numa lista dedicada para o efeito;
 * 
 * @param listC 
 * @return true 
 * @return false 
 */
bool ReadFileClient(struct client** listC){

    FILE* file;
    file=fopen("DadosClientes.txt","r");

    struct client* previous = NULL;

    char line[100];
    char *token;

    if(file==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }

    while(fgets(line,sizeof(line),file)!=NULL){

        struct client *new = malloc(sizeof(struct client));
        
        token=strtok(line,";");
        new->id=atoi(token);     

        token=strtok(NULL,";");
        strcpy(new->userName, token);

        token=strtok(NULL,";");
        strcpy(new->password, token);

        token=strtok(NULL,";");
        strcpy(new->location, token);

        token=strtok(line,";");
        new->nif=atoi(token);    

        token=strtok(line,";");
        new->cash=atoi(token);    

        new->next=NULL;

        if(previous==NULL){
            *listC = new; // coloca o primeiro nodo 
        }else{
            previous->next=new;// liga o nodo anterior ao atual
        }
        previous=new;// atualiza o elemento anterior
    }
    
    fclose(file);
    return true;
}

/**
 * @brief Lê o número de elementos do ficheiro
 * 
 * @param listC 
 * @return int 
 */
int ReadFileClient2(struct client** listC){

    FILE* file;
    file=fopen("DadosClientes.txt","r");
    int i = 0;

    struct client* previous = NULL;

    char line[100];
    char *token;

    if(file==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }

    while(fgets(line,sizeof(line),file)!=NULL){

        struct client *new = malloc(sizeof(struct client));
        
        token=strtok(line,";");
        new->id=atoi(token);     

        token=strtok(NULL,";");
        strcpy(new->userName, token);

        token=strtok(NULL,";");
        strcpy(new->password, token);

        token=strtok(NULL,";");
        strcpy(new->location, token);

        token=strtok(line,";");
        new->nif=atoi(token);    

        token=strtok(line,";");
        new->cash=atoi(token);    

        new->next=NULL;

        if(previous==NULL){
            *listC = new; // coloca o primeiro nodo 
        }else{
            previous->next=new;// liga o nodo anterior ao atual
        }
        previous=new;// atualiza o elemento anterior
        i++;
    }
    
    fclose(file);
    return i;
}




