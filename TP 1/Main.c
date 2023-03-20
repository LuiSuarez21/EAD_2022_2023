/**
 * @file Main.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Main do projecto da fase 1
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
 * @brief Função main 
 * 
 * @return int 
 */
int main ()
{

setlocale(LC_ALL, "Portuguese");

struct client* c = NULL;
struct manager * m = NULL;
struct transport * t = NULL;
int opc, count;
bool b;
b = false;
opc = count = 0;

b = ReadFileClient(&c);
b = ReadFileManager(&m);
b = ReadFileTransport(&t);
if (b == false){
    printf("\nErro a ler os dados inicias do programa!!!\n");
    return 0;
}
opc = Menu();

while (opc != 13)
{
   if (count != 0) opc = Menu();
   //Switch case que vai funcionar dependendo do input do utilizador;
   //As adições de certos Clientes ou transportes são feitas automaticamente aqui na função, para ilustrar apenas o bom funcionamento das funções;
   switch (opc)
   {
    case 1:

        b = AddClient(&c, "LuisSS", "fsefsf","Braga", 34343242, 321);
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }
        break;

    case 2:
        b = RemoveClient(&c, 0);
        if (b == false)wprintf(L"\nErro na remoção de dados!\n");
        else{
            wprintf(L"\nSucesso!Remoção bem feita!\n");
        }
        break;
    case 3:

        b = AlterClient(&c, 0, "Luis","mmm","Braga",2343242432,343);
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }
        break;
    case 4:

        b = AddManager(&m, "Jose", "fsgsegsegsse", "Braga");
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }

        b = AddManager(&m, "Luis", "fsgsegsegsse", "Braga");
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }
        break;

    case 5:
        b = RemoveManager(&m, 0);
        if (b == false)wprintf(L"\nErro na remoção de dados!\n");
        else{
            wprintf(L"\nSucesso!Remoção bem feita!\n");
        }
        break;
    case 6:

        b = AlterManager(&m, 1, "mmm", "Tiago", "Porto");
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }
        break;
    case 7:

        b = AddTransport(&t,"bicicleta","Braga","true",21,23,21);
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }

        b = AddTransport(&t,"trotinete","Porto","true",21,21,21);
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }
        break;

    case 8:
        b = RemoveTransport(&t, 0);
        if (b == false)wprintf(L"\nErro na remoção de dados!\n");
        else{
            wprintf(L"\nSucesso!Remoção bem feita!\n");
        }
        break;
    case 9:
        b = AlterTransport(&t, 1, "bicicleta", "Braga", "True",21,21,32);
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }
        break;
    case 10:
        break;
    case 11:
        /*
        b = DescendingListByAutonomy(&t);
        if (b == false)wprintf(L"\nErro na inserção de dados!\n");
        else{
            wprintf(L"\nSucesso!Inserção bem feita!\n");
        }
        */
        break;
    case 12:
        b = ListMobilitiesGeo(&t,"Braga");
        if (b == false)wprintf(L"\nErro na listagem dos dados!\n");
        else{
            wprintf(L"\nSucesso!Listagem bem feita!\n");
        }
        break;
    case 13:
        break;
    default:
        break;
    }
    count++;

}

free(m);
free(t);
free(c);

    return 0;
}
