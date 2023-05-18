#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "login_cadastro.h"

#define TRUE 0
#define FALSE 1

void menu(){
    unsigned int op;
    printf("[1]Login\n[2]Cadastro\n[0]Finalizar Programa\nSelecione o que desejar: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        if (login() == 0){
            printf("logado");
        }else{
            printf("Nao foi possivel realizar o login\n");
            menu();
        }
        break;
    
    case 2:
        cadastrar();
        menu();
        break;
    
    case 0:
        printf("Obrigado e ate a proxima :) ");
        exit(0);
        break;

    default:
        printf("Opcao invalida! Tente novamente\n");
        menu();
        break;
    }
}