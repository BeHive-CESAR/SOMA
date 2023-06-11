#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "login_cadastro.h"
#include "residentes_preceptores.h"


void main_menu(){
    system("cls");
    unsigned int op, id;
    printf("[1]Login\n[0]Finalizar Programa\nSelecione o que desejar: ");
    scanf("%d", &op);
    system("cls");

    switch (op){
    case 1:

        switch (id=login()){

        case 1:
            menu_preceptor();
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
        printf("[+]Cadastrar novo usuario[/]Voltar[?]Acessar usuario\n");

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

void menu_preceptor()
{
    unsigned int op;
    char opcao;


    system("cls");
    printf("--- Preceptor ---\n");
    printf("[1]Atividades\n[2]Avisos\n[3]Lista dos Residentes\n[4]Sair da Conta\nSelecione o que desejar: ");

    scanf("%d", &op);

    switch (op)
    {
    case 1:
        //atividades
        atividades();
        break;

    case 2:
        //avisos
        avisos_preceptor();
        break;

    case 3:
        //residentes
        lista_residentes();
        break;

    case 4:
        //sair
        main_menu();
        break;
    
    default:
        printf("Opção inválida! Tente novamente.\n");
        menu_preceptor();
        break;
    }
}

void atividades()
{
    unsigned int op;

    system("cls");
    printf("--- Atividades ---\n");
    printf("[1]Exame\n13/06/2023  12:30\nResidente: Vitoria Vaporube\n\n"
    "[2]Cirurgia\n13/06/2023  12:30\nResidente: Eduarda Souza\n\n"
    "[3]Estudo de Caso\n13/06/2023  12:30\nResidente: Arthur Figueiredo\n\n"
    "[4]Sair\n\nSelecione o que desejar: ");

    scanf("%d", &op);

    switch (op)
    {
    case 1:
        //exame
        opcoes_atividade();
        break;
    case 2:
        //cirurgia
        opcoes_atividade();
        break;
    case 3:
        //estudo de caso
        opcoes_atividade();
        break;
    case 4:
        //sair
        menu_preceptor();
        break;
    default:
        printf("Opção inválida! Tente novamente.\n");
        atividades();
        break;
    }
}

void opcoes_atividade()
{
    char opcao;

    system("cls");
    printf("\nDescricao:\n(Descricao da Atividade)\n\n[+]Avaliar\n[/]Voltar\nSelecione o que desejar: ");
    scanf("\n%c", &opcao);

    if(opcao == '+'){
        avaliar_residente();
    }
    else if(opcao == '/'){
        atividades();
    }
    else{
        printf("Opcao invalida. Tente novamente.\n");
        atividades();
    }
}

void avaliar_residente()
{
    Usuario residente_selecionado;
    char criterio[9][50] = {"Assiduidade", "Pontualidade", "Iniciativa", "Postura Etico-Profissional", "Relacionamento em equipe",
    "Espirito Critico", "Comunicacao", "Habilidades Especificas", "Participacao nas Atividades"};
    char nota_criterio[9][50];
    char opcao;

    printf("Qual o email do residente que voce deseja avaliar? ");
    scanf(" %[^\n]", residente_selecionado.email);

    system("cls");
    printf("--- Avaliacao Pratica | Exame ---\n");
    printf("%s\nTipo de Avaliacao: Pratica", residente_selecionado.email);

    for (int i = 0; i < 9; i++)
    {
        printf("\n%s: ", criterio[i]);
        scanf("%s", nota_criterio[i]);
        if((int) nota_criterio[i] < 1 || (int) nota_criterio[i] > 5)
        {
            printf("\nNota invalida! Apenas notas entre 1 e 5.");
            avaliar_residente();
        }
    }

    printf("[+]Enviar: ");
    scanf("\n%c", &opcao);
    if(opcao == '+'){
        for (int i = 0; i < 9; i++)
        {
            salvar_nota_residente(residente_selecionado, nota_criterio[i]);
        }
        printf("\nNotas atribuidas com sucesso!");
        opcoes_atividade();
    }
    else
    {
        printf("Opção invalida. Tente novamente.\n");
        avaliar_residente();
    }
    
}

void avisos_preceptor()
{
    unsigned int op;

    system("cls");
    printf("--- Avisos ---");
    printf("\nFeedback Disponivel\n(Aviso 1)\n(Aviso 2)");
    printf("\n[1]Voltar: ");

    scanf("%d", &op);
    if(op == 1)
    {
        menu_preceptor();
    }
    else
    {
        printf("\nOpcao invalida. Tente novamente.");
        avisos_preceptor();
    }
}

void salvar_nota_residente(Usuario residente_selecionado, char* nota)
{
    FILE *fp = fopen("notas_residentes.txt", "r");
    if(fp == NULL) 
    {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    char linhas[100][100];
    int num_linhas = 0;

    char linha[100];
    while(fgets(linha, sizeof(linha), fp) != NULL) 
    {
        if(strstr(linha, residente_selecionado.email) != NULL) 
        {
            linha[strcspn(linha, "\n")] = 0;
            strcat(linha, " ");
            strcat(linha, nota);
        }
        strcpy(linhas[num_linhas++], linha);
    }

    fclose(fp);

    fp = fopen("notas_residentes.txt", "w");
    if(fp == NULL) 
    {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    for(int i = 0; i < num_linhas; i++) 
    {
        fputs(linhas[i], fp);
    }

    fclose(fp);
}

void lista_residentes()
{
    Usuario user, auth;   

    FILE *fp = fopen("cadastrados.txt", "r");

    char linha[69];
    while(fgets(linha, 70, fp) != NULL)
    {
        char* token = strtok(linha, " ");

        auth.idCargo = atoi(token);
        token = strtok(NULL, " ");
        strcpy(auth.email, token);
        token = strtok(NULL, " ");
        strcpy(auth.senha, token);
        token = strtok(NULL, " ");
        auth.idResidencia = atoi(token);
        // fazer checagem se é da mesma residencia que o preceptor logado
        if(auth.idCargo == 2 && auth.idResidencia == 1)
        {
            printf("%s\n", auth.email);
        }
    }
    fclose(fp);
    // fazer com que consiga selecionar o residente
    // fazer a visualização individual do residente
}