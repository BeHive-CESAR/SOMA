#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "login_cadastro.h"

#define TRUE 0
#define FALSE 1

void main_menu(){
    unsigned int op;
    printf("[1]Login\n[2]Acesso Coordenacao\n[0]Finalizar Programa\nSelecione o que desejar: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        if (login() == 0){
            printf("logado");
        }else{
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
            printf("Credenciais Invalidos!\n");
            main_menu();
        }
        main_menu();
        break;
    
    case 0:
        printf("Obrigado e ate a proxima :) ");
        exit(0);
        break;

    default:
        printf("Opcao invalida! Tente novamente\n");
        main_menu();
        break;
    }
}