#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_cadastro.h"
#include "residente.h"
#include "preceptor.h"
#include "residentes_preceptores.h"
#include "interface.h"

// Coisas do Residente
// feedback_criterios MUDAR TXT para feedback_do_preceptor
// mudar o conteudo da variavel criterio para ficar de acordo com o figma na função fazer_feedback_para_preceptor ?????????????????
// mudar printf na função fazer_feedback_para_preceptor para ficar de acordo com o figma
// mudar nome das variaveis na funcao fazer_feedback_para_preceptor. Atualmente esta vago/confuso o que cada variavel faz e é
// mudar printf dentro do if de checagem 1 < || > 5 para numero, visto que usuario nao digita a avaliacao e sim o numero que deseja
// mudar printf de fazer comentario sobre o preceptor na funcao fazer_feedback_para_preceptor para ficar de acordo com o figma 
// Verificar se peu colocou as #include dos arquivos .h na ordem correta, com suas dependencias verificadas para estar na ordem de quem depende de quem
// trocar nome do arquivo "avaliacao_preceptor.txt" na funcao fazer_feedback_para_preceptor e salvar_feedback_preceptor para "feedback_residentes.txt" para ficar igual aos outros arquivos
// verificar ortografia nos prints | alguns prints estao com "ç" ou acentou ou "~"
// ajustar a formatação da funcao ver_feedback_residente() para que fique no lugar dos numeros, as palavras que estao na funcao converter_feedback_para_texto() | esta localizada no arquivo resisdentes_preceptores.c
// ajustar a formatação na funcao ver_feedback_resisdente() para que fique um em baixo do outro

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
    FILE *fp = fopen("feedback_preceptor.txt", "r");
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
    char criterio[7][100] = {"O preceptor tem um bom relacionamento com os residentes", "O preceptor e assiduo", "O preceptor tem uma boa metodologia te ensino", 
                            "O preceptor apresenta um bom nivel de conhecimento", "O preceptor e pontual", "O preceptor esclarece bem as duvidas",
                            "O preceptor incentiva a participacao do aluno"};
    char avaliacao_criterio[7][100];
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
        int avaliacao;
        scanf("%d", &avaliacao);
        strcpy(avaliacao_criterio[i], converter_numero_feedback_para_texto(avaliacao));
        if(avaliacao < 1 || avaliacao > 5)
        {
            printf("\nFeedback invalido! Apenas feedbacks entre 1 e 5.");
            fazer_feedback_para_preceptor();
        }
    }

    char comentario[100];
    printf("\nDigite um comentario sobre o preceptor: ");
    scanf(" %[^\n]", comentario);

    printf("[+]Enviar: \n[/]Cancelar: ");
    scanf("\n%c", &opcao);
    if(opcao == '+'){
        salvar_feedback_preceptor_nome(preceptor_selecionado);
        for (int i = 0; i < 7; i++)
        {
            salvar_feedback_preceptor(preceptor_selecionado, criterio[i], avaliacao_criterio[i]);
        }
        
        salvar_feedback_preceptor(preceptor_selecionado, "Comentario", comentario);
        
        printf("\nAvaliacoes e comentario atribuidos com sucesso!");
        menu_residente();
    }
    else if(opcao == '/')
    {
        printf("\nFeedback cancelado.\n");
        menu_residente();
    }
    else
    {
        printf("Opcao invalida. Tente novamente.\n");
        fazer_feedback_para_preceptor();
    }
}

void salvar_feedback_preceptor_nome(Usuario preceptor_selecionado)
{
    FILE *fp = fopen("feedback_residente.txt", "a+");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    fputs(preceptor_selecionado.email, fp);
    fputs("\n", fp);
    fclose(fp);
}

void salvar_feedback_preceptor(Usuario preceptor_selecionado, char* criterio, char* avaliacao)
{
    FILE *fp = fopen("feedback_residente.txt", "a+");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    fputs(criterio, fp);
    fputs(":\n", fp);
    fputs(avaliacao, fp);
    fputs("\n", fp);
    fclose(fp);
}

char* converter_numero_feedback_para_texto(int notas) 
{
    switch(notas) 
    {
        case 1: return "Muito Ruim";
        case 2: return "Ruim";
        case 3: return "Moderado";
        case 4: return "Bom";
        case 5: return "Muito Bom";
        default: return "Invalido";
    }
}

void ver_nota_residente() 
{
    FILE *fp = fopen("notas_residentes.txt", "r");
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