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
#define MAX 5

int main()
{
    Aluno *infoAluno;
    Curso *infoCurso;
    FILE *arqAluno = abrirArqAluno(ALUNO, infoAluno);
    FILE *arqCurso = abrirArqCurso(CURSO, infoCurso);
    int opcao[3] = {[0 ... 2] = 0};//Vetor das opcoes, util para nao ter que criar varias variaveis de opcao para cara submenu
    int quantidade;
    int quantidadeTotal[4] = {[0 ... 3] = 0};//Vetor para armazenar quantidade total de alunos, cursos, matricula e usuarios do sistema, sera utilizado nas funcoes para percorrer o total de cadastros. 0 - Alunos, 1 - Cursos, 2 - Matriculas 3 - Usuarios
    char auxNome[51];//Variavel para pesquisa e remoção de registros pelo nome
    int auxNumero;//Variavel para pesquisa e remoção de registros pelo ID

    do
    {
        printf("Bem Vindo ao sistema\nOperacoes:\n- Digite o numero da base de dados que deseja acessar:\n1 - Alunos\n2 - Cursos\n3 - Matriculas\n4 - Salvar operacoes\n5 - Sair do sistema\n");
        scanf("%d", &opcao[0]);
        switch (opcao[0])
        {
        case 1:
            infoAluno = (Aluno*) calloc(MAX, sizeof(Aluno));
            //Alocar vetor
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
                    //Inserir alunos
                    printf("Digite quantos alunos deseja inserir no sistema: ");
                    scanf("%d", &quantidade);
                    infoAluno = inserirAluno(infoAluno, quantidade, quantidadeTotal);
                    break;
                case 2:
                    //Remover aluno
                    printf("Como deseja remover o aluno do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[2]);
                    switch (opcao[2])
                    {
                    case 1:
                        //Remover por ID
                        printf("Digite o ID do aluno que deseja excluir: ");
                        scanf("%d", &auxNumero);
                        //Verificar se encontrou o aluno (return 1 na funcao = nao achou)
                        if (removerAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Aluno nao encontrado\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        } else
                        {
                            printf("Aluno removido do sistema!\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        }
                        break;
                    case 2:
                        //Remover pelo nome
                        printf("Digite o nome do aluno que deseja excluir: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        //Verificar se encontrou o aluno (return 1 na funcao = nao achou)
                        if (removerAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Aluno nao encontrado\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        } else //Se o retorno nao for 1 entao os dados foram apagados corretamente
                        {
                            printf("Aluno removido do sistema!\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        }
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
                    break;
                case 3:
                    //Pesquisar aluno
                    printf("Como deseja pesquisar o aluno no registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[2]);
                    switch (opcao[2])
                    {
                    case 1:
                        //Pesquisar pelo ID
                        printf("Digite o ID do aluno que deseja pesquisar: ");
                        scanf("%d", &auxNumero);
                        //Verificar se encontrou o aluno (return 1 na funcao = nao achou)
                        if (pesquisarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Aluno nao encontrado\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        }
                        break;
                    case 2:
                        //Pesquisar pelo nome
                        printf("Digite o nome do aluno que deseja pesquisar: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        //Verificar se encontrou o aluno (return 1 na funcao = nao achou)
                        if (pesquisarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Aluno nao encontrado\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        }
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
                    break;
                case 4:
                    //Alterar aluno
                    printf("Como deseja acessar o aluno do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[2]);
                    switch (opcao[2])
                    {
                    case 1:
                        //Alterar por ID
                        printf("Digite o ID do aluno que deseja alterar: ");
                        scanf("%d", &auxNumero);
                        alterarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal);
                        break;
                    case 2:
                        //Alterar pelo nome
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
                    //Listar alunos
                    listarAlunos(infoAluno, quantidadeTotal);
                    break;
                case 6:
                    //Salvar
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
            //Alocar vetor
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
                    //Inserir cursos
                    printf("Digite quantos cursos deseja inserir no sistema: ");
                    scanf("%d", &quantidade);
                    //Ocorre um erro, ao voltar para main os dados sao perdidos, dentro das funções eles estão sendo salvos corretamente
                    infoCurso = inserirCurso(infoCurso, quantidade, quantidadeTotal);
                    break;
                case 2:
                    //Remover curso
                    printf("Como deseja remover o curso do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[2]);
                    switch (opcao[2])
                    {
                    case 1:
                        //Remover pelo ID
                        printf("Digite o ID do curso que deseja excluir: ");
                        scanf("%d", &auxNumero);
                        //Verificar se encontrou o curso (return 1 na funcao = nao achou)
                        if (removerCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Curso nao encontrado\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        } else //Se o retorno nao for 1 entao os dados foram apagados corretamente
                        {
                            printf("Curso removido do sistema!\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        }
                        break;
                    case 2:
                        //Remover pelo nome
                        printf("Digite o nome do curso que deseja excluir: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        //Verificar se encontrou o curso (return 1 na funcao = nao achou)
                        if (removerCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Curso nao encontrado\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        } else //Se o retorno nao for 1 entao os dados foram apagados corretamente
                        {
                            printf("Curso removido do sistema!\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        }
                        break;
                    default:
                        printf("Opcao invalida! Digite novamente\n");
                        break;
                    }
                    break;
                case 3:
                    //Pesquisar curso
                    printf("Como deseja pesquisar o curso no registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[2]);
                    switch (opcao[2])
                    {
                    case 1:
                        //Pesquisar pelo ID
                        printf("Digite o ID do curso que deseja pesquisar: ");
                        scanf("%d", &auxNumero);
                        //Verificar se encontrou o curso (return 1 na funcao = nao achou)
                        if (pesquisarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Curso nao encontrado\n");
                            printf("Aperte ENTER para voltar ao menu\n");
                            setbuf(stdin, NULL);
                            getchar();
                        }
                        break;
                    case 2:
                        //Pesquisar pelo nome
                        printf("Digite o nome do curso que deseja pesquisar: ");
                        setbuf(stdin, NULL);
                        fgets(auxNome, 50, stdin);
                        auxNome[strcspn(auxNome, "\n")] = '\0';
                        //Verificar se encontrou o curso (return 1 na funcao = nao achou)
                        if (pesquisarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
                        {
                            printf("Curso nao encontrado\n");
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
                case 4:
                    //Alterar curso
                    printf("Como deseja acessar o curso do registro ?\n1 - ID\n2 - Nome\n");
                    scanf("%d", &opcao[2]);
                    switch (opcao[2])
                    {
                    case 1:
                        //Buscar pelo ID
                        printf("Digite o ID do curso que deseja alterar: ");
                        scanf("%d", &auxNumero);
                        //Assim como em inserir os dados voltam vazios para a main, dentro da função são salvos
                        alterarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal);
                        break;
                    case 2:
                        //Buscar pelo nome
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
                    //Listar cursos
                    listarCursos(infoCurso, quantidadeTotal);
                    break;
                case 6:
                    //Salvar cursos
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