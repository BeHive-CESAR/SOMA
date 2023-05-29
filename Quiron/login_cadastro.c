#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login_cadastro.h"
#include "interface.h"


#define FILE_NAME "cadastrados.txt"


int cadastrar(){

    Usuario user;
    printf("REALIZAR CADASTROS\n");
    printf("Cargo\n[1]Preceptor [2]Residente [3]Cancelar:  ");
    scanf("%d", &user.idCargo);
    if (user.idCargo == 3){
        return 1;
    }

    printf("Email: ");
    scanf(" %[^\n]", user.email);

    printf("Senha: ");
    scanf(" %[^\n]", user.senha);

    FILE *fp = fopen(FILE_NAME, "a+");
    fprintf(fp, "%d %s %s\n", user.idCargo, user.email, user.senha);
    fclose(fp);
    
    return 0;

}

int login(){
    Usuario user, auth;

    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL){
        printf("Nenhum usuario foi cadastrado! :()");
        return 1;

    }else{

        printf("Insira seu E-mail cadastrado: ");
        scanf(" %[^\n]", user.email);

        printf("Insira sua senha: ");
        scanf(" %[^\n]", user.senha);

        char linha[69];
        while(fgets(linha, 70, fp) != NULL){
            char* token = strtok(linha, " ");

            auth.idCargo = atoi(token);
            token = strtok(NULL, " ");
            strcpy(auth.email, token);
            token = strtok(NULL, " ");
            strcpy(auth.senha, token);
            auth.senha[strlen(auth.senha)-1] = '\0';

            if(strcmp(auth.email, user.email) == 0 && strcmp(auth.senha, user.senha) == 0){
                fclose(fp);
                return 0;
            }
            
        }
        fclose(fp);
        return 1;
    }

        
    }

int login_coord(){

    char login[10];
    char senha[10];

    printf("Digite seu login: ");
    scanf("%s", login);
    printf("Digite sua senha: ");
    scanf("%s", senha);

    if (strcmp(login, "admin") && strcmp(login, "admin")){
        return 0;
    }else{
        return 1;
    }

}

