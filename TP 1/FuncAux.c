/**
 * @file FuncAux.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Este ficheiro serve para funções que nos auxilam com o resto do programa
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
 * @brief Função que imprime um menu para o utilizador poder utilizar
 * 
 * @return int 
 */
int Menu(){

   setlocale(LC_ALL, "Portuguese");
   int opc;
   opc = 0;

   printf("\n----------------Menu--------------------\n");
   printf("1) Adicionar um Cliente;\n");
   printf("2) Remover um Cliente;\n");
   printf("3) Alterar um Cliente;\n");
   printf("4) Adicionar um Gestor;\n");
   printf("5) Remover um Gestor;\n");
   printf("6) Alterar um Gestor;\n");
   printf("7) Adicionar um Transporte;\n");
   printf("8) Remover um Transporte;\n");
   printf("9) Alterar um Transporte;\n");
   wprintf(L"10) Registo do aluguer de um determinado meio de mobilidade elétrica;\n");
   wprintf(L"11) Listagem dos meios de mobilidade elétrica por ordem decrescente de autonomia;\n");
   wprintf(L"12) Listagem dos meios de mobilidade elétrica existentes numa localização com determinado geocódigo;\n");
   wprintf(L"13) Sair;\n");
   wprintf(L"\n\nInsira a opção que deseja selecionar: ");
   scanf("%d", &opc);
    
    while (opc < 0 || opc > 13 || opc == 0)
    {
        wprintf(L"\nErro! Por favor insira outro número entre 1 e 13!\n");
        wprintf(L"Insira a opção que deseja selecionar: ");
        scanf("%d", &opc);

    }
    return opc;
}