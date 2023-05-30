#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "login_cadastro.h"

#define TRUE 0
#define FALSE 1

void main_menu(){
    unsigned int op;
    printf("Selecione uma das opções abaixo:\n[1]Login\n[2]Acesso Coordenacao\n[0]Finalizar Programa\n");
    scanf("%d", &op);
    system("cls");

    switch (op)
    {
    case 1:
        if (login() == 0){
            system("cls");
            printf("Logado\n");
        }else{
            system("cls");
            printf("Nao foi possivel realizar o login\n");
            main_menu();
            
        }
        break;
    
    case 2:
        if (login_coord() == 0){
            if (!cadastrar()){
                main_menu(); // Nesta Parte iremos chamar a função responsavel pela interface da coordenação
            }
        }else{
            system("cls");
            printf("Credenciais Invalidos!\n");
            main_menu();
        }
        main_menu();
        break;
    
    case 0:
        system("cls");
        printf("Obrigado e ate a proxima :) \n");
        exit(0);
        break;

    default:
        system("cls");
        printf("Opcao invalida! Tente novamente\n");
        main_menu();
        break;
    }
}