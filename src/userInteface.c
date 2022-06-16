#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <userInterface.h>
#include <Cursos.h>
#include <utils.h>
#include <Alunos.h>
#include <Matriculas.h>

#define ALUNO "../dataAluno.dat"
#define CURSO "../dataCurso.dat"
#define MATRICULA "../dataMatricula.dat"
#define MAX 10

void alunosOptions();
void cursosOptions();

void userInterface() {

    char *opcao = NULL;

    while (true) {
        printf("Bem Vindo ao sistema\nOperacoes:\n- Digite o numero da base de dados que deseja acessar:\n1 - Alunos\n2 - Cursos\n3 - Matriculas\n4 - Salvar operacoes\n5 - Sair do sistema\n");
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
                //cursosOptions();
                break;

            case 3: // Matriculas

                break;

            case 4: // Salvar
    //         arqAluno = salvarArqAluno(arqAluno, infoAluno, totalAlunos);
    //         arqCurso = salvarArqCurso(arqCurso, infoCurso, totalAlunos);
                break;

            case 5: // Sair
                return;

        }

    }
}

void alunosOptions() {

    // CRIAR ALUNO
    FILE *arquivo = abrirArqAluno(ALUNO); // NAO ESQUECER DE FECHAR O ARQUIVO
    int totalAlunos;
    printf("Lendo..");
    Aluno *infoAluno = getAlunos(arquivo, &totalAlunos); // NAO ESQUECER DE DAR FREE

    // Aluno *infoAluno = NULL;
    // infoAluno = (Aluno*) calloc(MAX, sizeof(Aluno));
    // int totalAlunos = MAX;
    // FILE *arqAluno = abrirArqAluno(ALUNO, infoAluno);
    // infoAluno = lerArquivo(arqAluno, infoAluno, &totalAlunos);
    printf("BASE DADOS - ALUNOS\n");
    char *id = NULL;
    int idAluno = 0;


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
                if (infoAluno == NULL) {
                    printf("Erro ao alocar memória!\n");
                }
                //INSERIR O ALUNO
                infoAluno = inserirAluno(infoAluno, &totalAlunos);

                // for (int i = 0; i < totalAlunos; i++)
                // {
                //     printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);//Mostra as informacoes atuais do aluno
                // }

                printf("TOTAL ALUNOS: %d\n", totalAlunos);
                break;

            case 2: // Remover aluno
                printf("Digite o ID do aluno a ser removido:\n");
                id = getUserInput();

                idAluno = atoi(id);
                free(id);
                //REMOVER ALUNO
                if (removerAluno(infoAluno, "\0", idAluno, totalAlunos) == 1) {
                    printf("Aluno nao encontrado\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    setbuf(stdin, NULL);
                    getchar();
                } else {
                    printf("Aluno removido do sistema!\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    setbuf(stdin, NULL);
                    getchar();
                }
                break;

            case 3: // Pesquisar
                printf("Digite o ID do aluno a ser pesquisado:\n");
                id = getUserInput();
                idAluno = atoi(id);
                free(id);
                // SUGESTÃO DO ENTER: free(getUserInput());
                if (pesquisarAluno(infoAluno, "\0", idAluno, totalAlunos) == 1) {
                    printf("Aluno nao encontrado\n");
                    printf("Aperte ENTER para voltar ao menu\n");
                    setbuf(stdin, NULL);
                    getchar();
                }
                break;

            case 4: // Alterar aluno
                printf("Digite o ID do aluno a ser alterado:\n");
                id = getUserInput();

                idAluno = atoi(id);
                free(id);
                alterarAluno(infoAluno, "\0", idAluno, totalAlunos);
                break;

            case 5: // Listar alunos
                listarAlunos(infoAluno, totalAlunos);
                break;

            case 6: // Salvar operacoes
                arquivo = salvarArqAluno(arquivo, infoAluno, &totalAlunos);
                break;

            case 7: // Voltar ao menu inicial
                free(infoAluno);
                fclose(arquivo);
                return;
                break;
        }
    }
}

// void cursosOptions() {
//     Curso *infoCurso = NULL;

//     printf("\nRegistro de Cursos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir curso\n2 - Remover curso\n3 - Pesquisar curso\n4 - Alterar curso\n5 - Listar cursos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");

//     while (true) {
//         char *opcao = getUserInput();

//         if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 7) {
//             printf("Opção inválida! Digite novamente:\n");
//             free(opcao);
//             continue;
//         }

//         char valorOpcao = atoi(opcao);
//         free(opcao);

//         switch (valorOpcao) {
//             case 1: // Inserir curso
//                 printf("Digite a quantidade de cursos que deseja inserir:\n");
//                 char *quantidade = getUserInput();
//                 int qtd = atoi(quantidade);
//                 free(quantidade);

//                 // INSERIR O CURSO
//                 // infoCurso = inserirCurso(infoCurso, quantidade, totalAlunos);

//                 break;

//             case 2: // Remover curso
//                 printf("Digite o ID do curso a ser removido:\n");

//                 char *id = getUserInput();
//                 int idCurso = atoi(id);
//                 free(id);

//     //                     if (removerCurso(infoCurso, auxNome, auxNumero, totalAlunos) == 1)
//     //                     {
//     //                         printf("Curso nao encontrado\n");
//     //                         printf("Aperte ENTER para voltar ao menu\n");
//     //                         setbuf(stdin, NULL);
//     //                         getchar();
//     //                     } else //Se o retorno nao for 1 entao os dados foram apagados corretamente
//     //                     {
//     //                         printf("Curso removido do sistema!\n");
//     //                         printf("Aperte ENTER para voltar ao menu\n");
//     //                         setbuf(stdin, NULL);
//     //                         getchar();
//     //                     }

//                 break;

//             case 3: // Pesquisar curso
//                 printf("Digite o ID do curso a ser pesquisado:\n");
//                 char *id = getUserInput();

//                 int idCurso = atoi(id);
//                 free(id);

//                 // SUGESTÃO DO ENTER: free(getUserInput());

//     //                     if (pesquisarCurso(infoCurso, auxNome, auxNumero, totalAlunos) == 1)
//     //                     {
//     //                         printf("Curso nao encontrado\n");
//     //                         printf("Aperte ENTER para voltar ao menu\n");
//     //                         setbuf(stdin, NULL);
//     //                         getchar();
//     //                     }

//                 break;

//             case 4: // Alterar curso
//                 printf("Digite o ID do curso a ser alterado:\n");
//                 char *id = getUserInput();
//                 int idCurso = atoi(id);
//                 free(id);

//                 // alterarCurso(infoCurso, auxNome, auxNumero, totalAlunos);

//                 break;

//             case 5: // Listar cursos

//     //          listarCursos(infoCurso, totalAlunos);
//                 break;

//             case 6: // Salvar operacoes
//     //          arqCurso = salvarArqCurso(arqCurso, infoCurso, totalAlunos);
//                 break;

//             case 7: // Voltar ao menu inicial
//                 return;
//         }

//     }
// }
