/**
 * @file FuncTransportes.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Ficheiro que vai manipular os dados dos meios de mobilidade;
 * @version EAD - Projeto Prático (Fase 1) (LESI-PL)
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Header.h"

/**
 * @brief Função de Inserção de Transportes;
 * 
 * @param listT 
 * @param userNameC 
 * @param passwordC 
 * @param locationC 
 * @param nifC 
 * @param cashC 
 */
bool AddTransport(struct transport** listT, char type[20], char locationT[50], char availableT[10], int batteryT, int autonomyT, int priceT)
{
    int count = 0;
    bool b = false;
    bool b2 = false;
    struct transport* new_new_transport = *listT;
    struct transport* new_transport = (struct transport*)malloc(sizeof(struct transport));

    while (new_new_transport != NULL) {
        count++;
        new_new_transport = new_new_transport->next;
    }

    strcpy(new_transport->typeT, type);
    strcpy(new_transport->location, locationT);
    strcpy(new_transport->available , availableT);
    new_transport->battery = batteryT;
    new_transport->autonomy = autonomyT;
    new_transport->price = priceT;
    new_transport->id = count;

    //Mete o next apontador na cabeça da lista;
    new_transport->next = *listT;
    //Mete a cabeça da lista a apontar para o novo cliente;
    * listT = new_transport;

    b = AddTransportFile(listT);
    b2 = AddTransportFileBin(listT);
    if (b == b2 == true)return true;
    else{return false;}
}

/**
 * @brief Função de Alteração de Transportes;
 * 
 * @param listT 
 * @param id_New 
 * @param newType 
 * @param newLocationT 
 * @param newAvailableT 
 * @param newBatteryT 
 * @param newAutonomyT 
 * @param newPriceT 
 * @return true 
 * @return false 
 */
bool AlterTransport(struct transport** listT,int id_New,char newType[20], char newLocationT[50], char newAvailableT[10], int newBatteryT, int newAutonomyT, int newPriceT) {

    int newId = id_New;
    struct transport* new;
    new = *listT;
    int i = 0;

    while(new != NULL){
        if(new->id == newId){
        strcpy(new->typeT, newType);
        strcpy(new->location, newLocationT);
        strcpy(new->available , newAvailableT);
        new->battery = newBatteryT;
        new->autonomy = newAutonomyT;
        new->price = newPriceT;
        new->id = id_New;
        i++;
        }
    }
    bool b = AddTransportFile(listT);
    if (i != 0)return true;
    else{ return false; }
}


/**
 * @brief Função que remove transportes;
 * 
 * @param listT 
 * @param id 
 * @return true 
 * @return false 
 */
bool RemoveTransport(struct transport** listT, int id) {

    struct transport* new;
    new = *listT;
    int i = 0;
    FILE* fp;
    fp=fopen("DadosTransportes.txt", "w");
    
    int aux = ReadFileTransport2(listT);

    while(new != NULL && new->id != id){
        fprintf(fp,"%d;%s;%s;%s;%d;%d;%d;\n", new->id, new->typeT, new->location, new->available, new->battery, new->autonomy, new->price);
        new=new->next;
    }
        
    fclose(fp);
    
    int b2 = ReadFileTransport2(listT);
    if (i != 0 && b2 == aux-1)return true;
    else{ return false; }
}

//-------------------Manipulação de ficheiros de texto ou binários---------------------

/**
 * @brief Função para inserir dados no ficheiro de Texto "DadosTransportes.txt"
 * 
 * @param listM 
 */
bool AddTransportFile(struct transport** listT)
{
    FILE* fp;
    fp=fopen("DadosTransportes.txt", "w");
    struct transport*new=*listT;

    if(fp==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }
    else{

        while(new!=NULL){

                fprintf(fp,"%d;%s;%s;%s;%d;%d;%d;\n", new->id, new->typeT, new->location, new->available, new->battery, new->autonomy, new->price);
                new=new->next;
        }
        
        fclose(fp);
        return true;
    }
    
}


/**
 * @brief Função para inserir dados no ficheiro de Texto "DadosGestoresBinario.txt"
 * 
 * @param listT 
 */
bool AddTransportFileBin(struct transport** listT)
{
    FILE* fp;
    fp=fopen("DadosTransportesBinario.txt", "wb");
    struct transport*new=*listT;

    if(fp==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }
    else{
        while(new!=NULL){
            fwrite((&new->id,&new->typeT,&new->location,&new->available, &new->battery, &new->autonomy, &new->price), sizeof(struct transport), 1 , fp);
            new=new->next;
        }
        fclose(fp);
        return true;
    }
}

/**
 * @brief Função que lê o ficheiro "DadosTransportes.txt" e guarda esses dados numa lista dedicada para o efeito;
 * 
 * @param listM 
 * @return true 
 * @return false 
 */
bool ReadFileTransport(struct transport** listT){

    FILE* file;
    file=fopen("DadosTransportes.txt","r");

    struct transport* previous = NULL;

    char line[100];
    char *token;

    if(file==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }

    while(fgets(line,sizeof(line),file)!=NULL){

        struct transport *new = malloc(sizeof(struct transport));
        
        token=strtok(line,";");
        new->id=atoi(token);     

        token=strtok(NULL,";");
        strcpy(new->typeT, token);

        token=strtok(NULL,";");
        strcpy(new->location, token);
        
        token=strtok(NULL,";");
        strcpy(new->available, token);

        token=strtok(NULL,";");
        new->battery=atoi(token);

        token=strtok(NULL,";");
        new->autonomy=atoi(token);

        token=strtok(NULL,";");
        new->price = atoi(token);

        new->next=NULL;

        if(previous==NULL){
            *listT = new; // coloca o primeiro nodo 
        }else{
            previous->next=new;// liga o nodo anterior ao atual
        }
        previous=new;// atualiza o elemento anterior
    }
    
    fclose(file);
    return true;
}


/**
 * @brief Retorna o número de elementos de transportes que estão registados no ficheiro
 * 
 * @param listT 
 * @return int 
 */
int ReadFileTransport2(struct transport** listT){

    FILE* file;
    file=fopen("DadosTransportes.txt","r");
    int i = 0;
    struct transport* previous = NULL;

    char line[100];
    char *token;

    if(file==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }

    while(fgets(line,sizeof(line),file)!=NULL){

        struct transport *new = malloc(sizeof(struct transport));
        
        token=strtok(line,";");
        new->id=atoi(token);     

        token=strtok(NULL,";");
        strcpy(new->typeT, token);

        token=strtok(NULL,";");
        strcpy(new->location, token);
        
        token=strtok(NULL,";");
        strcpy(new->available, token);

        token=strtok(NULL,";");
        new->battery=atoi(token);

        token=strtok(NULL,";");
        new->autonomy=atoi(token);

        token=strtok(NULL,";");
        new->price = atoi(token);

        new->next=NULL;

        if(previous==NULL){
            *listT = new; // coloca o primeiro nodo 
        }else{
            previous->next=new;// liga o nodo anterior ao atual
        }
        previous=new;// atualiza o elemento anterior
        i++;
    }
    
    fclose(file);
    return i;
}


/**
 * @brief Lista os transportes com uma determinada localização
 * 
 * @param listT 
 * @param newLocation 
 */
bool ListMobilitiesGeo (struct transport** listT, char newLocation[50]){
    struct transport* new;
    new = *listT;
    FILE* fp;
    fp=fopen("TransportesOrdenadosGeoCode.txt", "w");
    new = *listT;

    if(fp==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }
    else{
        while(new != NULL)
    {
        if(strcmp(new->location, newLocation) == 0){
        fprintf(fp,"\n-------------------------------\n");
        fprintf(fp,"Transport ID: %d\n", new->id);
        fprintf(fp,"Transport type: %s\n", new->typeT);
        fprintf(fp,"Battery level: %d\n", new->battery);
        fprintf(fp,"Price: %d\n", new->price);
        fprintf(fp,"Autonomy: %d\n", new->autonomy);
        fprintf(fp,"Available: %d\n", new->available);
        fprintf(fp,"Location: %s\n", new->location);
        }
        new = new->next;
    }

    }
    fclose(fp);
    return true;
}

