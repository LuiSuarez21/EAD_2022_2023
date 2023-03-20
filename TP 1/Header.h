/**
 * @file Header.h
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Header do projecto
 * @version EAD - Projeto Prático (Fase 1) (LESI-PL)
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief truct que define um Cliente
 * 
 */
struct client{
    int id;
    char userName[20];
    int nif;
    int cash;
    char location[50];
    char password[20];
    struct client* next;
};

/**
 * @brief Struct que define um manager;
 * 
 */
struct manager{
    char userName[20];
    int id;
    char password[20];
    char location[30];
    struct manager* next;
};

/**
 * @brief Struct que define um transporte;
 * 
 */
struct transport{
    int id;
    char typeT[20];
    int battery;
    int price;
    int autonomy;
    char available[10];
    char location[50];
    struct transport* next;
};

//------------------------------------------------------------------------------------
//Em seguida, as funções estão divididas de maneira a entender onde estão localizadas;

//-----------FuncAux.c-------------------
int Menu();

//-----------FuncClientes.c-------------------
bool AddClient(struct client** listC, char userNameC[50], char passwordC[30], char locationC[30], int nifC, int cashC);
bool AddClientFile(struct client** listC);
bool AddClientFileBin(struct client** listC);
bool ReadFileClient(struct client** listC);
int ReadFileClient2(struct client** listC);
bool AlterClient(struct client** listC,int id_New,char newUserNameC[50], char newPasswordC[30], char newLocationC[30], int newNifC, int newCashC);
bool RemoveClient(struct client** listC, int id);


//-----------FuncGestores.c-------------------
bool AddManager(struct manager** listM, char userNameG[50], char passwordG[30], char location[30]);
bool AddManagerFile(struct manager** listM);
bool AddManagerFileBin(struct manager** listM);
bool ReadFileManager(struct manager** listM);
int ReadFileManager2(struct manager** listM);
bool AlterManager(struct manager** listM,int id_New,char newPassword[20], char newUserName[20], char newLocation[50]);
bool RemoveManager(struct manager** listM, int id);

//-----------FuncTransportes.c-------------------
bool AddTransport(struct transport** listT, char type[20], char locationT[50], char availableT[10], int batteryT, int autonomyT, int priceT);
bool AddTransportFile(struct transport** listT);
bool AddTransportFileBin(struct transport** listT);
bool ReadFileTransport(struct transport** listT);
int ReadFileTransport2(struct transport** listT);
bool AlterTransport(struct transport** listT,int id_New,char newType[20], char newLocationT[50], char newAvailableT[10], int newBatteryT, int newAutonomyT, int newPriceT);
bool RemoveTransport(struct transport** listT, int id);
bool ListMobilitiesGeo (struct transport** listT, char newLocation[50]);




