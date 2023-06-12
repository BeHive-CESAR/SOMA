#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "login_cadastro.h"
#include "preceptor.h"
#include "residente.h"
#include "residentes_preceptores.h"

extern Usuario usuario_logado;

// Coisas Gerais
// Lembrar de pedir para expandir o terminal para melhor visualização do programa no README
// colocar um define para o numero 7 que é a quantidade de criterios do feedback em fazer_feedback_para_preceptor
// colocar um define para o numero 6 que é a quantidade de criterios do feedback em fazer_feedback_para_residente
// Ajeitar os system("cls"). Em algumas funcoes quando o usario digita algo errado ou é confirmado o envio de algum formulario e chamamos novamente a função o "cls" apaga imediatamente o aviso de erro ou a confirmacao de envio
// Padronizar os botoes que estamos usando nas funcoes. Ex.: confirmar envio ser o botao "+". Ex.2: voltar para tela anterior ser o botao "/"

// Coisas da Interface do Figma
// Quando o feedback fica disponivel, quem adiciona o feedback? Seja para o preceptor ou residente, mas quem adiciona o feedback na pagina de avisos?
// Na pagina de avisos aparece apenas Feedback disponivel. Deveria ter algum botao para ser apertado? Atualmente apenas esta um aviso. Acredito que nao seja muito "claro" de que o usuario deve apertar no aviso em si

// Coisas do Residente
// colocar opcao de cancelar o envio das notas do feedback na funcao fazer_feedback_para_preceptor
// mudar o conteudo da variavel criterio para ficar de acordo com o figma
// mudar printf na função fazer_feedback_para_preceptor para ficar de acordo com o figma
// mudar nome das variaveis na funcao fazer_feedback_para_preceptor. Atualmente esta vago/confuso o que cada variavel faz e é
// mudar printf dentro do if de checagem 1 < || > 5 para numero, visto que usuario nao digita a avaliacao e sim o numero que deseja
// mudar printf de fazer comentario sobre o preceptor na funcao fazer_feedback_para_preceptor para ficar de acordo com o figma 
// Verificar se peu colocou as #include dos arquivos .h na ordem correta, com suas dependencias verificadas para estar na ordem de quem depende de quem

// Coisas do Preceptor
// fazer pagina de feedback dos residentes para o preceptor -> em processo (peu)
// checar se caso digite um numero maior que 5 e menor que 1, na proximo vez digitar o numero certo e ter certeza que o numero correto ira para o txt na funcao fazer_feedback_para_residente
// Falta apenas a função de fazer a visualização do feedback que os residentes fizeram do preceptor
// Na funcao fazer_feedback_para_residente apos confirmar o envio do feedback o programa encerra. why?
// Adicionar o nome do preceptor que esta fazendo o feedback ao residente no arquivo de feedback_preceptor
// funcao fazer_feedback_para_residente nao esta funcionando corretamente. 
    // 1. o comentario que é adicionado primeiro fica se repetindo em todos os outros feedbacks
    // 2. Esta apagando qualquer residente que ja estivesse presente no arquivo


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

void menu_coordenacao()
{
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};
    char *email;
    
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
                printf("Digite o nome do usuario: ");
                scanf(" %[^\n]", email);
                // dados do usuario
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


void menu_residente()
{
    unsigned int op;
    char opcao;
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
        // case 1:
        //     ver_atividades_residente();
        //     break;
        case 2:
            printar_notas_residente(usuario_logado);
            break;
        case 3:
            ver_feedback_residente();
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

void menu_preceptor()
{
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};


    system("cls");
    printf("--- Preceptor ---\n");
    printf("%s\n", usuario_logado.email);
    printf("%s | Preceptor", residencias[usuario_logado.idResidencia -1]);

    printf("\n\n[1]Atividades\n[2]Avisos\n[3]Criar atividade\n[4]Residentes\n[5]Sair da Conta\nSelecione o que deseja: ");
    scanf("%d", &op);

    switch (op)
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
        //residentes
        lista_residentes();
        break;

    case 5:
        //sair
        main_menu();
        break;
    default:
        printf("Opcao invalida! Tente novamente.\n");
        menu_preceptor();
        break;
    }
}