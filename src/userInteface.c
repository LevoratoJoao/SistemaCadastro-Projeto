#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include <userInterface.h>
#include <Cursos.h>
#include <utils.h>
#include <Alunos.h>
#include <Matriculas.h>

#define ALUNO "./dataAluno.dat"
#define CURSO "./dataCurso.dat"
#define MATRICULA "./dataMatricula.dat"
#define MAX 10
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define CYN "\x1B[36m"
#define BLU "\x1B[34m"
#define RESET "\x1B[0m"

Aluno *alunosOptions(Aluno *alunos);
Curso *cursosOptions(Curso *cursos);
Matricula *matriculasOptions(Matricula *matriculas, Aluno *alunos, Curso *cursos);

void userInterface() {
    Aluno *alunos = NULL;
    Curso *cursos = NULL;
    Matricula *matriculas = NULL;
    char *opcao = NULL;

    while (true) {
        printf(BLU"----------------------\n- SISTEMA DE ESCOLAR -\n----------------------\n");
        printf("---- MENU INICIAL ----\n");
        printf(CYN"- Digite o numero da base de dados que deseja acessar:\n- 1 . Alunos\n- 2 . Cursos\n- 3 . Matriculas\n- 4 . Salvar operacoes\n- 5 . Sair do sistema\n----------------------\n");
        printf("Digite sua opção:\n");
        opcao = getUserInput();

        if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 5) {
            printf(YEL"Opção inválida! Digite novamente:\n");
            fflush(stdout);
            usleep(900000);
            free(opcao);
            continue;
        }

        char valorOpcao = atoi(opcao);
        free(opcao);

        switch(valorOpcao) {
            case 1: // Alunos
                alunos = alunosOptions(alunos);
                break;

            case 2: // Cursos
                cursos = cursosOptions(cursos);
                break;

            case 3: // Matriculas
                matriculas = matriculasOptions(matriculas, alunos, cursos);
                break;

            case 4: // Salvar
    //          arqAluno = salvarArqAluno(arqAluno, alunos, totalAlunos);
    //          arqCurso = salvarArqCurso(arqCurso, infoCurso, totalAlunos);
                break;

            case 5: // Sair
                free(alunos);
                free(cursos);
                free(matriculas);
                return;
                break;
        }

    }
}

Aluno *alunosOptions(Aluno *alunos) {

    // CRIAR ALUNO
    FILE *arquivo = abrirArqAluno(ALUNO);

    int totalAlunos = 0;

    printf(GRN"Carregando...\n");
    fflush(stdout);
    usleep(900000);
    system("clear");
    alunos = getAlunos(arquivo, &totalAlunos);

    char *id = NULL;
    int idAluno = 0;
    char *nome = {"\0"};
    int retorno = 0;

    printf(BLU"------------------\n--- BASE DADOS ---\n------------------\n----- ALUNOS -----\n");

    while (true) {
        printf(BLU"Registro de Alunos"CYN"\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir aluno\n2 - Remover aluno\n3 - Pesquisar\n4 - Alterar aluno\n5 - Listar alunos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
        char *opcao = getUserInput();

        if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 7) {
            printf(YEL"Opção inválida! Digite novamente:\n");
            fflush(stdout);
            usleep(900000);
            free(opcao);
            continue;
        }

        char valorOpcao = atoi(opcao);
        free(opcao);

        switch (valorOpcao) {
            case 1: // Inserir aluno
                if (alunos == NULL) {
                    printf(YEL"Erro ao alocar memória!\n");
                }
                //INSERIR O ALUNO
                alunos = inserirAluno(alunos, &totalAlunos);
                printf(CYN"TOTAL ALUNOS: %d\n", totalAlunos);
                break;

            case 2: // Remover aluno
                printf("Remover aluno por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf(YEL"Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf(CYN"Digite o nome do aluno a ser removido:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);

                    retorno = removerAluno(alunos, nome, idAluno, &totalAlunos);
                    //REMOVER ALUNO POR NOME
                    if (retorno == 1) {

                        free(nome);
                        printf(YEL"Aluno nao encontrado\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());

                    } else if (retorno == 0){

                        free(nome);
                        printf(GRN"Aluno removido do sistema!\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());

                    } else {

                        printf(GRN"Operacao finalizada\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());

                    }
                } else {
                    printf("Digite o ID do aluno a ser removido:\n");
                    id = getUserInput();
                    idAluno = atoi(id);
                    free(id);
                    retorno = removerAluno(alunos, nome, idAluno, &totalAlunos);
                    if (retorno == 1) {

                        printf(YEL"Aluno nao encontrado\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());

                    } else if (retorno == 0) {

                        printf(GRN"Aluno removido do sistema!\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());

                    } else {
                        printf(GRN"Operacao finalizada\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    }
                }
                break;

            case 3: // Pesquisar
                printf("Pesquisar aluno por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf(YEL"Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf(CYN"Digite o nome do aluno a ser pesquisado:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);
                    //PESQUISAR ALUNO POR NOME
                    retorno = pesquisarAluno(alunos, nome, idAluno, totalAlunos);
                    if (retorno == 1) {
                        free(nome);
                        printf(YEL"Aluno nao encontrado\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        free(nome);
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    }
                } else {
                    printf("Digite o ID do aluno a ser pesquisado:\n");
                    id = getUserInput();
                    idAluno = atoi(id);
                    free(id);
                    //PESQUISAR ALUNO POR ID
                    retorno = pesquisarAluno(alunos, nome, idAluno, totalAlunos);
                    if (retorno == 1) {
                        printf(YEL"Aluno nao encontrado\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    }
                }
                break;

            case 4: // Alterar aluno
                printf("Alterar aluno por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf(YEL"Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf(CYN"Digite o nome do aluno a ser alterado:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);

                    //ALTERAR ALUNO POR NOME
                    alterarAluno(alunos, nome, idAluno, totalAlunos); //Chamada da função alterarAluno
                    free(nome);
                    sleep(1);
                } else {
                    printf("Digite o ID do aluno a ser alterado:\n");
                    id = getUserInput();
                    idAluno = atoi(id);
                    free(id);

                    //ALTERAR ALUNO POR ID
                    alterarAluno(alunos, nome, idAluno, totalAlunos); //Chamada da função alterarAluno
                    sleep(1);
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
                //system("clear");
                return alunos;
                break;
        }
    }
    return alunos;
}

Curso *cursosOptions(Curso *cursos) {

    // CRIAR CURSO
    FILE *arquivo = abrirArqCurso(CURSO);
    //FILE *arquivoMatricula = abrirArqMatricula(MATRICULA);

    int totalCursos = 0;
    //int totalMatriculas = 0;

    printf("Carregando...\n");
    fflush(stdout);
    usleep(900000);
    system("clear");

    cursos = getCursos(arquivo, &totalCursos);
    //matriculas = getMatricula(arquivoMatricula, &totalMatriculas);

    char *id = NULL;
    int idCurso = 0;
    char *nome = {"\0"};
    int retorno = 0;

    printf(BLU"------------------\n----- BASE DADOS -----\n------------------\n----- CURSOS -----\n");

    while (true) {
        printf(BLU"\nRegistro de Cursos"CYN"\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir curso\n2 - Remover curso\n3 - Pesquisar\n4 - Alterar curso\n5 - Listar curso\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
        char *opcao = getUserInput();

        if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 7) {
            printf(YEL"Opção inválida! Digite novamente:\n");
            free(opcao);
            continue;
        }

        char valorOpcao = atoi(opcao);
        free(opcao);

        switch (valorOpcao) {
            case 1: // Inserir aluno
                if (cursos == NULL) {
                    printf(RED"Erro ao alocar memória!\n");
                }
                //INSERIR O CURSO
                cursos = inserirCurso(cursos, &totalCursos);
                printf(CYN"TOTAL CURSOS: %d\n", totalCursos);
                break;

            case 2: // Remover cursos
                printf("Remover curso por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf(YEL"Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf(CYN"Digite o nome do curso a ser removido:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);

                    //REMOVER CURSO POR NOME
                    retorno = removerCurso(cursos, nome, idCurso, totalCursos);
                    if (retorno == 1) {

                        free(nome);
                        printf(YEL"Curso nao encontrado\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());

                    } else if (retorno == 0) {
                        free(nome);
                        printf(GRN"Curso removido do sistema!\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf("Operacao finalizada\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    }
                } else {
                    printf("Digite o ID do curso a ser removido:\n");
                    id = getUserInput();
                    idCurso = atoi(id);
                    free(id);
                    //REMOVER CURSO POR ID
                    retorno = removerCurso(cursos, nome, idCurso, totalCursos);
                    if (retorno == 1) {
                        printf(YEL"Curso nao encontrado\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else if (retorno == 0) {
                        printf(GRN"Curso removido do sistema!\n");
                        printf("Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    } else {
                        printf(GRN"Operacao finalizada\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
                        free(getUserInput());
                    }
                }
                break;

            case 3: // Pesquisar
                printf("Pesquisar curso por:\n1 - nome\n2 - ID\n");
                opcao = getUserInput();
                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 2) {
                    printf(YEL"Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf(CYN"Digite o nome do curso a ser pesquisado:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);

                    //PESQUISAR CURSO POR NOME
                    if (pesquisarCurso(cursos, nome, idCurso, totalCursos) == 1) {
                        printf(YEL"Curso nao encontrado\n");
                        free(nome);
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
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

                    //PESQUISAR CURSO POR ID
                    if (pesquisarCurso(cursos, nome, idCurso, totalCursos) == 1) {
                        printf(YEL"Curso nao encontrado\n");
                        printf(CYN"Aperte ENTER para voltar ao menu\n");
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
                    printf(YEL"Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                valorOpcao = atoi(opcao);
                free(opcao);
                if (valorOpcao == 1) {
                    printf(CYN"Digite o nome do curso a ser alterado:\n");
                    nome = getUserInput();
                    printf("Nome: %s\n", nome);

                    //ALTERAR CURSO POR NOME
                    alterarCurso(cursos, nome, idCurso, totalCursos);
                    free(nome);
                    printf("Aperte ENTER para voltar ao menu\n");
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
                //free(matriculas);
                return cursos;
                break;
        }
    }
    return cursos;
}

Matricula *matriculasOptions(Matricula *matriculas, Aluno *alunos, Curso *cursos) {

    // CRIAR MATRICULA
    FILE *arquivoCurso = abrirArqCurso(CURSO);
    FILE *arquivoAluno = abrirArqAluno(ALUNO);
    FILE *arquivo = abrirArqMatricula(MATRICULA);

    int totalAlunos = 0;
    int totalMatriculas = 0;
    int totalCursos = 0;

    printf("Carregando...\n");
    fflush(stdout);
    usleep(900000);
    system("clear");

    alunos = getAlunos(arquivoAluno, &totalAlunos);
    cursos = getCursos(arquivoCurso, &totalCursos);
    matriculas = getMatricula(arquivo, &totalMatriculas);

    int idMatricula = 0;
    int retorno = 0;

    printf(BLU"----------------------\n----- BASE DADOS -----\n----------------------\n----- MATRICULAS -----\n");

    while (true) {
        printf(BLU"Registro de Matriculas"CYN"\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir matricula\n2 - Excluir matricula\n3 - Pesquisar\n4 - Alterar matricula\n5 - Listar matriculas\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");
        char *opcao = getUserInput();

        if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 7) {
            printf(YEL"Opção inválida! Digite novamente:\n");
            free(opcao);
            continue;
        }

        int valorOpcao = atoi(opcao);
        free(opcao);

        switch (valorOpcao) {
            case 1: // Inserir matricula
                if (matriculas == NULL) {
                    printf(RED"Erro ao alocar memória!\n");
                }
                //INSERIR O MATRICULA
                matriculas = inserirMatricula(matriculas,  alunos, cursos, &totalMatriculas, &totalAlunos, &totalCursos);
                printf(CYN"TOTAL MATRICULAS: %d\n", totalMatriculas);
                break;

            case 2: // Remover matricula
                printf("Digite o ID da matricula a ser removido:\n");
                opcao = getUserInput();
                idMatricula = atoi(opcao);
                free(opcao);

                //REMOVER MATRICULA
                retorno = removerMatricula(matriculas, idMatricula, &totalAlunos);
                if (retorno == 1) {
                    printf(YEL"Matricula nao encontrado\n");
                    printf(CYN"Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());

                } else if (retorno == 0) {
                    printf("Matricula removido do sistema!\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());

                } else {
                    printf(GRN"Operacao finalizada\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                }
                break;

            case 3: // Pesquisar
                printf(CYN"Digite o ID da matricula a ser pesquisada:\n");
                opcao = getUserInput();
                idMatricula = atoi(opcao);
                free(opcao);

                //PESQUISAR MATRICULA POR ID
                retorno = pesquisarMatricula(matriculas, idMatricula, totalAlunos);
                if (retorno == 1) {
                    printf(YEL"Matricula nao encontrada\n");
                    printf(CYN"Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                } else {
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());
                }
                break;

            case 4: // Alterar matricula
                printf("Digite o ID da matricula a ser alterada:\n");
                opcao = getUserInput();
                idMatricula = atoi(opcao);
                free(opcao);

                //ALTERAR MATRICULA POR ID
                alterarMatricula(matriculas, idMatricula, totalAlunos, alunos, cursos, &totalAlunos, &totalCursos);
                printf("Aperte ENTER para voltar ao menu\n");
                free(getUserInput());
                break;

            case 5: // Listar alunos
                listarMatriculas(matriculas, totalMatriculas);
                break;

            case 6: // Salvar operacoes
                arquivo = salvarArqMatricula(arquivo, matriculas, &totalMatriculas);
                fclose(arquivo);
                break;

            case 7: // Voltar ao menu inicial
                //system("clear");
                free(alunos);
                free(cursos);
                return matriculas;
                break;
        }
    }
    return matriculas;
}


