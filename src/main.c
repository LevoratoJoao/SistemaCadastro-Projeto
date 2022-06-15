/**
 * @file main.c
 * @author Alexandre Aparecido da Silva (alexandreaparecido@alunos.utfpr.edu.br)
 * @author João Vitor Levorato de Souza (joaosouza.2021@alunos.utfpr.edu.br)
 * @brief
 * @version 0.1
 * @date 2022-06-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Usuarios.h>
#include <Alunos.h>
#include <Cursos.h>
#include <userInterface.h>
#include <utils.h>

#define USER "../dataUser.dat"
#define MAX 10

int main()
{
    /*
    User *usuario = NULL;
    char *opcao = NULL;
    usuario = (User*) calloc(MAX, sizeof(User));
    FILE *arqUser = abrirArqUser(USER, usuario);

    if (logarUser(usuario) == 1)
    {
        while (1)
        {
            printf("Bem vindo ao sistema!\n");
            printf("1 - Acessar base de dados\n2 - Cadastrar novo usuario\n3 - Sair\n");
            opcao = getUserInput();

            if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 5) {
                printf("Opção inválida! Digite novamente:\n");
                free(opcao);
                continue;
            }
            char valorOpcao = atoi(opcao);
            free(opcao);

            switch(valorOpcao) {
                case 1: // Acessar base de dados
                    userInterface();
                    break;
                case 2: // Cadastrar novo usuario
                    cadastrarUser(usuario);
                    break;
                case 3: // Sair
                    printf("Saindo do sistema...\n");
                    break;
            }
        }
    }


     LoginInterface prototipo:
        - abrir o arquivo de usuario e armazenar na variavel de usuario
        - se o arquivo estiver vazio, pede novo cadastro e criptografa a senha, apos cadastro ira pedir login novamente
        - a cada vez que colocar a senha ela é criptografada para poder ser comparada a senha original
        - verificar se os dados armazenados na variavel da struct correspondem com os dados informados para o login
        - se for libera acesso ao menu do sistema
        - se nao for mostra uma mensagem de login errado e pede novamente
        - apos login, perguntar se quer entrar nos menus do sistema ou se quer cadastrar novo usuario

    fclose(arqUser);
    // free(infoAluno);
    // free(infoCurso);
    // fclose(arqAluno);
    // fclose(arqCurso);
    */
    userInterface();
    return 0;
}