#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "login_cadastro.h"
#include "preceptor.h"
#include "residente.h"
#include "residentes_preceptores.h"

extern Usuario usuario_logado;


// Função para iniciar o programa e direcionar o usuario
void main_menu() 
{
    system("cls");
    unsigned int op, id;
    printf("[1]Login\n[0]Finalizar Programa\nSelecione o que desejar: ");
    scanf("%d", &op);
    system("cls");

    switch (op)
    {
    case 1:

        switch (id=login())
        {
        case 1:
            menu_preceptor();
            break;
        
        case 2:
            menu_residente();
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
//Função responsável pela interface do menu da coordenação (ações que ela pode realizar no sistema)
void menu_coordenacao()
{
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};
    char *email;
    Usuario usuario_desejado;
    
    system("cls");
    printf("--- Coordenacao ---\n");
    printf("[1]Anestesia\n[2]Cardiologia\n[3]Cirurgia Geral\n[4]Clinica Geral\n[0]Sair da conta\nSelecione o que desejar: ");
    scanf("%d", &op);

    if (op > 0 && op <= 4)
    {
        printf("====%s====\n", residencias[op-1]);
        printf("[+]Cadastrar novo usuario[/]Voltar[?]Acessar usuario\n");

        printf("Preceptores: \n");
        printar_residentes_preceptores(op, 1);
        printf("Residentes: \n");
        printar_residentes_preceptores(op, 2);

        scanf("\n%c", &opcao);
        switch(opcao)
        {
            case '+':
                cadastrar(op);
                menu_coordenacao();
                break;

            case '/':
                menu_coordenacao();
                break;

            case '?':
                printf("Selecione o usuario que deseja visualizar: ");
                scanf(" %[^\n]", usuario_desejado.email);

                if(preceptor_ou_residente(usuario_desejado) == 0){
                    printf("\nResidente nao encontrado! Tente novamente! ");
                }else if(preceptor_ou_residente(usuario_desejado) == 2){
                    int escolha;
                    printf("[1]Atividades\n[2]Notas\n[3]FeedBacks\n[0]Voltar\nEscolha a opcao que deseja: ");
                    scanf("%d", &escolha);

                    switch(escolha){
                        case 1:
                            ver_atividades_residente();
                            break;
                        
                        case 2:
                            printar_notas_residente(usuario_desejado);
                            break;
                        
                        case 3:
                            ver_feedback_residente();
                            break;
                        
                        default:
                            menu_coordenacao();
                            break;

                    }

                    
                }else{
                    int escolha2;
                    printf("[1]Atividades\n[2]FeedBacks\n[0]Voltar\nEscolha a opcao que deseja: ");
                    scanf("%d", &escolha2);

                    switch(escolha2){
                        case 1:
                            ver_atividades_residente();
                            break;
                        
                        case 2:
                            ver_feedback_preceptor_coord();
                            break;
                        
                        default:
                            menu_coordenacao();
                            break;
                    }
                }
                printf("\nDigite [0] para voltar ");
                scanf("%d", &op);
                menu_coordenacao();
                break;
            default:
                printf("Opcao invalida!");
                menu_coordenacao();
        }
    }
    else if(op == 0)
    {
        main_menu();
    }
    else
    {
        printf("Opcao invalida! Tente novamente\n");
        menu_coordenacao();
    }
}
//Função responsável pela interface do menu do residente (ações que ele pode realizar no sistema)
void menu_residente()
{
    unsigned int op;
    char opcao, voltar;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};


    system("cls");
    printf("--- Residentes ---\n");
    printf("%s\n", usuario_logado.email);
    printf("%s | Residentes\n", residencias[usuario_logado.idResidencia -1]);

    printf("[1]Ver atividades\n[2]Visulizar avaliacoes\n[3]Visualizar feedback\n"
    "[4]Avaliacao do feedback\n[0]Sair da conta\nSelecione qual opcao deseja visualizar: ");
    scanf("%d", &op);
    switch(op) 
    {
        case 1:
            ver_atividades_residente();
            break;
        case 2:
            ver_nota_residente();
            printf("[/]Voltar ");
            scanf("\n%c", &voltar);
            menu_residente();
            break;
        case 3:
            ver_feedback_residente();
            printf("[/]Voltar ");
            scanf("\n%c", &voltar);
            menu_residente();
            break;
        case 4:
            fazer_feedback_para_preceptor();
            break;
        case 0:
            main_menu();
            break;
        default:
            printf("opçao invalida! tente novamente\n");
            menu_residente();
            break;
    }

}
//Função responsável pela interface do menu do preceptor (ações que ele pode realizar no sistema)
void menu_preceptor() 
{
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};


    system("cls");
    printf("--- Preceptor ---\n");
    printf("%s\n", usuario_logado.email);

    printf("%s | Preceptor", residencias[usuario_logado.idResidencia -1]);

    printf("\n\n[1]Atividades\n[2]Avisos\n[3]Criar atividade\n[4]Ver Feedbacks\n[5]Lista de Residentes" //opções disponíveis
    "\n[0]Sair da Conta\nSelecione o que deseja: ");

    scanf("%d", &op);

    switch (op) //Switch feito para chamar as funções responsáveis por cada atividade
    {
    case 1:
        //atividades
        ver_atividades_preceptor();
        break;

    case 2:
        //avisos
        avisos_preceptor();
        break;

    case 3:
        //Nova atividade
        criar_atividade();
        break;
    
    case 4:
        //Ver feedbacks
        ver_feedback_preceptor();
        break;

    case 5:
        //residentes
        lista_residentes();
        break;

    case 0:
        //sair
        main_menu();
        break;
        
    default:
        system("cls");
        printf("Opcao invalida! Tente novamente.\n");
        menu_preceptor();
        break;
    }
}