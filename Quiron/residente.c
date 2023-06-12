#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_cadastro.h"
#include "residente.h"
#include "preceptor.h"
#include "residentes_preceptores.h"
#include "interface.h"


extern Usuario usuario_logado;

void ver_atividades_residente() 
{
    FILE *fp = fopen("atividades.txt", "r");
    if (fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo de atividades.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), fp) != NULL) 
    {
        printf("%s", linha);
    }

    fclose(fp);
}

void ver_feedback_residente() 
{
    FILE *fp = fopen("feedbacks_residentes.txt", "r");
    if (fp == NULL) {
        printf("Nao foi possivel abrir o arquivo de feedbacks.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s", linha);
    }

    fclose(fp);
}

void fazer_feedback_para_preceptor()
{
    Usuario preceptor_selecionado;
    char criterio[7][50] = {"Relacionamento com os residentes", "Assiduidade", "Metodologia de ensino", 
                            "Nivel de conhecimento", "Pontualidade", "Esclarecimento de duvidas",
                            "Incentiva a participacao do aluno"};
    char avaliacao_criterio[7][50];
    char opcao;

    printf("Qual o email do preceptor que voce deseja avaliar? ");
    scanf(" %[^\n]", preceptor_selecionado.email);

    system("cls");
    printf("--- Avaliacao de Feedback ---\n");
    printf("%s\n", preceptor_selecionado.email);

    for (int i = 0; i < 7; i++)
    {
        printf("\n%s: ", criterio[i]);
        printf("\n[1] Muito Ruim\n[2] Ruim\n[3] Moderado\n[4] Bom\n[5] Muito Bom\nSelecione a avaliacao: ");
        scanf("%s", avaliacao_criterio[i]);
        int avaliacao = atoi(avaliacao_criterio[i]);
        if(avaliacao < 1 || avaliacao > 5)
        {
            printf("\nAvaliacao invalida! Apenas avaliacoes entre 1 e 5.");
            fazer_feedback_para_preceptor();
        }
    }

    char comentario[100];
    printf("\nDigite um comentario sobre o preceptor: ");
    scanf(" %[^\n]", comentario);

    printf("[+]Enviar: ");
    scanf("\n%c", &opcao);
    if(opcao == '+'){
        for (int i = 0; i < 7; i++)
        {
            salvar_feedback_preceptor(preceptor_selecionado, avaliacao_criterio[i]);
        }
        // Salve o comentário como uma avaliação
        salvar_feedback_preceptor(preceptor_selecionado, comentario);
        
        printf("\nAvaliacoes e comentario atribuidos com sucesso!");
        menu_residente();
    }
    else
    {
        printf("Opcao invalida. Tente novamente.\n");
        fazer_feedback_para_preceptor();
    }
}


void salvar_feedback_preceptor(Usuario preceptor_selecionado, char* avaliacao)
{
    FILE *fp = fopen("avaliacao_preceptor.txt", "a+");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    fclose(fp);

    fp = fopen("avaliacao_preceptor.txt", "r");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    char linhas[100][100];
    int num_linhas = 0;
    int preceptor_found = 0;

    char linha[100];
    while(fgets(linha, sizeof(linha), fp) != NULL) 
    {
        linha[strcspn(linha, "\n")] = 0;  // remover a nova linha do final
        if(strlen(linha) == 0) 
        {
            continue;  // ignorar linhas vazias
        }

        if(strstr(linha, preceptor_selecionado.email) != NULL) 
        {
            strcat(linha, " ");
            strcat(linha, avaliacao);
            preceptor_found = 1;
        }
        strcpy(linhas[num_linhas++], linha);
    }

    if(!preceptor_found)  // se o preceptor não foi encontrado, adicione uma nova linha para ele
    {
        strcpy(linha, preceptor_selecionado.email);
        strcat(linha, " ");
        strcat(linha, avaliacao);
        strcpy(linhas[num_linhas++], linha);
    }

    fclose(fp);

    fp = fopen("avaliacao_preceptor.txt", "w");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    for(int i = 0; i < num_linhas; i++) 
    {
        fputs(linhas[i], fp);
        fputs("\n", fp);
    }

    fclose(fp);
}