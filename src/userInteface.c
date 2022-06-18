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
//void matriculasOptions();

void userInterface() {

    char *opcao = NULL;

    while (true) {
        printf("----------------------\n- SISTEMA DE ESCOLAR -\n----------------------\n");
        printf("---- MENU INICIAL ----\n");
        printf("\nOperacoes:\n- Digite o numero da base de dados que deseja acessar:\n1 - Alunos\n2 - Cursos\n3 - Matriculas\n4 - Salvar operacoes\n5 - Sair do sistema\n");
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
                //matriculasOptions();
                break;

            case 4: // Salvar
    //         arqAluno = salvarArqAluno(arqAluno, alunos, totalAlunos);
    //         arqCurso = salvarArqCurso(arqCurso, infoCurso, totalAlunos);
                break;

            case 5: // Sair
                //system("clear");
                return;

        }

    }
}

void alunosOptions() {

    // CRIAR ALUNO
    FILE *arquivo = abrirArqAluno(ALUNO);
    int totalAlunos = 0;
    printf("Carregando...\n");
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
                printf("Remover aluno por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf("Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf("Digite o nome do aluno a ser removido:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);
                    //REMOVER ALUNO POR NOME
                    if (removerAluno(alunos, nome, idAluno, totalAlunos) == 1) {
                        printf("Aluno nao encontrado\n");
                        free(nome);
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf("Aluno removido do sistema!\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(nome);
                        free(getUserInput());
                    }
                } else {
                    printf("Digite o ID do aluno a ser removido:\n");
                    id = getUserInput();
                    idAluno = atoi(id);
                    free(id);
                    if (pesquisarAluno(alunos, nome, idAluno, totalAlunos) == 1) {
                        printf("Aluno nao encontrado\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf("Aluno removido do sistema!\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    }
                }
                break;

            case 3: // Pesquisar
                printf("Pesquisar aluno por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf("Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf("Digite o nome do aluno a ser pesquisado:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);
                    //PESQUISAR ALUNO POR NOME
                    if (pesquisarAluno(alunos, nome, idAluno, totalAlunos) == 1) {
                        printf("Aluno nao encontrado\n");
                        free(nome);
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(nome);
                        free(getUserInput());
                    }
                } else {
                    printf("Digite o ID do aluno a ser pesquisado:\n");
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
                }
                break;

            case 4: // Alterar aluno
                printf("Alterar aluno por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf("Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf("Digite o nome do aluno a ser alterado:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);
                    //ALTERAR ALUNO POR NOME
                    alterarAluno(alunos, nome, idAluno, totalAlunos);
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(nome);
                    free(getUserInput());
                } else {
                    printf("Digite o ID do aluno a ser alterado:\n");
                    id = getUserInput();
                    idAluno = atoi(id);
                    free(id);
                    alterarAluno(alunos, nome, idAluno, totalAlunos);
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(nome);
                    free(getUserInput());
                }
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
                //system("clear");
                return;
                break;
        }
    }
}

void cursosOptions() {

    // CRIAR CURSO
    FILE *arquivo = abrirArqCurso(CURSO);
    int totalCursos = 0;
    printf("Carregando...");
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
                printf("TOTAL CURSOS: %d\n", totalCursos);
                break;

            case 2: // Remover cursos
                printf("Remover curso por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf("Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf("Digite o nome do curso a ser removido:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);
                    //REMOVER CURSO POR NOME
                    if (removerCurso(cursos, nome, idCurso, totalCursos) == 1) {
                        printf("Curso nao encontrado\n");
                        free(nome);
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf("Curso removido do sistema!\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(nome);
                        free(getUserInput());
                    }
                } else {
                    printf("Digite o ID do curso a ser removido:\n");
                    id = getUserInput();
                    idCurso = atoi(id);
                    free(id);
                    if (removerCurso(cursos, nome, idCurso, totalCursos) == 1) {
                        printf("Curso nao encontrado\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf("Curso removido do sistema!\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    }
                }
                break;

            case 3: // Pesquisar
                printf("Pesquisar curso por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf("Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf("Digite o nome do curso a ser pesquisado:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);
                    //REMOVER CURSO POR NOME
                    if (pesquisarCurso(cursos, nome, idCurso, totalCursos) == 1) {
                        printf("Curso nao encontrado\n");
                        free(nome);
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(nome);
                        free(getUserInput());
                    }
                } else {
                    printf("Digite o ID do curso a ser pesquisado:\n");
                    id = getUserInput();
                    idCurso = atoi(id);
                    free(id);
                    if (pesquisarCurso(cursos, nome, idCurso, totalCursos) == 1) {
                        printf("Curso nao encontrado\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    }
                }
                break;

            case 4: // Alterar cursos
                printf("Alterar curso por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf("Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf("Digite o nome do curso a ser alterado:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);
                    //ALTERAR CURSO POR NOME
                    alterarCurso(cursos, nome, idCurso, totalCursos);
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(nome);
                    free(getUserInput());
                } else {
                    printf("Digite o ID do curso a ser pesquisado:\n");
                    id = getUserInput();
                    idCurso = atoi(id);
                    free(id);
                    //ALTERAR CURSO POR ID
                    alterarCurso(cursos, nome, idCurso, totalCursos);
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                }
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
                //system("clear");
                return;
                break;
        }
    }
}

// void matriculasOptions() {

//     // CRIAR MATRICULA
//     FILE *arquivo = abrirArqMatricula(MATRICULA);
//     int totalMatriculas = 0;
//     printf("Carregando...\n");
//     Matricula *matriculas = getMatricula(arquivo, &totalMatriculas);
//     printf("BASE DADOS - MATRICULAS\n");
//     char *id = NULL;
//     int idMatricula = 0;
//     char *nome = NULL;
// }


