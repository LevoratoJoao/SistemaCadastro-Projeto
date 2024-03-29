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
#include <unistd.h>

#include <Usuarios.h>
#include <Alunos.h>
#include <Cursos.h>
#include <userInterface.h>
#include <utils.h>

#define USER "./dataBase/dataUser.dat"
#define MAX 10
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"
#define BLU "\x1B[34m"

int main()
{
    char *opcao = NULL;
    int valorOpcao = 0;
    int totalUsuarios = 0;
    FILE *arqUser = abrirArqUser(USER);
    User *usuario = getUsers(arqUser, &totalUsuarios);

    if (logarUser(usuario, &totalUsuarios) == 1)
    {
        while (1)
        {
            system("clear");
            printf(BLU "----------------------\n- SISTEMA    ESCOLAR -\n----------------------\n");
            printf(CYN"1 - Acessar base de dados\n2 - Cadastrar novo usuario\n3 - Sair\n");
            opcao = getUserInput();

            if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 5) {
                printf("Opção inválida! Digite novamente:\n");
                free(opcao);
                continue;
            }
            valorOpcao = atoi(opcao);
            free(opcao);

            switch(valorOpcao) {
                case 1: // Acessar base de dados
                    system("clear");
                    userInterface();
                    break;
                case 2: // Cadastrar novo usuario
                    system("clear");
                    usuario = cadastrarUser(usuario, &totalUsuarios);
                    break;
                case 3: // Sair
                    printf(GRN"Saindo do sistema...\n");
                    free(usuario);
                    return EXIT_SUCCESS;
                
            }
        }
    }
}