// #include "residentes_preceptores.h"
#include "login_cadastro.h"
#include "residentes_preceptores.h"
#include "residente.h"
#include "preceptor.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define FILE_NAME "cadastrados.txt"

// Função para exibir lista de preceptores e residentes cadastrados
void printar_residentes_preceptores(int residencia, int cargo)
{

    FILE *fp = fopen(FILE_NAME, "r");
    Usuario usuario;

    if (fp == NULL) // Nao achou nenhum residente ou preceptor para a residencia selecionada
    {
        printf("Nenhum usuario cadastrado para essa residencia!\n");
    }
    else // Achou!
    {
        char linha[69];
        while(fgets(linha, 70, fp) != NULL) // While verifica se o usuario digitado existe no arquivo e printa suas informações
        {
            char* token = strtok(linha, " ");

            usuario.idCargo = atoi(token);
            token = strtok(NULL, " ");
            strcpy(usuario.email, token);
            token = strtok(NULL, " ");
            strcpy(usuario.senha, token);
            usuario.senha[strlen(usuario.senha)-1] = '\0';
            token = strtok(NULL, " ");
            usuario.idResidencia = atoi(token);

            if(usuario.idCargo == cargo && usuario.idResidencia == residencia)
            {
                printf("%s\n", usuario.email);
            }      
        }

        fclose(fp);

    }

    
}
// Função para converter os dados numerais do feedback em textos representante ao avaliar
char* converter_feedback_para_texto(int notas) 
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
// Função para definir se email digitado é de um residente ou preceptor
int preceptor_ou_residente(Usuario user)
{
    Usuario usuario;

    FILE *fp = fopen("cadastrados.txt", "r");
    char linha[69];
    char email[50];

    while (fgets(linha, sizeof(linha), fp))
    {
        char* token = strtok(linha, " ");

        usuario.idCargo = atoi(token);
        token = strtok(NULL, " ");
        strcpy(usuario.email, token);
        token = strtok(NULL, " ");
        strcpy(usuario.senha, token);
        token = strtok(NULL, " ");
        usuario.idResidencia = atoi(token);

        if(strcmp(user.email, usuario.email) == 0)
        {
            fclose(fp);
            if(usuario.idCargo == 1)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }

        
    }
    fclose(fp);
    return 0;  // não encontrado
}
// Função para ver o feedback dos residentes a determinado preceptor
void ver_feedback_preceptor_coord()
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
}
