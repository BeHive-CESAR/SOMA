// #include "residentes_preceptores.h"
#include "login_cadastro.h"
#include "residentes_preceptores.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define FILE_NAME "cadastrados.txt"


void printar_residentes_preceptores(int residencia, int cargo){

    FILE *fp = fopen(FILE_NAME, "r");
    Usuario usuario;

    if (fp == NULL){
        printf("Nenhum usuario cadastrado para essa residencia!\n");
    }else{
        char linha[69];
        while(fgets(linha, 70, fp) != NULL){
            char* token = strtok(linha, " ");

            usuario.idCargo = atoi(token);
            token = strtok(NULL, " ");
            strcpy(usuario.email, token);
            token = strtok(NULL, " ");
            strcpy(usuario.senha, token);
            usuario.senha[strlen(usuario.senha)-1] = '\0';
            token = strtok(NULL, " ");
            usuario.idResidencia = atoi(token);

            if(usuario.idCargo == cargo && usuario.idResidencia == residencia){
                printf("%s\n", usuario.email);
            }      
        }
        fclose(fp);

    }

    
}