#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Usuarios.h"
#define MAX 10

User *criptografarSenha(User *usuarios, int indice);

/**
 * @brief Função que abre o arquivo de usuários
 *
 * @param nome
 * @return FILE*
 */
FILE *abrirArqUser(char *nome)
{
    FILE *arq = fopen(nome, "r+b"); // abre o arquivo para leitura e escrita
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

    return arq;
}

/**
 * @brief le o arquivo de usuários e armazena os dados em um vetor de usuários
 *
 * @param arquivo
 * @param total
 * @return User*
 */
User *getUsers(FILE *arquivo, int *total)
{
    User *usuarios = NULL; // vetor de usuários
    int cont = 0; // contador de usuários
    while (!feof(arquivo)) { // enquanto não chegar no fim do arquivo
        if (cont % 10 == 0) { // se o contador for divisivel por 10 realoca o vetor
            usuarios = (User*) realloc(usuarios, (cont + 10) * sizeof(User));
        }
        fread(&usuarios[cont], sizeof(User), 1, arquivo);

        if (strcmp(usuarios[0].nome, "\0") == 0) { // se o nome da primeira posicao lida (primeira linha do arquivo) for vazio indica que nao há usuarios cadastrados no sistema entao é feito logo um cadastro e armaazenado no arquivo
            printf("\nOla, seja bem vindo :)\n");
            printf("Digite nome de usuario: \n");
            fgets(usuarios[cont].nome, 30, stdin);
            usuarios[cont].nome[strcspn(usuarios[cont].nome, "\n")] = '\0';
            printf("Digite a senha: \n");
            fgets(usuarios[cont].senha, 30, stdin);
            usuarios[cont].senha[strcspn(usuarios[cont].senha, "\n")] = '\0';
            usuarios = criptografarSenha(usuarios, cont);
            printf("%i\n", cont);
            printf("Usuario: %s / Senha: %s\n", usuarios[cont].nome, usuarios[cont].senha);
            fwrite(&usuarios[cont], sizeof(User), 1, arquivo);
            cont--;
        }
        cont++;

    }
    for (int i = cont + 1; i < cont + MAX; i++) { // Indica que as posições estão vazias
        strcpy(usuarios[i].nome, "\0");
    }
    *total = cont + 1;
    fclose(arquivo);
    return usuarios;
}

/**
 * @brief Função que realiza o cadastro do usuarios
 *
 * @param usuarios
 */
User *cadastrarUser(User *usuarios, int *total)
{
    int indice = 0;
    char nome[31] = {"./dataUser.dat"};
    FILE *arq = fopen(nome, "a+b"); // abre o arquivo para adicionar informações ao final dele
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo!!!\n");
        // exit(1);
        return NULL;
    }
    for (int i = 0; i <= *total; i++) { // procura a primeira posição vazia
        if (strcmp(usuarios[i].nome, "\0") == 0) {
            indice = i;
            break;
        }
    }
    if (indice == *total + MAX) // se não houver posição vazia realoca o vetor
    {
        printf("Nao ha espaco disponivel...\nRealocando...\n");
        int realocador = MAX;
        realocador += 10;
        usuarios = (User*) realloc(usuarios, realocador * sizeof(User)); //realoca para preencher mais
        if (usuarios == NULL)
        {
            printf("Erro: memoria insuficiente\n");
            return NULL;//return -1;
        }
    }
    //preenchimento do usuario
    printf("- CADASTRO USUARIOS ----------------------\n");
    printf("\nOla, seja bem vindo ao sistema :)\n");
    printf("Digite nome de usuario: \n");
    fgets(usuarios[indice].nome, 30, stdin);
    usuarios[indice].nome[strcspn(usuarios[indice].nome, "\n")] = '\0';
    printf("Digite a senha: \n");
    fgets(usuarios[indice].senha, 30, stdin);
    usuarios[indice].senha[strcspn(usuarios[indice].senha, "\n")] = '\0';
    criptografarSenha(usuarios, indice);
    printf("Usuario: %s / Senha: %s\n", usuarios[indice].nome, usuarios[indice].senha);
    fwrite(&usuarios[indice], sizeof(User), 1, arq);
    fclose(arq);
    return usuarios;
}

/**
 * @brief Funcao que criptografa a senha do usuario
 *
 * @param usuarios
 */
User *criptografarSenha(User *usuarios, int indice)
{
    printf("Criptografando senha...\n");
    usleep(100000);
    for (long unsigned int i = 0; i < strlen(usuarios[indice].senha); i++)
    {
        usuarios[indice].senha[i] = usuarios[indice].senha[i] + 2; // criptografa a senha
    }
    return usuarios;
}

/**
 * @brief Funcao que realiza o login do usuario
 *
 * @param usuarios
 * @param total
 * @return int
 */
int logarUser(User usuarios[], int *total)
{
    system("clear");
    printf("- LOGIN ----------------------\n");
    char nomeAux[31];
    char senhaAux[31];
    int tentativas = 0;

    while (tentativas < 3) // loop que realiza o login ate que o usuario digite 3 vezes a senha incorreta
    {
        printf("Digite nome usuarios: \n");
        setbuf(stdin, NULL);
        fgets(nomeAux, 30, stdin);
        nomeAux[strcspn(nomeAux, "\n")] = '\0';
        printf("Digite a senha: \n");
        setbuf(stdin, NULL);
        fgets(senhaAux, 30, stdin);
        senhaAux[strcspn(senhaAux, "\n")] = '\0';
        for (long unsigned int i = 0; i < strlen(senhaAux); i++)
        {
            senhaAux[i] = senhaAux[i] + 2; //criptografa a senha auxiliar
        }
        for (int i = 0; i <= *total; i++)
        {
            if (strcasecmp(usuarios[i].nome, nomeAux) == 0) // compara o nome do usuario com o nome digitado
            {
                if (strcmp(senhaAux, usuarios[i].senha) == 0) //verifica se a senha auxiliar e senha do usuario da posicao sao iguais
                {
                    printf("Login realizado com sucesso!\n");
                    printf("Carregando...\n");
                    fflush(stdout);
                    usleep(2000000);
                    return 1;
                }
            }
        }
        printf("Nome ou senha de usuarios incorretos\n");
        tentativas++;
    }
    printf("ATENCAO...\nVoce excedeu o numero de tentativas\n");
    printf("Tentativas: %i\n", tentativas);
    printf("Login falhou\n");
    return 0;
}