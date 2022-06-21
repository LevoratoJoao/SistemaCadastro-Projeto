#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include <Alunos.h>
#include <Matriculas.h>
#include <Cursos.h>
#include <utils.h>

#define MATRICULA_CSV "./dataMatricula.csv"
#define MAXIMO 10
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"
#define BLU "\x1B[34m"

FILE *abrirArqMatricula(char *nome)
{
    FILE *arq = fopen(nome, "r+b");
    if (arq == NULL)
    {
        //se o arquivo nao existe ele cria um novo
        printf("Arquivo nao esta no sistema!\nCriando arquivo...\n");
        arq = fopen(nome, "w+b");
        if (arq == NULL)
        {
            printf("Erro ao abrir arquivo!!!\n");
            // exit(1);
            return NULL;
        }
    }

    return arq;
}

Matricula *getMatricula(FILE *arquivo, int *total) {
    Matricula *matriculas = NULL;
    int cont = 0;
    int tmp;
    while (!feof(arquivo)) { // enquanto não chegar no fim do arquivo
        if (cont % 10 == 0) { // se o contador for divisivel por 10 realoca o vetor
            matriculas = (Matricula*) realloc(matriculas, (cont + 10) * sizeof(Matricula));
        }
        tmp = fread(&matriculas[cont], sizeof(Matricula), 1, arquivo); // le o arquivo e armazena os dados em um vetor de cursos
        if (tmp == 0) { // Diminui o contador pois nao há mais cursos no arquivo, isso ocorre por feof pega uma linha a mais do arquivo entao total de cursos no arquivo viria com um a mais o que daria problemas na exibicao e insercao de novos
            cont--;
        }
        cont++;
    }
    for (int i = cont; i <= cont + MAXIMO; i++) { // Indica que as posições estão vazias
        matriculas[i].idMatricula = 0;
    }
    *total = cont;
    fclose(arquivo);
    return matriculas;
}

int verificarMatricula(Matricula *matriculas, int indice)
{
    if (matriculas[indice].anoMatricula <= 0 || matriculas[indice].coeficiente < 0 || matriculas[indice].semestre < 0 || matriculas[indice].aluno.idAluno < 0 || matriculas[indice].curso.idCurso < 0)//If() -- verifica se os dados do Curso foram inseridos corretamente
    {
        return 1;
    } else {
        return 0;
    }
}

Matricula *inserirMatricula(Matricula *matriculas, Aluno *alunos, Curso *cursos, int *totalMatriculas, int *totalAlunos, int *totalCursos)
{
    int indice = 0; //indice
    char *confirma = NULL; //confirmacao
    //Verifica se tem um espaço disponível (id = 0)
    int valorOpcao = 0;
    int naoTem = 0;
    while (valorOpcao != 2) //Enquanto não for escolhido a opção de sair
    {
        for (int i = 1; i <= *totalMatriculas; i++) { //Verifica se tem um espaço disponível (id = 0)
            if (matriculas[i].idMatricula == 0) {
                indice = i;
                break;
            }
        }
        if (indice == *totalMatriculas + MAXIMO) //Se não houver espaço disponível realoca o vetor
        {
            printf("Nao ha espaco disponivel...\nRealocando...\n");
            int realocador = MAXIMO;
            realocador += 10;
            matriculas = (Matricula*) realloc(matriculas, realocador * sizeof(Matricula)); //realoca cursos para preencher mais
            if (matriculas == NULL)
            {
                printf("Erro: memoria insuficiente\n");
                return NULL;//return -1;
            }
        }

        do {
            matriculas[indice].idMatricula = indice + 1;
            printf("\nMatricula %i\n", indice + 1);
            printf("ID do aluno: ");
            scanf("%d", &matriculas[indice].aluno.idAluno);
            for (int i = 0; i < *totalAlunos; i++)
            {
                if (matriculas[indice].aluno.idAluno == alunos[i].idAluno)
                {
                    matriculas[indice].aluno = alunos[i];
                    printf("Informacoes do aluno: \n");
                    printf("ID: %i\n", matriculas[indice].aluno.idAluno);
                    printf("Nome: %s\n", matriculas[indice].aluno.nome);
                    printf("Idade: %i\n", matriculas[indice].aluno.idade);
                    printf("Cidade: %s\n", matriculas[indice].aluno.cidade);
                    printf("Data de nascimento: %d/%d/%d\n", matriculas[indice].aluno.nascimento.dia, matriculas[indice].aluno.nascimento.mes, matriculas[indice].aluno.nascimento.ano);
                    naoTem = 0;
                    break;
                } else {
                    naoTem = 1;
                }
            }
            if (naoTem == 1)
            {
                printf(YEL"O ID do aluno inserido nao se encontra na base de dados do sistema!\n");
                matriculas[indice].aluno.idAluno = 0;
            }
            printf("ID do curso: ");
            scanf("%d", &matriculas[indice].curso.idCurso);
            for (int i = 0; i < *totalCursos; i++)
            {
                if (matriculas[indice].curso.idCurso == cursos[i].idCurso)
                {
                    matriculas[indice].curso = cursos[i];
                    printf("Informacoes do curso: \n");
                    printf("ID: %i\n", matriculas[indice].curso.idCurso);
                    printf("Nome: %s\n", matriculas[indice].curso.nome);
                    printf("Periodo: %s\n", matriculas[indice].curso.periodo);
                    printf("Duracao (semestres): %d\n", matriculas[indice].curso.duracao);
                    naoTem = 0;
                } else {
                    naoTem = 1;
                }
            }
            if (naoTem == 1)
            {
                printf(YEL"O ID do curso inserido nao se encontra na base de dados do sistema!\n");
                matriculas[indice].curso.idCurso = 0;
            }
            printf("Ano de matricula: ");
            scanf("%d", &matriculas[indice].anoMatricula);
            printf("Coeficiente: ");
            scanf("%f", &matriculas[indice].coeficiente);
            printf("Semestre que esta: ");
            scanf("%d", &matriculas[indice].semestre);

            if (verificarMatricula(matriculas, indice) == 1) { //verifica se os dados foram preenchidos corretamente
                printf(RED"Erro!!! Preencha novamente\n");
            }
            else {
                printf("Matricula cadastrada no sistema!\n");
                (*totalMatriculas)++;

                printf("ID da matricula: %d | ID do aluno: %d | Nome: %10s | Idade: %d | Cidade: %10s | Data de nascimento: %d/%d/%d | ID do curso: %d | Curso: %10s | Periodo: %10s | Duracao: %d | Ano de matricula: %d | Coeficiente: %.2f | Semmestre: %d\n", matriculas[indice].idMatricula, matriculas[indice].aluno.idAluno, matriculas[indice].aluno.nome, matriculas[indice].aluno.idade, matriculas[indice].aluno.cidade, matriculas[indice].aluno.nascimento.dia, matriculas[indice].aluno.nascimento.mes, matriculas[indice].aluno.nascimento.ano, matriculas[indice].curso.idCurso, matriculas[indice].curso.nome, matriculas[indice].curso.periodo, matriculas[indice].curso.duracao, matriculas[indice].anoMatricula, matriculas[indice].coeficiente, matriculas[indice].semestre); //Mostra as informacoes atuais do Curso

                printf("Deseja cadastrar outra matricula? (1 - S/ 2 - N): "); //Pergunta se deseja cadastrar outro Curso
                setbuf(stdin, NULL);
                confirma = getUserInput();
                if (strlen(confirma) != 1 || atoi(confirma) < 1 || atoi(confirma) > 2) {
                    printf("Opção inválida! Digite novamente:\n");
                    free(confirma);
                    continue;
                }
                int valorOpcao = atoi(confirma);
                free(confirma);

                if (valorOpcao == 2) {
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());// Apos inserido todos os cursos desejados basta apertaar ENTER para voltar ao menu
                    return matriculas;
                } else {
                    continue;
                }
            }
        } while (verificarMatricula(matriculas, indice) == 1);//do while() -- caso uma das informações inseridas estiver com algum erro o usuario devera inserir novamente
    }
    return matriculas;
}

Matricula limparMatricula(Matricula matriculas[], int indice)
{
    matriculas[indice].idMatricula = 0;
    matriculas[indice].aluno.idAluno = 0;
    strcpy(matriculas[indice].aluno.nome, "\0");
    matriculas[indice].aluno.idade = 0;
    strcpy(matriculas[indice].aluno.cidade, "\0");
    matriculas[indice].aluno.nascimento.dia = 0;
    matriculas[indice].aluno.nascimento.mes = 0;
    matriculas[indice].aluno.nascimento.ano = 0;
    matriculas[indice].curso.idCurso = 0;
    strcpy(matriculas[indice].curso.nome, "\0");
    strcpy(matriculas[indice].curso.periodo, "\0");
    matriculas[indice].curso.duracao = 0;
    matriculas[indice].anoMatricula = 0;
    matriculas[indice].coeficiente = 0;
    matriculas[indice].semestre = 0;

    return matriculas[indice];
}

int removerMatricula(Matricula *matriculas, int id, int *total)
{
    char *confirmacao;
    int valorOpcao = 3;
    for (int i = 0; i < *total; i++)
    {
        if (matriculas[i].idMatricula == id)//Busca a matricula desejada
        {
            printf("As seguintes informacoes da matricula serao apagadas do registro:\n");
            printf("ID da matricula: %d | ID: do aluno: %d | Nome: %10s | Idade: %d | Cidade: %10s | Data de nascimento: %d/%d/%d | ID do curso: %d | Curso: %10s | Periodo: %10s | Duracao: %d | Ano de matricula: %d | Coeficiente: %.2f | Semestre: %d\n", matriculas[i].idMatricula, matriculas[i].aluno.idAluno, matriculas[i].aluno.nome, matriculas[i].aluno.idade, matriculas[i].aluno.cidade, matriculas[i].aluno.nascimento.dia, matriculas[i].aluno.nascimento.mes, matriculas[i].aluno.nascimento.ano, matriculas[i].curso.idCurso, matriculas[i].curso.nome, matriculas[i].curso.periodo, matriculas[i].curso.duracao, matriculas[i].anoMatricula, matriculas[i].coeficiente, matriculas[i].semestre);
            printf("Deseja continuar ? 1 - Sim / 2 - Nao\n");
            setbuf(stdin, NULL);
            confirmacao = getUserInput();
            if (strlen(confirmacao) != 1 || atoi(confirmacao) < 1 || atoi(confirmacao) > 2) {
                printf("Opção inválida! Digite novamente:\n");
                free(confirmacao);
                continue;
            }
            valorOpcao = atoi(confirmacao);
            free(confirmacao);//Confirmacao para excluir

            if (valorOpcao == 1) {

                limparMatricula(matriculas, i);
                (*total)--;
                return 0;
            } else {
                return 3;
            }
        }
    }
    return 1;
}

int pesquisarMatricula(Matricula *matriculas, int id, int total)
{
    for (int i = 0; i < total; i++)
    {
        if (matriculas[i].idMatricula == id)
        {
            printf("ID da matricula: %d | ID: do aluno: %d | Nome: %10s | Idade: %d | Cidade: %10s | Data de nascimento: %d/%d/%d | ID do curso: %d | Curso: %10s | Periodo: %10s | Duracao: %d | Ano de matricula: %d | Coeficiente: %.2f | Semestre: %d\n", matriculas[i].idMatricula, matriculas[i].aluno.idAluno, matriculas[i].aluno.nome, matriculas[i].aluno.idade, matriculas[i].aluno.cidade, matriculas[i].aluno.nascimento.dia, matriculas[i].aluno.nascimento.mes, matriculas[i].aluno.nascimento.ano, matriculas[i].curso.idCurso, matriculas[i].curso.nome, matriculas[i].curso.periodo, matriculas[i].curso.duracao, matriculas[i].anoMatricula, matriculas[i].coeficiente, matriculas[i].semestre);
            return 0;
        }
    }
    return 1;
}

void alterarMatricula(Matricula *matriculas, int id, int total, Aluno *alunos, Curso *cursos, int *totalAlunos, int *totalCursos)
{
    for (int i = 0; i < total; i++)
    {
        if (matriculas[i].idMatricula == id)
        {
            do
            {
                printf("ID da matricula: %d | ID: do aluno: %d | Nome: %10s | Idade: %d | Cidade: %10s | Data de nascimento: %d/%d/%d | ID do curso: %d | Curso: %10s | Periodo: %10s | Duracao: %d | Ano de matricula: %d | Coeficiente: %.2f | Semestre: %d\n", matriculas[i].idMatricula, matriculas[i].aluno.idAluno, matriculas[i].aluno.nome, matriculas[i].aluno.idade, matriculas[i].aluno.cidade, matriculas[i].aluno.nascimento.dia, matriculas[i].aluno.nascimento.mes, matriculas[i].aluno.nascimento.ano, matriculas[i].curso.idCurso, matriculas[i].curso.nome, matriculas[i].curso.periodo, matriculas[i].curso.duracao, matriculas[i].anoMatricula, matriculas[i].coeficiente, matriculas[i].semestre);
                printf("Qual informacao deseja alterar do registro da matricula ?\n1 - Informacoes do aluno\n  - As alteracoes serao feitas pelo ID do aluno, ira substituir todas as informacoes do aluno dessa matricula pela do aluno do ID inserido\n2 - Informacoes do curso\n  - As alteracoes serao feitas pelo ID do curso, ira substituir todas as informacoes do curso dessa matricula pela do curso do ID inserido\n3 - Ano da matricula\n3 - Coeficiente\n5 - Semestre\n6 - Cancelar\n");//Opcoes de alteracao (ID nao pode ser alterado)


                char *opcao = getUserInput();

                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 6) {
                    printf("Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                char valorOpcao = atoi(opcao);
                free(opcao);

                switch (valorOpcao)
                {
                case 1:
                    printf("Digite o ID do aluno: ");
                    scanf("%d", &matriculas[i].aluno.idAluno);
                    for (int i = 0; i < *totalAlunos; i++)
                    {
                        if (alunos[i].idAluno == matriculas[i].aluno.idAluno)
                        {
                            matriculas[i].aluno = alunos[i];
                        }
                    }
                    break;

                case 2:
                    printf("Digite o ID do curso: ");
                    scanf("%d", &matriculas[i].curso.idCurso);
                    for (int i = 0; i < *totalCursos; i++)
                    {
                        if (cursos[i].idCurso == matriculas[i].curso.idCurso)
                        {
                            matriculas[i].curso = cursos[i];
                        }
                    }
                    break;
                case 3:
                    printf("Ano da matricula: ");
                    scanf("%d", &matriculas[i].anoMatricula);
                    break;
                case 4:
                    printf("Digite o novo coeficiente: ");
                    scanf("%f", &matriculas[i].coeficiente);
                    break;
                case 5:
                    printf("Digite o novo semestre: ");
                    scanf("%d", &matriculas[i].semestre);
                    break;
                case 6:
                    return;
                    break;
                default:
                    printf("Opcao invalida! Digite novamente\n");
                    break;
                }
                if (verificarMatricula(matriculas, i) == 1)//If() -- verifica se os dados da matricula foram alterados corretamente
                {
                    printf("Erro!!! Preencha novamente\n");
                } else
                {
                    printf("Matricula alterada no sistema!\n");
                }
            } while (verificarMatricula(matriculas, i) == 1);//Verificacao de preenchimento das informacoes
        }
    }
}

void listarMatriculas(Matricula matriculas[], int total)
{
    for (int i = 0; i < total; i++)
    {
        if (matriculas[i].idMatricula != 0)
        {
            printf("ID da matricula: %d | ID: do aluno: %d | Nome: %10s | Idade: %d | Cidade: %10s | Data de nascimento: %d/%d/%d | ID do curso: %d | Curso: %10s | Periodo: %10s | Duracao: %d | Ano de matricula: %d | Coeficiente: %.2f | Semmestre: %d\n", matriculas[i].idMatricula, matriculas[i].aluno.idAluno, matriculas[i].aluno.nome, matriculas[i].aluno.idade, matriculas[i].aluno.cidade, matriculas[i].aluno.nascimento.dia, matriculas[i].aluno.nascimento.mes, matriculas[i].aluno.nascimento.ano, matriculas[i].curso.idCurso, matriculas[i].curso.nome, matriculas[i].curso.periodo, matriculas[i].curso.duracao, matriculas[i].anoMatricula, matriculas[i].coeficiente, matriculas[i].semestre);
        }
    }
    printf("Total de matriculas registradas no sistema: %d\n", total);
    printf("Aperte ENTER para voltar ao menu\n");
    free(getUserInput());
}

FILE *salvarArqMatricula(FILE *arq, Matricula *matriculas, int *total)
{
    int aux;
    char nome[31] = {"./dataMatricula.dat"};
    arq = fopen(nome, "r+b");

    printf("Salvando os dados...\nNao feche o programa!\n");
    for (int i = 0; i < *total; i++)
    {
        fwrite(&matriculas[i], sizeof(Matricula), 1, arq);
    }
    aux = ftell(arq);
    if (aux == 0)//Verifica se os dados foram salvos corretamente, se o arquivo estiver vazio eles nao foram salvos
    {
        printf("Erro ao salvar! Tente novamente\n");
    } else
    {
        printf("Dados salvos com sucesso!\n");
    }

    return arq;
}

void exportarMatriculas(Matricula *matriculas, int total) {
    printf(YEL"Exportando dados das matriculas...\n");
    printf("Aguarde...\n");
    usleep(100000);
    char matriculas_csv[201];
    sprintf(matriculas_csv, "%s.csv", MATRICULA_CSV);
    FILE *arq_csv = fopen(matriculas_csv, "w+");
    if (arq_csv == NULL)
    {
        printf(RED"Erro ao abrir o arquivo!\n");
        return;
    }
    fprintf(arq_csv, "ID da matricula, ID do aluno, Nome do aluno, Idade do aluno, Cidade do aluno, Data de nascimento, ID do curso, Nome do curso, Periodo do curso, Duracao do curso, Ano de matricula, Coeficiente, Semestre\n");
    for (int i = 0; i < total; i++)
    {
        fprintf(arq_csv, "%d, %d, %s, %d, %s, %d/%d/%d, %d, %s, %s, %d, %d, %.2f, %d\n", matriculas[i].idMatricula, matriculas[i].aluno.idAluno, matriculas[i].aluno.nome, matriculas[i].aluno.idade, matriculas[i].aluno.cidade, matriculas[i].aluno.nascimento.dia, matriculas[i].aluno.nascimento.mes, matriculas[i].aluno.nascimento.ano, matriculas[i].curso.idCurso, matriculas[i].curso.nome, matriculas[i].curso.periodo, matriculas[i].curso.duracao, matriculas[i].anoMatricula, matriculas[i].coeficiente, matriculas[i].semestre);
    }
    printf(GRN"Dados exportados com sucesso!\n");
    printf(CYN"Aperte ENTER para voltar ao menu\n");
    free(getUserInput());
    fclose(arq_csv);
}

