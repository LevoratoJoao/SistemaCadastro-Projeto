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
#include "Usuarios.h"
#include "Alunos.h"
#include "Cursos.h"
#define ALUNO "dataAluno.dat"
#define CURSO "dataCurso.dat"
#define MATRICULA "dataMatricula.dat"
#define USER "dataUser.dat"
#define MAX 10

int main()
{
    Aluno *infoAluno;
    FILE *arqAluno = abrirArqAluno(ALUNO, infoAluno);
    int opcao[2] = {[0 ... 1] = 0};//Vetor das opcoes, util para nao ter que criar varias variaveis de opcao para cara submenu
    int quantidade;
    int quantidadeTotal[4] = {[0 ... 3] = MAX};//Vetor para armazenar quantidade total de alunos, cursos, matricula e usuarios do sistema, sera utilizado nas funcoes para percorrer o total de cadastros. 0 - Alunos, 1 - Cursos, 2 - Matriculas 3 - Usuarios
    char auxNome[51];//Variavel para pesquisa e remoção de registros pelo nome
    int auxNumero;//Variavel para pesquisa e remoção de registros pelo ID

    do
    {
        printf("Bem Vindo ao sistema\nOperacoes:\n- Digite o numero da base de dados que deseja usar:\n1 - Alunos\n2 - Cursos\n3 - Matriculas\n4 - Salvar operacoes\n5 - Sair do sistema\n");
        scanf("%d", &opcao[0]);
        switch (opcao[0])
        {
        case 1:
            infoAluno = (Aluno*) calloc(MAX, sizeof(Aluno));
            do
            {
                printf("\nRegistro de Alunos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir aluno\n2 - Remover aluno\n3 - Pesquisar\n4 - Alterar aluno\n5 - Listar alunos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
                scanf("%d", &opcao[1]);
                switch (opcao[1])
                {
                case 1:
                    printf("Digite quantos alunos deseja inserir no sistema: ");
                    scanf("%d", &quantidade);
                    quantidadeTotal[0] = inserirAluno(infoAluno, quantidade, quantidadeTotal);
                    break;
                case 2:
                    printf("Como deseja remover o aluno do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[1]);
                    switch (opcao[1])
                    {
                    case 1:
                        printf("Digite o ID do aluno que deseja excluir: ");
                        scanf("%d", &auxNumero);
                        removerAluno(infoAluno, auxNome, auxNumero, quantidadeTotal);
                        break;
                    case 2:
                        printf("Digite o nome do aluno que deseja excluir: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        removerAluno(infoAluno, auxNome, auxNumero, quantidadeTotal);
                        break;
                    default:
                        break;
                    }
                    break;
                case 3:
                    break;
                case 4:
                    printf("HEHE");
                    break;
                case 5:
                    listarAlunos(infoAluno, quantidadeTotal);
                    break;
                case 6:
                    arqAluno = salvarArqAluno(arqAluno, infoAluno, quantidadeTotal);
                    break;
                case 7:
                    break;
                default:
                    printf("Opcao invalida!!!");
                    break;
                }
            } while (opcao[1] != 7);
            break;
        case 2:
            do
            {
                printf("\nRegistro de Cursos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir curso\n2 - Remover curso\n3 - Pesquisar curso\n4 - Alterar curso\n5 - Listar cursos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
                scanf("%d", &opcao[1]);
                switch (opcao[1])
                {
                case 1:
                    printf("Digite quantos alunos deseja inserir no sistema: ");
                    scanf("%d", &quantidade);
                    inserirAluno(infoAluno, quantidade, quantidadeTotal);
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    printf("HEHE");
                    break;
                case 5:
                    printf("teste");
                    break;
                default:
                    printf("Opcao invalida!!!");
                    break;
                }
                break;
            } while (opcao[1] != 7);
            break;
        case 3:

            break;
        case 4:
            break;
        default:
            break;
        }
    } while (opcao[0] != 5);

    fclose(arqAluno);

    return 0;
}