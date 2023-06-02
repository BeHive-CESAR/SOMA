#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "login_cadastro.h"

#define TRUE 0
#define FALSE 1

void main_menu(){
    unsigned int op, id;
    printf("[1]Login\n[0]Finalizar Programa\nSelecione o que desejar: ");
    scanf("%d", &op);
    system("cls");

    switch (op){
    case 1:

        switch (id=login()){

        case 1:
            printf("--- Preceptor ---");
            break;
        
        case 2:
            printf("--- Residente ---");
            break;
        
        case 3:
            printf("--- Coordenacao ---\n");
            menu_coordenacao();
            break;

        default:
            printf("Login Invalido! Tente novamente\n");
            main_menu();
            break;
        }
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

void menu_coordenacao(){
    unsigned int op;

    printf("[1]Cadastrar novos usuarios\n[0]Sair da conta\nSelecione o que desejar: ");
    scanf("%d", &op);

    switch(op){
        case 1:
            cadastrar();
            break;
        
        case 0:
            main_menu();
            break;
        
        default:
            printf("Opcao invalida! Tente novamente\n");
            menu_coordenacao();
            break;
    }
}