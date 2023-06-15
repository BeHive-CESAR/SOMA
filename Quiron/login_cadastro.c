#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login_cadastro.h"
#include "interface.h"


#define FILE_NAME "cadastrados.txt" // Definição do nome do arquivo para facil alteração, caso seja necessario

Usuario usuario_logado;

// Função para realizar o cadastro de novos usuarios no sistema, adicionando informação em um arquivo
int cadastrar(int residencia)
{

    Usuario user; // Criação do Struct "user" para uso na função
    system("cls");
    printf("REALIZAR CADASTRO\n");
    printf("Seleciona um dos cargos abaixo para cadastrar\n[1]Preceptor [2]Residente [3]Cancelar:  ");
    scanf("%d", &user.idCargo);

    if (user.idCargo == 3) // Cargo da coordenação
    {
        system("cls");
        return 1;
    }

    printf("Email: ");
    scanf(" %[^\n]", user.email); // Email do usuario cadastrado

    printf("Senha: ");
    scanf(" %[^\n]", user.senha); // Senha do usuario cadastrado

    FILE *fp = fopen(FILE_NAME, "a+"); // Salvando no arquivo as informações do usuario cadastrado
    system("cls");
    fprintf(fp, "%d %s %s %d\n", user.idCargo, user.email, user.senha, residencia);
    fclose(fp);
 
    return 0;

}
// Função para definir o tipo de interface que cada usuario vai utilizar
int login()
{
    system("cls");
    Usuario user, auth; // Criação de dois Structs do mesmo tipo "Usuario". "user" quem está tentando logar | "auth" verificação se o usuario ja foi cadastrado

    FILE *fp = fopen(FILE_NAME, "r"); // Abre arquivo para leitura


    printf("Insira seu E-mail cadastrado: ");
    scanf(" %[^\n]", user.email);

    printf("Insira sua senha: ");
    scanf(" %[^\n]", user.senha);

    if (strcmp(user.email, "admin") == 0 && strcmp(user.senha, "admin") == 0) // Caso seja login da coordenação direciona para o menu da coordenação
    {
        return 3;
    }

    if (fp == NULL) // Se o usuario nao existir no arquivo | Ou seja, nao foi cadastrado
    {
        printf("Nenhum usuario foi cadastrado! :o\n");
        return 4;
    }

    // While que verifica linha a linha todos os usuarios cadastrados no arquivo
    char linha[69];
    while(fgets(linha, 70, fp) != NULL){
        char* token = strtok(linha, " ");

        auth.idCargo = atoi(token);
        token = strtok(NULL, " ");
        strcpy(auth.email, token);
        token = strtok(NULL, " ");
        strcpy(auth.senha, token);
        token = strtok(NULL, " ");
        auth.idResidencia = atoi(token);

        if(strcmp(auth.email, user.email) == 0 && strcmp(auth.senha, user.senha) == 0) // Verificação para ver se o email e a senha que foram digitados, se existe dentro do arquivo de cadastros
        {
            def_usuario_logado(auth);
            fclose(fp);
            return auth.idCargo;
        }
        
    }
    fclose(fp);

    return 4;
}
// Função que separa o tipo de usuario que está usando o sistema
void def_usuario_logado(Usuario auth)
{
    strcpy(usuario_logado.email, auth.email);
    usuario_logado.idResidencia = auth.idResidencia;
}