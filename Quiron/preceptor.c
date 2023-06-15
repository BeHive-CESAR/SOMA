#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_cadastro.h"
#include "preceptor.h"
#include "residente.h"
#include "residentes_preceptores.h"
#include "interface.h"


extern Usuario usuario_logado;

#define MAX 70 // Maximo de caracteres da linha do arquivo
#define MAX_CRITERIOS 6 // Maximo de criterios a seram avaliados

// Função para ler arquivo e imprimir as atividades que o preceptor realizou
void ver_atividades_preceptor()
{
    
    printf("--- Atividades ---\n");

    FILE *fp = fopen("atividades.txt", "r"); 

    if (fp == NULL) 
    {
        system("cls");
        printf("Nao foi possivel abrir o arquivo.\n"); // Caso não consiga abrir o arquivo, volta pra o menu do preceptor
        menu_preceptor();
        return;
    }

    char linha[MAX];
    while (fgets(linha, MAX, fp) != NULL) // While para pular a primeira palavra (email do preceptor) e pegar o restante da atividade
    {
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

    char opcao; // Variavel da selação da proxima opção

    printf("\n[+]Avaliar residente [/]Voltar\nSelecione o que desejar: ");
    scanf("\n%c", &opcao);

    if (opcao == '+')
    {
        system("cls");
        avaliar_residente(); // Avaliar o residente na atividade criada previamente
    }
    else
    {
        system("cls");
        menu_preceptor(); // Volta pra o menu preceptor
    }

}
// Função para adiconar atividades no cronograma dos residentes
void criar_atividade()
{
    
    printf("--- Criar Atividade ---\n");
    FILE *fp = fopen("atividades.txt", "a"); // Abre o arquivo das atividades

    if(fp == NULL) 
    {
        system("cls");
        printf("Nao foi possivel abrir o arquivo.\n"); // Houve algum erro e não conseguiu abrir o arquivo
        return;
    }

    char nome_atividade[MAX], data_atividade[MAX], residente_atividade[MAX], descricao_atividade[MAX], pontuacao_atividade[MAX];
    char preceptor_responsavel[MAX];
    strcpy(preceptor_responsavel, usuario_logado.email);


    printf("Favor, substituir 'espaco' por ''\n");

    //Preceptor responsavel
    fprintf(fp, "%s", usuario_logado.email);

    // Nome da atividade
    printf("Nome da atividade: ");
    scanf(" %[^\n]", nome_atividade);
    fprintf(fp, " %s", nome_atividade);

    // Data de entrega
    printf("Data de entrega: ");
    scanf(" %[^\n]", data_atividade);
    fprintf(fp, " %s", data_atividade);

    // Definição dos residentes que irão receber as atividades
    printf("Residentes: ");
    scanf(" %[^\n]", residente_atividade);
    fprintf(fp, " %s", residente_atividade);

    // Breve descrição da atividade
    printf("Descricao: ");
    scanf(" %[^\n]", descricao_atividade);
    fprintf(fp, " %s", descricao_atividade);

    // Pontuação maxima da atividade
    printf("Pontuacao: ");
    scanf("%s", pontuacao_atividade);
    fprintf(fp, " %s\n", pontuacao_atividade);


    fclose(fp); // Fecha o arquivo

    system("cls");
    menu_preceptor(); // Volta para o menu do preceptor
}
// Função para realizar a avaliação das competencias dos residentes
void avaliar_residente()
{
    // Criação das variaveis
    Usuario residente_selecionado;
    char criterio[9][50] = {"Assiduidade", "Pontualidade", "Iniciativa", "Postura Etico-Profissional", "Relacionamento em equipe",
    "Espirito Critico", "Comunicacao", "Habilidades Especificas", "Participacao nas Atividades"};
    char nota_criterio[9][50];
    char opcao;
    float media_residente = 0;

    printf("Qual o email do residente que voce deseja avaliar? "); // Digita o email do residente que deseja avaliar
    scanf(" %[^\n]", residente_selecionado.email); 
    
    if(residente_existe(residente_selecionado) == 0) // Se não encontrar o residente volta para o menu de avaliar residente
    {
        system("cls");
        printf("\nResidente nao encontrado! Tente novamente.\n");
        avaliar_residente();
    }

    printf("--- Avaliacao Pratica | Exame ---\n");
    printf("%s\nTipo de Avaliacao: Pratica", residente_selecionado.email); // Achou o residente | Printa o email do residente que foi selecionado

    for (int i = 0; i < 9; i++) // For para printar cada criterio individualmente e espera o input do preceptor com a nota referente ao criterio
    {
        printf("\n%s: ", criterio[i]);
        scanf(" %s", nota_criterio[i]);
        int verificar = nota_criterio[i][0] - '0';
        if(verificar < 1 || strlen(nota_criterio[i]) > 1 || verificar > 5) // Verifica se a nota dada foi entre 1 e 5
        {
            system("cls");
            printf("\nNota invalida! Apenas notas entre 1 e 5.\n"); // Caso nao for, apresenta o nota invalida e volta para o menu de avaliar o residente
            avaliar_residente();
        }
    }

    printf("[+]Enviar: \n[/]Cancelar: "); // Confirmar ou Cancelar o envio do formulario de avaliação
    scanf("\n%c", &opcao);
    if(opcao == '+')
    {
        for (int i = 0; i < 9; i++)
        {
            media_residente += (nota_criterio[i][0] - '0') * 2; // Multiplica todas as notas por 2 para ao inves de ser 5, ser 10 o maximo
        }
        media_residente /= 9; // Dividimos por 9, ou seja por todos os criterios

        char media_char[10];

        sprintf(media_char, "%.2f\n", media_residente);
        salvar_nota_residente(residente_selecionado, media_char); // Chama a função para salvar as notas no arquivo

        system("cls");
        printf("\nNotas atribuidas com sucesso!\n");

        ver_atividades_preceptor(); // Volta pra o menu de atividades do preceptor
    }
    else
    {
        system("cls");
        avaliar_residente(); // Ao cancelar o envio volta para o menu de avaliar residente
    }
}
// Função para criar avisos para serem enviados aos residentes
void avisos_preceptor()
{
    unsigned int op;

    printf("--- Avisos ---");
    printf("\nFeedback Disponivel");
    printf("\n[1]Realizar Feedback");
    printf("\n[2]Voltar\nEscolha: ");

    scanf("%d", &op);
    if(op == 1) // realiza o feedback
    {
        system("cls");
        fazer_feedback_para_residente(); // Volta para o menu de fazer o feedback
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
// Função para escrever a nota do residente em uma arquivo
void salvar_nota_residente(Usuario residente_selecionado, char* nota) 
{
    FILE *fp = fopen("notas_residentes.txt", "a"); // abre o arquivo em modo anexação
    if(fp == NULL) 
    {
        system("cls");
        printf("Nao foi possivel abrir o arquivo.\n"); // Nao achou o arquivo
        return;
    }

    // Escreve no arquivo as notas com o email do residente, o email do preceptor que fez a avaliação e as notas
    fprintf(fp, "%s %s %s", residente_selecionado.email, usuario_logado.email, nota); 

    fclose(fp);

    system("cls");
    printf("Notas atribuídas com sucesso\n");
    

}
// Função para imprimir lista de residente
void lista_residentes()
{
    Usuario user, auth, residente_selecionado;   

    FILE *fp = fopen("cadastrados.txt", "r");

    char linha[69];
    while(fgets(linha, 70, fp) != NULL) // While para filtrar os residentes de acordo com a residencia do preceptor que está logado
    {
        char* token = strtok(linha, " ");

        auth.idCargo = atoi(token);
        token = strtok(NULL, " ");
        strcpy(auth.email, token);
        token = strtok(NULL, " ");
        strcpy(auth.senha, token);
        token = strtok(NULL, " ");
        auth.idResidencia = atoi(token);

        if(auth.idCargo == 2 && auth.idResidencia == usuario_logado.idResidencia) // Se o id do residente for igual ao do preceptor, será printado na lista
        {
            printf("%s\n", auth.email);
        }
    }

    printf("Selecione o residente que deseja visualizar: ");
    scanf(" %[^\n]", residente_selecionado.email); // Seleciona um dos residente da lista para visualizar

    if(residente_existe(residente_selecionado) == 0) // Nao encontrou o residente
    {
        system("cls");
        printf("\nResidente nao encontrado! Tente novamente.\n");
        strcpy(residente_selecionado.email, NULL);
        fclose(fp);
        lista_residentes();
    }
    // Encontrou o residente
    fclose(fp);
    system("cls");
    perfil_residente(residente_selecionado, auth); // Mostra o perfil do residente que foi selecionado
    printf("\n[/]Para voltar ");
    char voltar;
    scanf("\n%c", &voltar);
    menu_preceptor();
    
}
// Função para separar as opções de residente
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
    printar_grafico(); // Print do grafico demonstrativo do residente selecionado
    printf("\nAvalicoes Individuais");
    printar_notas_residente(residente_selecionado); // Printa as notas que estão no arquivo do residente selecionado
}
// Função para mostrar no terminal as competencias em forma de grafico (Grafico Demonstrativo)
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

    // Desenha uma linha inferior após o gráfico
    printf("    ");
    for(int i = 0; i < 52; i++) 
    {
        printf("-");
    }
    printf("\n");
}
// Função para exibir media do residente 
void printar_notas_residente(Usuario residente_selecionado)
{
    FILE *fp = fopen("notas_residentes.txt", "r"); // Abre o arquivo para leitura

    char linha[69];
    char nome_preceptor[69];
    char nome_residente[69];
    float nota_residente;

    // While para pegar apenas as notas do residente que foi selecionado
    while(fgets(linha, 70, fp) != NULL)
    {
        
        char* token = strtok(linha, " ");

        strcpy(nome_residente, token);
        token = strtok(NULL, " ");
        strcpy(nome_preceptor, token);
        token = strtok(NULL, " ");
        nota_residente = atof(token);
        
        if(strcmp(nome_residente, residente_selecionado.email) == 0) // Compara o email que existe no arquivo com o email que foi digitado
        {
            printf("\nPreceptor: %s.... Media: %0.2f", nome_preceptor, nota_residente);
        }
  
    }
    fclose(fp);
}
// Função para conferir se o usuario está dentro do arquivo cadastrados.txt
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
// Função para enviar feedback para determinado residente
void fazer_feedback_para_residente()
{
    // Criação das variaveis
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

    printf("Qual o email do residente que voce deseja avaliar? "); // Seleciona o residente a ser avaliado
    scanf(" %[^\n]", residente_selecionado.email);

    system("cls");
    printf("---Feedback para Residente---\n");
    printf("%s\n", residente_selecionado.email); // Email do residente que foi selecionado

    // For que printa os criterios 1 a 1 para receber o input com a nota para aquele criterio
    for (int i = 0; i < MAX_CRITERIOS; i++)
    {
        printf("\n%s: ", criterios[i]);
        printf("\n[1] Muito Ruim\n[2] Ruim\n[3] Moderado\n[4] Bom\n[5] Muito Bom\nSelecione a avaliacao: ");
        scanf("%s", nota_feedback[i]);
        int int_nota_criterio = atoi(nota_feedback[i]); // Transforma o char em int para verificação
        if(int_nota_criterio < 1 || int_nota_criterio > 5) // Verifica se está entre 1 e 5
        {
            printf("\nNota invalida! Apenas notas entre 1 e 5.");
            fazer_feedback_para_residente(); // Caso não, volta para o inicio
        }
    }

    char comentario[100];
    printf("\nDigite um comentario sobre o residente: "); // Comentario / Observação a fazer do residente para aquela atividade
    scanf(" %[^\n]", comentario);

    printf("[+]Enviar: ");
    scanf("\n%c", &opcao);
    if(opcao == '+')
    {
        for (int i = 0; i < MAX_CRITERIOS; i++)
        {
            salvar_feedback_residente(residente_selecionado, nota_feedback[i]); // Salva todas as notas dos criterios
        }
        // Salva o comentario
        salvar_feedback_residente(residente_selecionado, comentario);
        // Salva o nome do preceptor que esta logado e realizou o feedback
        salvar_feedback_residente(residente_selecionado, usuario_logado.email);

        
        printf("\nFeedback e observacao atribuidos com sucesso!"); // Tudo certo! Voltamos para o menu do preceptor
        menu_preceptor();
    }
    else
    {
        printf("Opcao invalida. Tente novamente.\n"); // Algo deu errado, voltamos para o inicio
        fazer_feedback_para_residente();
    }
}
// Função para escrever feedback em um arquivo
void salvar_feedback_residente(Usuario residente_selecionado, char* nota)
{
    FILE *fp = fopen("feedback_preceptor.txt", "a+"); // Abre o arquivo para anexação, se não houver cria o arquivo
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
        
    }
    fclose(fp); // Fecha o arquivo

    fp = fopen("feedback_preceptor.txt", "r"); // Abre o arquivo para leitura
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    // Criação das variaveis
    char linhas[100][100];
    int num_linhas = 0;
    int achou_residente = 0;

    char linha[100];
    while(fgets(linha, sizeof(linha), fp) != NULL) // Procura se o residente ja existe no arquivo
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

    if(!achou_residente)  // Nao encontrou o residente, adiciona uma nova linha para ele
    {
        strcpy(linha, residente_selecionado.email);
        strcat(linha, " ");
        strcat(linha, nota);
        strcpy(linhas[num_linhas++], linha);
    }

    fclose(fp); // Fecha o arquivo

    fp = fopen("feedback_preceptor.txt", "w"); // Abre o arquivo para escrita
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    for(int i = 0; i < num_linhas; i++) // Escreve o feedback no arquivo
    {
        fputs(linhas[i], fp);
        fputs("\n", fp);
    }

    fclose(fp);
}
// Função para ver feedbaks escritos por residentes
void ver_feedback_preceptor()
{
    system("cls");
    char opcao;
    char linha[69];
    FILE *fp = fopen("feedback_residente.txt", "r"); // Abre o arquivo para leitura

    if (fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo de feedbacks.\n");
        return;
    }

    printf("Anonimo\n"); // Todos os feedbacks dos residentes para preceptores são vistos como anonimos

    while (fgets(linha, 70, fp) != NULL) 
    {
        printf("%s", linha);
    }

    fclose(fp);

    printf("\nDeseja voltar?\n[/] Voltar: "); // Opcao para voltar para o menu do preceptor
    scanf(" %c", &opcao);

    menu_preceptor();
}

 