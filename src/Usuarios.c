#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuarios.h"
#define MAX 10

User *cadastrarUser(User usuario[])
{
    printf("CADASTRO USUARIO\n");
    printf("Digite nome usuario: \n");
    fgets(usuario->usuario, 30, stdin);
    usuario->usuario[strcspn(usuario->usuario, "\n")] = '\0';
    printf("Digite a senha: \n");
    fgets(usuario->senha, 30, stdin);
    usuario->senha[strcspn(usuario->senha, "\n")] = '\0';

    return usuario;
}

FILE *abrirArqUser(char nome[], User usuario[])
{
    FILE *arq = fopen(nome, "r+b");
    if (arq == NULL)
    {
        //se o arquivo nao existe ele cria um novo
        printf("Arquivo nao esta no sistema!\nCriando arquivo...\n");
        arq = fopen(nome, "w+b");
        if (arq == NULL)
        {
            printf("Erro ao abrir arquivo!!!\n");
            return NULL;
        }
        usuario = cadastrarUser(usuario);
    }
    printf("Arquivo aberto\n");
    for (int i = 0; i < MAX; i++)
    {
        //armazena as infformacoes do arquivo na variavel
        fread(&usuario, sizeof(User), 1, arq);
        printf("Lendo os dados do arquivo...\n");
    }
    return arq;
}


User *logarUser()
{
    User *infoUser;


    infoUser = (User*) calloc(MAX, sizeof(User));

    if (strcmp(infoUser[10].usuario, "\0") != 0)
    {
        printf("ola");
    }
    return infoUser;
}