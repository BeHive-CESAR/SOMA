#include <stdio.h>
#include "interface.h"
#include "login_cadastro.h"

#define TRUE 0
#define FALSE 1

void menu(){
    unsigned int op;
    printf("Selecione o que desejar: \n[1]Login\n[2]Cadastro");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        if (login() == 0){
            printf("logado");
        }else{
            printf("Usuario invalido");
        }
        break;
    
    case 2:
        cadastrar();
        break;

    default:
        printf("Opcao invalida! Tente novamente\n");
        menu();
        break;
    }
}