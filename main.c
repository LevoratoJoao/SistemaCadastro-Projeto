/**
 * @file main.c
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
#define MAX 5

int main()
{
    Aluno *infoAluno;
    Curso *infoCurso;
    FILE *arqAluno = abrirArqAluno(ALUNO, infoAluno);
    FILE *arqCurso = abrirArqCurso(CURSO, infoCurso);
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
            if (infoAluno == NULL)
            {
                printf("Erro: memoria insuficiente\n");
                exit(1);
            }
            do
            {
                printf("\nRegistro de Alunos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir aluno\n2 - Remover aluno\n3 - Pesquisar\n4 - Alterar aluno\n5 - Listar alunos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
                scanf("%d", &opcao[1]);
                switch (opcao[1])
                {
                case 1:
                    printf("Digite quantos alunos deseja inserir no sistema: ");
                    scanf("%d", &quantidade);
                    infoAluno = inserirAluno(infoAluno, quantidade, quantidadeTotal);
                    break;
                case 2:
                    printf("Como deseja remover o aluno do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[1]);
                    switch (opcao[1])
                    {
                    case 1:
                        printf("Digite o ID do aluno que deseja excluir: ");
                        scanf("%d", &auxNumero);
                        if (removerAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Aluno nao encontrado\n");
                        } else
                        {
                            printf("Aluno removido do sistema!\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            getchar();// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
                            setbuf(stdin, NULL);
                        }
                        break;
                    case 2:
                        printf("Digite o nome do aluno que deseja excluir: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        if (removerAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Aluno nao encontrado\n");
                        } else
                        {
                            printf("Aluno removido do sistema!\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            getchar();// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
                            setbuf(stdin, NULL);
                        }
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
                    break;
                case 3:
                    printf("Como deseja pesquisar o aluno no registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[1]);
                    switch (opcao[1])
                    {
                    case 1:
                        printf("Digite o ID do aluno que deseja pesquisar: ");
                        scanf("%d", &auxNumero);
                        if (pesquisarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Aluno nao encontrado\n");
                        }
                        break;
                    case 2:
                        printf("Digite o nome do aluno que deseja pesquisar: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        if (pesquisarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Aluno nao encontrado\n");
                        }
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
                    break;
                case 4:
                    printf("Como deseja acessar o aluno do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[1]);
                    switch (opcao[1])
                    {
                    case 1:
                        printf("Digite o ID do aluno que deseja alterar: ");
                        scanf("%d", &auxNumero);
                        alterarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal);
                        break;
                    case 2:
                        printf("Digite o nome do aluno que deseja alterar: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        alterarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal);
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
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
                    printf("Opcao invalida! Digite novamente\n");
                    break;
                }
            } while (opcao[1] != 7);
            break;
        case 2:
            infoCurso = (Curso*) calloc(MAX, sizeof(Curso));
            if (infoCurso == NULL)
            {
                printf("Erro: memoria insuficiente\n");
                exit(1);
            }
            do
            {
                printf("\nRegistro de Cursos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir curso\n2 - Remover curso\n3 - Pesquisar curso\n4 - Alterar curso\n5 - Listar cursos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
                scanf("%d", &opcao[1]);
                switch (opcao[1])
                {
                case 1:
                    printf("Digite quantos cursos deseja inserir no sistema: ");
                    scanf("%d", &quantidade);
                    infoCurso = inserirCurso(infoCurso, quantidade, quantidadeTotal);
                    break;
                case 2:
                    printf("Como deseja remover o curso do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[1]);
                    switch (opcao[1])
                    {
                    case 1:
                        printf("Digite o ID do curso que deseja excluir: ");
                        scanf("%d", &auxNumero);
                        if (removerCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Curso nao encontrado\n");
                        }
                        break;
                    case 2:
                        printf("Digite o nome do curso que deseja excluir: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        if (removerCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Curso nao encontrado\n");
                        } else
                        {
                            printf("Curso removido do sistema!\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            getchar();
                            setbuf(stdin, NULL);
                        }
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
                    break;
                case 3:
                    printf("Como deseja pesquisar o curso no registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[1]);
                    switch (opcao[1])
                    {
                    case 1:
                        printf("Digite o ID do curso que deseja pesquisar: ");
                        scanf("%d", &auxNumero);
                        if (pesquisarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Curso nao encontrado\n");
                        }
                        break;
                    case 2:
                        printf("Digite o nome do curso que deseja pesquisar: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        pesquisarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal);
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
                    break;
                case 4:
                    printf("Como deseja acessar o curso do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[1]);
                    switch (opcao[1])
                    {
                    case 1:
                        printf("Digite o ID do curso que deseja alterar: ");
                        scanf("%d", &auxNumero);
                        alterarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal);
                        break;
                    case 2:
                        printf("Digite o nome do curso que deseja alterar: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        alterarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal);
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
                    break;
                case 5:
                    listarCursos(infoCurso, quantidadeTotal);
                    break;
                case 6:
                    arqCurso = salvarArqCurso(arqCurso, infoCurso, quantidadeTotal);
                    break;
                case 7:
                    break;
                default:
                    printf("Opcao invalida! Digite novamente\n");
                    break;
                }
                break;
            } while (opcao[1] != 7);
            break;
        case 3:
            break;
        case 4:
            arqAluno = salvarArqAluno(arqAluno, infoAluno, quantidadeTotal);
            arqCurso = salvarArqCurso(arqCurso, infoCurso, quantidadeTotal);
            break;
        case 5:
            break;
        default:
            printf("Opcao invalida! Digite novamente\n");
            break;
        }
    } while (opcao[0] != 5);
    free(infoAluno);
    free(infoCurso);
    fclose(arqAluno);
    fclose(arqCurso);

    return 0;
}