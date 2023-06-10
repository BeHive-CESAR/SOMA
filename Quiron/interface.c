#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "login_cadastro.h"
#include "residentes_preceptores.h"


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
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};
    char *email;
    
    system("cls");
    printf("--- Coordenacao ---\n");
    printf("[1]Anestesia\n[2]Cardiologia\n[3]Cirurgia Geral\n[4]Clinica Geral\n[0]Sair da conta\nSelecione o que desejar: ");
    scanf("%d", &op);

    if (op > 0 && op <= 4){
        printf("====%s====\n", residencias[op-1]);
        printf("[+]Cadastrar alunos[/]Voltar[?]Acessar usuario\n");

        printf("Preceptores: \n");
        printar_residentes_preceptores(op, 1);
        printf("Residentes: \n");
        printar_residentes_preceptores(op, 2);

        scanf("\n%c", &opcao);
        switch(opcao){
            case '+':
                cadastrar(op);
                menu_coordenacao();
                break;

            case '/':
                menu_coordenacao();
                break;

            case '?':
                printf("Digite o nome do usuario: ");
                scanf(" %[^\n]", email);
                // dados do usuario
            default:
                printf("Opcao invalida!");
                menu_coordenacao();
        }
    }else if(op == 0){
        main_menu();
    }else{
        printf("Opcao invalida! Tente novamente\n");
        menu_coordenacao();
    }
}


void menu_residente(){
    unsigned int op;

    printf("[1] Ver atividades\n[2]Visulizar avaliações\n[3]Visualizar feedback\n[4]Avaliaçao do feedback\n[0]Sair da conta\nSelecione qual opçao deseja visualizar: ");
    scanf("%d", &op);
    switch(op) {
        case 1:
            // ver_atividades();
            break;
        case 2:
            // ver_avaliacoes();
            break;
        case 3:
            // ver_feedbacks();
            break;
        case 4:
            // avaliar_feedback();
            break;
        case 0:
            // main_menu();
            break;
        default:
            printf("opçao invalida! tente novamente\n");
            menu_residente();
            break;
    }

}