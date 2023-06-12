#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_cadastro.h"
#include "preceptor.h"
#include "residente.h"
#include "residentes_preceptores.h"
#include "interface.h"

// Coisas do Preceptor
// fazer pagina de feedback dos residentes para o preceptor -> em processo (peu)
// checar se caso digite um numero maior que 5 e menor que 1, na proximo vez digitar o numero certo e ter certeza que o numero correto ira para o txt na funcao fazer_feedback_para_residente
// Falta apenas a função de fazer a visualização do feedback que os residentes fizeram do preceptor
// Na funcao fazer_feedback_para_residente apos confirmar o envio do feedback o programa encerra. why?
// Adicionar o nome do preceptor que esta fazendo o feedback ao residente no arquivo de feedback_preceptor
// funcao fazer_feedback_para_residente nao esta funcionando corretamente. 
    // 1. o comentario que é adicionado primeiro fica se repetindo em todos os outros feedbacks
    // 2. Esta apagando qualquer residente que ja estivesse presente no arquivo
// função de perfil de residente encerra o programa após mostrar o perfil do residente | deveria voltar para a funcao de lista_residentes
// atualmente a funcao de fazer_feedback_para_residente() esta gravando o nome que foi 


extern Usuario usuario_logado;

#define MAX 70
#define MAX_CRITERIOS 6

void ver_atividades_preceptor()
{
    
    printf("--- Atividades ---\n");

    FILE *fp = fopen("atividades.txt", "r"); 

    if (fp == NULL) {
        system("cls");
        printf("Nao foi possivel abrir o arquivo.\n");
        menu_preceptor();
        return;
    }

    char linha[MAX];
    while (fgets(linha, MAX, fp) != NULL) {
        char* primeiraPalavra = strtok(linha, " ");
        if (strcmp(primeiraPalavra, usuario_logado.email) == 0) {
            char* palavra = strtok(NULL, " "); 
            while (palavra != NULL) {
                printf("\n%s", palavra);
                palavra = strtok(NULL, " "); 
            }

        }
    }

    fclose(fp);

    char opcao;

    printf("\n[+]Avaliar residente [/]Voltar\nSelecione o que desejar: ");
    scanf("%c", &opcao);

    if (opcao == '+')
    {
        system("cls");
        avaliar_residente();
    }
    else
    {
        system("cls");
        menu_preceptor();
    }

}

void criar_atividade()
{
    
    printf("--- Criar Atividade ---\n");
    FILE *fp = fopen("atividades.txt", "a"); 

    if(fp == NULL) 
    {
        system("cls");
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    char nome_atividade[MAX], data_atividade[MAX], residente_atividade[MAX], descricao_atividade[MAX], pontuacao_atividade[MAX];
    char preceptor_responsavel[MAX];
    strcpy(preceptor_responsavel, usuario_logado.email);


    printf("Favor, substituir 'espaco' por ''\n");

    //Preceptor responsavel
    fprintf(fp, "%s", usuario_logado.email);

    printf("Nome da atividade: ");
    scanf(" %[^\n]", nome_atividade);
    fprintf(fp, " %s", nome_atividade);

    printf("Data de entrega: ");
    scanf(" %[^\n]", data_atividade);
    fprintf(fp, " %s", data_atividade);

    printf("Residentes: ");
    scanf(" %[^\n]", residente_atividade);
    fprintf(fp, " %s", residente_atividade);

    printf("Descricao: ");
    scanf(" %[^\n]", descricao_atividade);
    fprintf(fp, " %s", descricao_atividade);

    printf("Pontuacao: ");
    scanf("%s", pontuacao_atividade);
    fprintf(fp, " %s\n", pontuacao_atividade);


    fclose(fp);

    system("cls");
    menu_preceptor();
}



void avaliar_residente()
{

    Usuario residente_selecionado;
    char criterio[9][50] = {"Assiduidade", "Pontualidade", "Iniciativa", "Postura Etico-Profissional", "Relacionamento em equipe",
    "Espirito Critico", "Comunicacao", "Habilidades Especificas", "Participacao nas Atividades"};
    char nota_criterio[9][50];
    char opcao;
    float media_residente = 0;

    printf("Qual o email do residente que voce deseja avaliar? ");
    scanf(" %[^\n]", residente_selecionado.email);
    
    if(residente_existe(residente_selecionado) == 0) 
    {
        system("cls");
        printf("\nResidente nao encontrado! Tente novamente.\n");
        avaliar_residente();
    }

    printf("--- Avaliacao Pratica | Exame ---\n");
    printf("%s\nTipo de Avaliacao: Pratica", residente_selecionado.email);

    for (int i = 0; i < 9; i++)
    {
        printf("\n%s: ", criterio[i]);
        scanf(" %s", nota_criterio[i]);
        int verificar = nota_criterio[i][0] - '0';
        if(verificar < 1 || strlen(nota_criterio[i]) > 1 || verificar > 5)
        {
            system("cls");
            printf("\nNota invalida! Apenas notas entre 1 e 5.\n");
            avaliar_residente();
        }
    }

    printf("[+]Enviar: \n[/]Cancelar: ");
    scanf("\n%c", &opcao);
    if(opcao == '+')
    {
        for (int i = 0; i < 9; i++)
        {
            media_residente += (nota_criterio[i][0] - '0') * 2;
        }
        media_residente /= 9;

        char media_char[10];

        sprintf(media_char, "%.2f", media_residente);
        salvar_nota_residente(residente_selecionado, media_char);

        system("cls");
        printf("\nNotas atribuidas com sucesso!");

        ver_atividades_preceptor();
    }
    else
    {
        system("cls");
        avaliar_residente();
    }
}

void avisos_preceptor()
{
    unsigned int op;

    printf("--- Avisos ---");
    printf("\nFeedback Disponivel");
    printf("\n[1]Realizar Feedback: ");
    printf("\n[2]Voltar: ");

    scanf("%d", &op);
    if(op == 1) // realiza o feedback
    {
        system("cls");
        fazer_feedback_para_residente();
    }
    else if(op == 2) // volta para a tela anterior
    {
        system("cls");
        menu_preceptor();
    }
    else // opcao invalida
    {
        system("cls");
        printf("\nOpcao invalida. Tente novamente.");
        avisos_preceptor();
    }
}

void salvar_nota_residente(Usuario residente_selecionado, char* nota) 
{
    FILE *fp = fopen("notas_residentes.txt", "a"); // abre o arquivo em modo anexação
    if(fp == NULL) 
    {
        system("cls");
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }


    fprintf(fp, "%s %s %s\n", residente_selecionado.email, usuario_logado.email, nota);

    fclose(fp);

    system("cls");
    printf("Notas atribuídas com sucesso\n");
    

}

void lista_residentes()
{
    Usuario user, auth, residente_selecionado;   

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

        if(auth.idCargo == 2 && auth.idResidencia == usuario_logado.idResidencia)
        {
            printf("%s\n", auth.email);
        }
    }

    printf("Selecione o residente que deseja visualizar: ");
    scanf(" %[^\n]", residente_selecionado.email);

    if(residente_existe(residente_selecionado) == 0) 
    {
        system("cls");
        printf("\nResidente nao encontrado! Tente novamente.\n");
        strcpy(residente_selecionado.email, NULL);
        fclose(fp);
        lista_residentes();
    }
    fclose(fp);
    system("cls");
    perfil_residente(residente_selecionado, auth);
    
}

void perfil_residente(Usuario residente_selecionado, Usuario auth)
{
    printf("--- Avaliacao Geral ---");
    printf("\n%s", residente_selecionado.email);

    switch (auth.idResidencia)
    {
    case 0:
        // Anestesia
        printf("\nAnestesia | Residente");
        break;
    case 1:
        // Cardiologia
        printf("\nCardiologia | Residente");
        break;
    case 2:
        // Cirurgia geral
        printf("\nCirurgia geral | Residente");
        break;
    case 3:
        // Clinica Geral
        printf("\nClinica Geral | Residente");
        break;
    
    default:
        system("cls");
        printf("\nResidente invalido. Tente novamente");
        lista_residentes();
        break;
    }

    printf("\n\n--- Grafico de Notas ---\n\n");
    printar_grafico();
    printf("\nAvalicoes Individuais");
    printar_notas_residente(residente_selecionado);
}

void printar_grafico() 
{

    int max = 0;
    int valores[9] = {5, 3, 5, 5, 2, 3, 4, 3, 5}; // Valores pre definidos por nos | Puramente estetico
    int tamanho = 9;

    for(int i = 0; i < tamanho; i++) 
    {
        if(valores[i] > max) 
        {
            max = valores[i];
        }
    }
    // Desenha o gráfico
    for(int i = 0; i < tamanho; i++) 
    {
        printf("%2d | ", i + 1);
        int barra = (valores[i] * 50) / max;  
        for(int j = 0; j < barra; j++) 
        {
            printf("#");
        }
        printf(" %d\n", valores[i]);
    }

    // Desenha a linha inferior
    printf("    ");
    for(int i = 0; i < 52; i++) 
    {
        printf("-");
    }
    printf("\n");
}

void printar_notas_residente(Usuario residente_selecionado)
{
    FILE *fp = fopen("notas_residentes.txt", "r");

    char linha[69];
    char nome_preceptor[69];
    char nome_residente[69];
    float nota_residente;

    while(fgets(linha, 70, fp) != NULL)
    {
        
        char* token = strtok(linha, " ");

        strcpy(nome_residente, token);
        token = strtok(NULL, " ");
        strcpy(nome_preceptor, token);
        token = strtok(NULL, " ");
        nota_residente = atof(token);
        
        if(strcmp(nome_residente, residente_selecionado.email) == 0)
        {
            printf("\nPreceptor: %s.... Media: %0.2f", nome_preceptor, nota_residente);
        }
  
    }
    fclose(fp);
}

int residente_existe(Usuario residente_selecionado) 
{
    FILE *fp = fopen("cadastrados.txt", "r");
    char linha[69];
    char email[50];

    while (fgets(linha, sizeof(linha), fp)) 
    {
        sscanf(linha, "%*d %s", email);  // ignora o primeiro campo e lê o segundo (email)
        if (strcmp(email, residente_selecionado.email) == 0) 
        {
            fclose(fp);
            return 1;  // encontrado
        }
    }

    fclose(fp);
    return 0;  // não encontrado
}

void fazer_feedback_para_residente()
{
    Usuario residente_selecionado;
    char criterios[MAX_CRITERIOS][80] = {
                            "O residente apresenta uma boa relacao com outros residentes e preceptores",
                            "O residente eh assiduo", 
                            "O residente se mostra interessado no assunto passado", 
                            "O residente apresenta um bom conhecimento no assunto", 
                            "O residente eh pontual",
                            "O residente eh engajado e participativo",
                            };
    char nota_feedback[MAX_CRITERIOS][50];
    char opcao;

    printf("Qual o email do residente que voce deseja avaliar? ");
    scanf(" %[^\n]", residente_selecionado.email);

    system("cls");
    printf("---Feedback para Residente---\n");
    printf("%s\n", residente_selecionado.email);

    for (int i = 0; i < MAX_CRITERIOS; i++)
    {
        printf("\n%s: ", criterios[i]);
        printf("\n[1] Muito Ruim\n[2] Ruim\n[3] Moderado\n[4] Bom\n[5] Muito Bom\nSelecione a avaliacao: ");
        scanf("%s", nota_feedback[i]);
        int int_nota_criterio = atoi(nota_feedback[i]);
        if(int_nota_criterio < 1 || int_nota_criterio > 5)
        {
            printf("\nNota invalida! Apenas notas entre 1 e 5.");
            fazer_feedback_para_residente();
        }
    }

    char comentario[100];
    printf("\nDigite um comentario sobre o residente: ");
    scanf(" %[^\n]", comentario);

    printf("[+]Enviar: ");
    scanf("\n%c", &opcao);
    if(opcao == '+')
    {
        for (int i = 0; i < MAX_CRITERIOS; i++)
        {
            salvar_feedback_residente(residente_selecionado, nota_feedback[i]);
        }
        // Salva o comentÃ¡rio como um comentario
        salvar_feedback_residente(residente_selecionado, comentario);
        // Salva o nome do preceptor que esta logado e realizou o feedback
        salvar_feedback_residente(residente_selecionado, usuario_logado.email);

        
        printf("\nFeedback e observacao atribuidos com sucesso!");
        menu_preceptor();
    }
    else
    {
        printf("Opcao invalida. Tente novamente.\n");
        fazer_feedback_para_residente();
    }
}


void salvar_feedback_residente(Usuario residente_selecionado, char* nota)
{
    FILE *fp = fopen("feedback_preceptor.txt", "a+");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
        
    }
    fclose(fp);

    fp = fopen("feedback_preceptor.txt", "r");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    char linhas[100][100];
    int num_linhas = 0;
    int achou_residente = 0;

    char linha[100];
    while(fgets(linha, sizeof(linha), fp) != NULL) 
    {
        linha[strcspn(linha, "\n")] = 0;  // remove a nova linha do final
        if(strlen(linha) == 0) 
        {
            continue;  // ignora as linhas vazias
        }

        if(strstr(linha, residente_selecionado.email) != NULL) 
        {
            strcat(linha, " ");
            strcat(linha, nota);
            achou_residente = 1;
        }
        strcpy(linhas[num_linhas++], linha);
    }

    if(!achou_residente)  // nao encontrou o residente, adiciona uma nova linha para ele
    {
        strcpy(linha, residente_selecionado.email);
        strcat(linha, " ");
        strcat(linha, nota);
        strcpy(linhas[num_linhas++], linha);
    }

    fclose(fp);

    fp = fopen("feedback_preceptor.txt", "w");
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

void ver_feedback_preceptor()
{
    system("cls");
    char opcao;
    char linha[69];
    FILE *fp = fopen("feedback_residente.txt", "r");

    if (fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo de feedbacks.\n");
        return;
    }

    printf("Anonimo\n");

    while (fgets(linha, 70, fp) != NULL) 
    {
        printf("%s", linha);
    }

    fclose(fp);

    printf("\nDeseja voltar?\n[/] Voltar: ");
    scanf(" %c", &opcao);

    menu_preceptor();
}

 