#include <userInterface.h>

#include <utils.h>
#include <string.h>

void alunoOptions();

char *getUserInput() {
    char *input = lerString(stdin, '\n');

    return input;
}

void userInterface() {
    printf("Bem Vindo ao sistema\nOperacoes:\n- Digite o numero da base de dados que deseja acessar:\n1 - Alunos\n2 - Cursos\n3 - Matriculas\n4 - Salvar operacoes\n5 - Sair do sistema\n");
    printf("Digite sua opção:\n");

    char *opcao = NULL;

    while (true) {
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
                alunoOptions();
                break;
        
            case 2: // Cursos
                cursosOptions();
                break;

            case 3: // Matriculas
                
                break;
            
            case 4: // Salvar
    //         arqAluno = salvarArqAluno(arqAluno, infoAluno, quantidadeTotal);
    //         arqCurso = salvarArqCurso(arqCurso, infoCurso, quantidadeTotal);
                break;

            case 5: // Sair
                return;
            
        }

    }
}

void alunoOptions() {

    // CRIAR ALUNO

    printf("\nRegistro de Alunos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir aluno\n2 - Remover aluno\n3 - Pesquisar\n4 - Alterar aluno\n5 - Listar alunos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");

    while (true) {
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
                printf("Digite a quantidade de alunos que deseja inserir:\n");
                char *quantidade = getUserInput();
                int qtd = atoi(quantidade);
                free(quantidade);

                // INSERIR O ALUNO
                // infoAluno = inserirAluno(infoAluno, quantidade, quantidadeTotal);

                break;
        
            case 2: // Remover aluno
                printf("Digite o ID do aluno a ser removido:\n");
                char *id = getUserInput();

                int idAluno = atoi(id);
                free(id);


    //          if (removerAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1) {
    //                  printf("Aluno nao encontrado\n");
    //                  printf("Aperte ENTER para voltar ao menu\n");
    //                  setbuf(stdin, NULL);
    //                         getchar();
    //                     } else {
    //                         printf("Aluno removido do sistema!\n");
    //                         printf("Aperte ENTER para voltar ao menu\n");
    //                         setbuf(stdin, NULL);
    //                         getchar();
    //                     }


                break;

            case 3: // Pesquisar
                printf("Digite o ID do aluno a ser pesquisado:\n");
                char *id = getUserInput();

                int idAluno = atoi(id);
                free(id);

                // SUGESTÃO DO ENTER: free(getUserInput());

    //                     if (pesquisarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal) == 1)
    //                     {
    //                         printf("Aluno nao encontrado\n");
    //                         printf("Aperte ENTER para voltar ao menu\n");
    //                         setbuf(stdin, NULL);
    //                         getchar();
    //                     }

                break;
            
            case 4: // Alterar aluno
                printf("Digite o ID do aluno a ser alterado:\n");
                char *id = getUserInput();

                int idAluno = atoi(id);
                free(id);

                // alterarAluno(infoAluno, auxNome, auxNumero, quantidadeTotal);
                
                break;

            case 5: // Listar alunos

                // listarAlunos(infoAluno, quantidadeTotal);
                break;

            case 6: // Salvar operacoes

                // arqAluno = salvarArqAluno(arqAluno, infoAluno, quantidadeTotal);
                break;

            case 7: // Voltar ao menu inicial
                return;
            
        }



    }
}

void cursosOptions() {
    printf("\nRegistro de Cursos\n- Qual operacao deseja realizar dentro do sistema ?\n1 - Inserir curso\n2 - Remover curso\n3 - Pesquisar curso\n4 - Alterar curso\n5 - Listar cursos\n6 - Salvar operacoes\n7 - Voltar ao menu inicial\n");

    while (true) {
        char *opcao = getUserInput();

        if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 7) {
            printf("Opção inválida! Digite novamente:\n");
            free(opcao);
            continue;
        }

        char valorOpcao = atoi(opcao);
        free(opcao);

        switch (valorOpcao) {
            case 1: // Inserir curso
                printf("Digite a quantidade de cursos que deseja inserir:\n");
                char *quantidade = getUserInput();
                int qtd = atoi(quantidade);
                free(quantidade);

                // INSERIR O CURSO
                // infoCurso = inserirCurso(infoCurso, quantidade, quantidadeTotal);

                break;
        
            case 2: // Remover curso
                printf("Digite o ID do curso a ser removido:\n");

                char *id = getUserInput();
                int idCurso = atoi(id);
                free(id);

    //                     if (removerCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
    //                     {
    //                         printf("Curso nao encontrado\n");
    //                         printf("Aperte ENTER para voltar ao menu\n");
    //                         setbuf(stdin, NULL);
    //                         getchar();
    //                     } else //Se o retorno nao for 1 entao os dados foram apagados corretamente
    //                     {
    //                         printf("Curso removido do sistema!\n");
    //                         printf("Aperte ENTER para voltar ao menu\n");
    //                         setbuf(stdin, NULL);
    //                         getchar();
    //                     }

                break;

            case 3: // Pesquisar curso
                printf("Digite o ID do curso a ser pesquisado:\n");
                char *id = getUserInput();

                int idCurso = atoi(id);
                free(id);

                // SUGESTÃO DO ENTER: free(getUserInput());

    //                     if (pesquisarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal) == 1)
    //                     {
    //                         printf("Curso nao encontrado\n");
    //                         printf("Aperte ENTER para voltar ao menu\n");
    //                         setbuf(stdin, NULL);
    //                         getchar();
    //                     }

                break;

            case 4: // Alterar curso
                printf("Digite o ID do curso a ser alterado:\n");
                char *id = getUserInput();
                int idCurso = atoi(id);
                free(id);

                // alterarCurso(infoCurso, auxNome, auxNumero, quantidadeTotal);

                break;

            case 5: // Listar cursos

    //          listarCursos(infoCurso, quantidadeTotal);
                break;

            case 6: // Salvar operacoes
    //          arqCurso = salvarArqCurso(arqCurso, infoCurso, quantidadeTotal);
                break;

            case 7: // Voltar ao menu inicial
                return;
        }

    }
}
