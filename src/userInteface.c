#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <userInterface.h>
#include <Cursos.h>
#include <utils.h>
#include <Alunos.h>
#include <Matriculas.h>

#define ALUNO "./dataAluno.dat"
#define CURSO "./dataCurso.dat"
#define MATRICULA "./dataMatricula.dat"
#define MAX 10

void alunosOptions();
void cursosOptions();

void userInterface() {

    char *opcao = NULL;

    while (true) {
        printf("\nMENU INICIAL\nOperacoes:\n- Digite o numero da base de dados que deseja acessar:\n1 - Alunos\n2 - Cursos\n3 - Matriculas\n4 - Salvar operacoes\n5 - Sair do sistema\n");
        printf("Digite sua opção:\n");
        opcao = getUserInput();

        if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 5) {
            printf("Opção inválida! Digite novamente:\n");
            free(opcao);
            continue;
        }

        char valorOpcao = atoi(opcao);
        free(opcao);

        switch(valorOpcao) {
            case 1: // Alunos
                alunosOptions();
                break;

            case 2: // Cursos
                cursosOptions();
                break;

            case 3: // Matriculas

                break;

            case 4: // Salvar
    //         arqAluno = salvarArqAluno(arqAluno, alunos, totalAlunos);
    //         arqCurso = salvarArqCurso(arqCurso, infoCurso, totalAlunos);
                break;

            case 5: // Sair
                return;

        }

    }
}

void alunosOptions() {

    // CRIAR ALUNO
    FILE *arquivo = abrirArqAluno(ALUNO);
    int totalAlunos = 0;
    printf("Lendo..");
    Aluno *alunos = getAlunos(arquivo, &totalAlunos);
    printf("BASE DADOS - ALUNOS\n");
    char *id = NULL;
    int idAluno = 0;
    char *nome = NULL;


    while (true) {
        printf("\nRegistro de Alunos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir aluno\n2 - Remover aluno\n3 - Pesquisar\n4 - Alterar aluno\n5 - Listar alunos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
        char *opcao = getUserInput();

        if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 7) {
            printf("Opção inválida! Digite novamente:\n");
            free(opcao);
            continue;
        }

        char valorOpcao = atoi(opcao);
        free(opcao);

        switch (valorOpcao) {
            case 1: // Inserir aluno
                if (alunos == NULL) {
                    printf("Erro ao alocar memória!\n");
                }
                //INSERIR O ALUNO
                alunos = inserirAluno(alunos, &totalAlunos);
                printf("TOTAL ALUNOS: %d\n", totalAlunos);
                break;

            case 2: // Remover aluno
                printf("Digite o ID do aluno a ser removido:\n");
                id = getUserInput();

                idAluno = atoi(id);
                free(id);
                //REMOVER ALUNO
                if (removerAluno(alunos, "\0", idAluno, totalAlunos) == 1) {
                    printf("Aluno nao encontrado\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                } else {
                    printf("Aluno removido do sistema!\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                }
                break;

            case 3: // Pesquisar
                printf("Digite o ID ou nome do aluno a ser pesquisado:\n");
                id = getUserInput();
                idAluno = atoi(id);
                free(id);
                if (pesquisarAluno(alunos, nome, idAluno, totalAlunos) == 1) {
                    printf("Aluno nao encontrado\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                } else {
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                }
                break;

            case 4: // Alterar aluno
                printf("Digite o ID do aluno a ser alterado:\n");
                id = getUserInput();

                idAluno = atoi(id);
                free(id);
                alterarAluno(alunos, "\0", idAluno, totalAlunos);
                break;

            case 5: // Listar alunos
                listarAlunos(alunos, totalAlunos);
                break;

            case 6: // Salvar operacoes
                arquivo = salvarArqAluno(arquivo, alunos, &totalAlunos);
                fclose(arquivo);
                break;

            case 7: // Voltar ao menu inicial
                //Ao voltar ao menu inicial não é possivel voltar ao menu de alunos
                free(alunos);
                return;
                break;
        }
    }
}

void cursosOptions() {

    // CRIAR CURSO
    FILE *arquivo = abrirArqCurso(CURSO);
    int totalCursos = 0;
    printf("Lendo..");
    Curso *cursos = getCursos(arquivo, &totalCursos);
    printf("BASE DADOS - CURSO\n");
    char *id = NULL;
    int idCurso = 0;
    char *nome = NULL;


    while (true) {
        printf("\nRegistro de Cursos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir curso\n2 - Remover curso\n3 - Pesquisar\n4 - Alterar curso\n5 - Listar curso\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
        char *opcao = getUserInput();

        if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 7) {
            printf("Opção inválida! Digite novamente:\n");
            free(opcao);
            continue;
        }

        char valorOpcao = atoi(opcao);
        free(opcao);

        switch (valorOpcao) {
            case 1: // Inserir aluno
                if (cursos == NULL) {
                    printf("Erro ao alocar memória!\n");
                }
                //INSERIR O CURSO
                cursos = inserirCurso(cursos, &totalCursos);
                printf("TOTAL ALUNOS: %d\n", totalCursos);
                break;

            case 2: // Remover cursos
                printf("Digite o ID do curso a ser removido:\n");
                id = getUserInput();

                idCurso = atoi(id);
                free(id);
                //REMOVER CURSO
                if (removerCurso(cursos, "\0", idCurso, totalCursos) == 1) {
                    printf("Cursos nao encontrado\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                } else {
                    printf("Curso removido do sistema!\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                }
                break;

            case 3: // Pesquisar
                printf("Digite o ID ou nome do curso a ser pesquisado:\n");
                id = getUserInput();
                idCurso = atoi(id);
                free(id);
                if (pesquisarCurso(cursos, nome, idCurso, totalCursos) == 1) {
                    printf("curso nao encontrado\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                } else {
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                }
                break;

            case 4: // Alterar cursos
                printf("Digite o ID do curso a ser alterado:\n");
                id = getUserInput();

                idCurso = atoi(id);
                free(id);
                alterarCurso(cursos, "\0", idCurso, totalCursos);
                break;

            case 5: // Listar cursos
                listarCursos(cursos, totalCursos);
                break;

            case 6: // Salvar operacoes
                arquivo = salvarArqCurso(arquivo, cursos, &totalCursos);
                fclose(arquivo);
                break;

            case 7: // Voltar ao menu inicial
                //Ao voltar ao menu inicial não é possivel voltar ao menu de cursos
                free(cursos);
                return;
                break;
        }
    }
}


