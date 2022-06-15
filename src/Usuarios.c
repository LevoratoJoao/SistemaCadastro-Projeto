#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuarios.h"
#define MAX 10

void criptografarSenha();

/**
 * @brief
 *
 * @param nome
 * @param usuario
 * @return FILE*
 */
FILE *abrirArqUser(char nome[], User usuario[])
{
    int aux = 0;
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
    }
    printf("Arquivo aberto\n");
    aux = ftell(arq);
    if (aux == 0)
    {
        printf("Arquivo vazio!\n");
        printf("Digite nome usuario: \n");
        fgets(usuario[0].nome, 30, stdin);
        usuario[0].nome[strcspn(usuario[0].nome, "\n")] = '\0';
        printf("Digite a senha: \n");
        fgets(usuario[0].senha, 30, stdin);
        usuario[0].senha[strcspn(usuario[0].senha, "\n")] = '\0';
        criptografarSenha(usuario);
    } else
    {
        printf("Arquivo nao vazio!\n");
        fseek(arq, 0, SEEK_SET);
        fread(usuario, sizeof(User), MAX, arq);
        //PEGAR TOTAL DE USUARIOS
        printf("Lendo os dados do arquivo...\n");
    }
    return arq;
}

/**
 * @brief Função que realiza o cadastro do usuario
 *
 * @param usuario
 */
void cadastrarUser(User usuario[])
{
    int indice = 0;
    printf("CADASTRO USUARIO\n");

    while (indice < MAX)
    {
        //PEGAR TOTAL DE USERS PELO ARQUIVO, NAO SEI FAZER
        //ASSIM NAO PRECISA VERIFICAR QUAL POSICAO TA LIVRE E QUAL NAO ESTA IGUAL EM ALUNOS 
        for (int i = 0; i < MAX; i++)
        {
            printf("Digite nome usuario: \n");
            fgets(usuario[i].nome, 30, stdin);
            usuario[i].nome[strcspn(usuario[i].nome, "\n")] = '\0';
            printf("Digite a senha: \n");
            fgets(usuario[i].senha, 30, stdin);
            usuario[i].senha[strcspn(usuario[i].senha, "\n")] = '\0';
            criptografarSenha(usuario);
        }
        indice++;
    }

}

/**
 * @brief Funcao que criptografa a senha do usuario
 *
 * @param usuario
 */
void criptografarSenha(User usuario[])
{
    for (long unsigned int i = 0; i < strlen(usuario->senha); i++) //strlen() nao vai nao sei o por que
    {
        usuario[0].senha[i] = usuario[0].senha[i] + 1;
    }
}

/**
 * @brief
 *
 * @param usuario
 * @return int
 */
int logarUser(User usuario[])
{
    printf("LOGIN USUARIO\n");
    char nomeAux[31];
    char senhaAux[31];
    int tentativas = 0;

    while (tentativas < 3)
    {
        printf("Digite nome usuario: \n");
        setbuf(stdin, NULL);
        fgets(nomeAux, 30, stdin);
        nomeAux[strcspn(nomeAux, "\n")] = '\0';
        printf("Digite a senha: \n");
        setbuf(stdin, NULL);
        fgets(senhaAux, 30, stdin);
        senhaAux[strcspn(senhaAux, "\n")] = '\0';
        for (long unsigned int i = 0; i < strlen(senhaAux); i++) //strlen() nao vai nao sei o por que
        {
            senhaAux[i] = senhaAux[i] + 1; //criptografa a senha
        }
        if (strcmp(nomeAux, usuario[0].nome) == 0)
        {
            printf("Nome de usuario correto\n");
            if (strcmp(senhaAux, usuario[0].senha) == 0) //verifica se o usuario e senha sao iguais aos do arquivo
            {
                printf("Login realizado com sucesso!\n");
                return 1;
            }
        } else
        {
            printf("Login falhou!\n");
            tentativas++;
        }
    }
    return 0;
}