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

    switch (op) // Switch que define para qual menu o usuario irá a depender do seu id cadastrado
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

    case 0: // Ao selecionar a opção de finalizar o programa, o usuario será direcionado para o case 0
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
    // Iniciação das variaveis
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};
    char *email;
    Usuario usuario_desejado;
    
    system("cls");
    printf("--- Coordenacao ---\n");
    printf("[1]Anestesia\n[2]Cardiologia\n[3]Cirurgia Geral\n[4]Clinica Geral\n[0]Sair da conta\nSelecione o que desejar: ");
    scanf("%d", &op);

    // Opções para cadastrar um novo usuario
    if (op > 0 && op <= 4)
    {
        printf("====%s====\n", residencias[op-1]);
        printf("[+]Cadastrar novo usuario[/]Voltar[?]Acessar usuario\n");

        printf("Preceptores: \n");
        printar_residentes_preceptores(op, 1); // Printa no terminal a lista de todos os preceptores cadastrados
        printf("Residentes: \n");
        printar_residentes_preceptores(op, 2); // Printa no terminar a lista de todos os residentes cadastrados

        scanf("\n%c", &opcao);
        switch(opcao)
        {
            case '+': // Opção para cadastrar um novo usuario
                cadastrar(op);
                menu_coordenacao(); // Ao casdastrar corretamente, o usuario será direcionado de volta ao menu da coordenação
                break;

            case '/': // Opção de voltar
                menu_coordenacao(); // Caso o coordenador desista de cadastrar um novo usuario, sendo direcionado de volta ao menu da coordenação
                break;

            case '?': // Opção de visualizar o usuario (preceptor ou residente)
                printf("Selecione o usuario que deseja visualizar: ");
                scanf(" %[^\n]", usuario_desejado.email);

                if(preceptor_ou_residente(usuario_desejado) == 0) // Usuario não foi encontrado
                {
                    printf("\nResidente nao encontrado! Tente novamente! ");
                }
                else if(preceptor_ou_residente(usuario_desejado) == 2) // Usuario foi encontrado e é um residente
                {
                    int escolha; // Variavel para a escolha das opções seguintes
                    printf("[1]Atividades\n[2]Notas\n[3]FeedBacks\n[0]Voltar\nEscolha a opcao que deseja: "); // Opções do que o usuario coordenação deseja visualizar do residente selecionado previamente
                    scanf("%d", &escolha);

                    switch(escolha)
                    {
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

                    
                }
                else // Usuario foi encontrado e é preceptor
                {
                    int escolha2; // Variavel para a escolha das opções seguintes
                    printf("[1]Atividades\n[2]FeedBacks\n[0]Voltar\nEscolha a opcao que deseja: "); // Opções do que o usuario coordenação deseja visualizar do preceptor selecionado previamente
                    scanf("%d", &escolha2);

                    switch(escolha2)
                    {
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
                printf("\nDigite [0] para voltar "); // Voltar para o menu da coordenação
                scanf("%d", &op);
                menu_coordenacao();
                break;
            default:
                printf("Opcao invalida!"); // Opção digitada não existe nas opções presentes
                menu_coordenacao();
        }
    }
    else if(op == 0) // Opção para sair do menu da coordenação
    {
        main_menu(); // Direcionado de volta ao menu principal
    }
    else
    {
        printf("Opcao invalida! Tente novamente\n"); // Opção digitada não existe | Direcionado de volta ao inicio do menu da coordenação
        menu_coordenacao();
    }
}
//Função responsável pela interface do menu do residente (ações que ele pode realizar no sistema)
void menu_residente()
{
    //Iniciação das variaveis
    unsigned int op;
    char opcao, voltar;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};


    system("cls");
    printf("--- Residentes ---\n");
    printf("%s\n", usuario_logado.email); // Printa o email do usuario que logou no sistema como residente
    printf("%s | Residentes\n", residencias[usuario_logado.idResidencia -1]); // Printa de qual residencia o residente pertence de acordo de como foi cadastrado

    printf("[1]Ver atividades\n[2]Visulizar avaliacoes\n[3]Visualizar feedback\n"
    "[4]Avaliacao do feedback\n[0]Sair da conta\nSelecione qual opcao deseja visualizar: ");
    scanf("%d", &op);
    switch(op) 
    {
        case 1:
            ver_atividades_residente(); // Atividades do residente que está logado
            break;
        case 2:
            ver_nota_residente(); // Notas do residente que está logado
            printf("[/]Voltar ");
            scanf("\n%c", &voltar);
            menu_residente(); // Ao visualizar e apertar para voltar, volta para o inicio do menu do residente
            break;
        case 3:
            ver_feedback_residente(); // Feedbacks feitos pelos preceptores para o residente
            printf("[/]Voltar ");
            scanf("\n%c", &voltar);
            menu_residente(); // Ao visualizar e apertar para voltar, volta para o inicio do menu do residente
            break;
        case 4:
            fazer_feedback_para_preceptor(); // Opção para realizar um feedback disponivel para o preceptor
            break;
        case 0:
            main_menu(); // Saiu da conta, volta para o menu principal
            break;
        default:
            printf("opçao invalida! tente novamente\n"); // Opção invalida, de volta ao menu do residente
            menu_residente();
            break;
    }

}
//Função responsável pela interface do menu do preceptor (ações que ele pode realizar no sistema)
void menu_preceptor() 
{
    // Iniciação das variaveis
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};


    system("cls");
    printf("--- Preceptor ---\n");
    printf("%s\n", usuario_logado.email); // Mostra o email do preceptor que está logado

    printf("%s | Preceptor", residencias[usuario_logado.idResidencia -1]); // Residencia do preceptor que está logado de acordo de como foi cadastrado

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
        printf("Opcao invalida! Tente novamente.\n"); // Opção invalida, volta para o menu do preceptor
        menu_preceptor();
        break;
    }
}