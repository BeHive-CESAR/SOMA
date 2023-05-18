#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login_cadastro.h"

#define FILE_NAME "cadastrados.txt"
#define TRUE 0
#define FALSE 1


void cadastrar(){

    Usuario user;

    printf("Cargo\n[1]Preceptor [2]Residente:  ");
    scanf("%d", &user.idCargo);

    printf("Email: ");
    scanf(" %[^\n]", user.email);

    printf("Senha: ");
    scanf(" %[^\n]", user.senha);

    FILE *fp = fopen(FILE_NAME, "a+");
    fprintf(fp, "%d %s %s\n", user.idCargo, user.email, user.senha);
    fclose(fp);

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

