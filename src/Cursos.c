#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <Cursos.h>
#include <utils.h>
#include <unistd.h>

#define MAX 10
#define CURSO_CSV "./dataCurso"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"
#define BLU "\x1B[34m"

/**
 * @brief Abre o arquivo que estao salvos as informacoes dos cursos
 *
 * @param nome
 * @param cursos
 * @return FILE*
 */
FILE *abrirArqCurso(char *nome)
{
    FILE *arq = fopen(nome, "r+b");
    if (arq == NULL)
    {
        //se o arquivo nao existe ele cria um novo
        printf(YEL"Arquivo nao esta no sistema!\nCriando arquivo...\n");
        arq = fopen(nome, "w+b");
        if (arq == NULL)
        {
            printf(RED"Erro ao abrir arquivo!!!\n");
            // exit(1);
            return NULL;
        }
    }
    printf(GRN"Arquivo aberto\n");

    return arq;
}

/**
 * @brief Le o arquivo de cursos e armazena os dados em um vetor de cursos
 *
 * @param arquivo
 * @param total
 * @return Curso*
 */
Curso *getCursos(FILE *arquivo, int *total) {
    Curso *cursos = NULL;
    int cont = 0;
    int tmp;
    while (!feof(arquivo)) { // enquanto não chegar no fim do arquivo
        if (cont % 10 == 0) { // se o contador for divisivel por 10 realoca o vetor
            cursos = (Curso*) realloc(cursos, (cont + 10) * sizeof(Curso));
        }
        tmp = fread(&cursos[cont], sizeof(Curso), 1, arquivo); // le o arquivo e armazena os dados em um vetor de cursos
        if (tmp == 0) { // Diminui o contador pois nao há mais cursos no arquivo, isso ocorre por feof pega uma linha a mais do arquivo entao total de cursos no arquivo viria com um a mais o que daria problemas na exibicao e insercao de novos
            cont--;
        }
        cont++;
    }
    for (int i = cont; i <= cont + MAX; i++) { // Indica que as posições estão vazias
        cursos[i].idCurso = 0;
    }
    *total = cont;
    fclose(arquivo);
    return cursos;
}

/**
 * @brief If() -- verifica se os dados do Curso foram inseridos corretamente
 *
 * @param cursos
 * @param indice
 * @return int
 */
int verificarCurso(Curso cursos[], int indice)
{
    if (strcasecmp(cursos[indice].nome, "\0") == 0 || cursos[indice].duracao <= 0 || strcasecmp(cursos[indice].periodo, "\0") == 0)//If() -- verifica se os dados do Curso foram inseridos corretamente
    {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Funcao para inserir as informacoes do Curso
 *
 * @param cursos
 * @param quantidade
 * @param total
 * @return Curso*
 */
Curso *inserirCurso(Curso *cursos, int *total)
{
    int indice = 0; //indice
    char *confirma = NULL; //confirmacao
    //Verifica se tem um espaço disponível (id = 0)
    int valorOpcao = 0;
    while (valorOpcao != 2) //Enquanto não for escolhido a opção de sair
    {
        for (int i = 1; i <= *total; i++) { //Verifica se tem um espaço disponível (id = 0)
            if (cursos[i].idCurso == 0) {
                indice = i;
                break;
            }
        }
        if (indice == *total + MAX) //Se não houver espaço disponível realoca o vetor
        {
            printf(RED"Nao ha espaco disponivel...\nRealocando...\n");
            int realocador = MAX;
            realocador += 10;
            cursos = (Curso*) realloc(cursos, realocador * sizeof(Curso)); //realoca cursos para preencher mais
            if (cursos == NULL)
            {
                printf(RED"Erro: memoria insuficiente\n");
                return NULL;//return -1;
            }
        }

        do {
            cursos[indice].idCurso = indice + 1;
            printf(CYN"\nCurso %i\n", indice + 1);
            setbuf(stdin, NULL);
            printf("Nome: ");
            fgets(cursos[indice].nome, 50, stdin);
            cursos[indice].nome[strcspn(cursos[indice].nome, "\n")] = '\0';
            printf("Duracao (semestres): ");
            scanf("%d", &cursos[indice].duracao);
            printf("Periodo: ");
            setbuf(stdin, NULL);
            fgets(cursos[indice].periodo, 10, stdin);
            cursos[indice].periodo[strcspn(cursos[indice].periodo, "\n")] = '\0';
            if (verificarCurso(cursos, indice) == 1) { //verifica se os dados foram preenchidos corretamente
                printf(RED"Erro!!! Preencha novamente\n");
            }
            else {
                printf(GRN"Curso cadastrado no sistema!\n");
                (*total)++;

                printf(GRN"ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", cursos[indice].idCurso, cursos[indice].nome, cursos[indice].duracao, cursos[indice].periodo); //Mostra as informacoes atuais do Curso

                printf(CYN"Deseja cadastrar outro Curso? (1 - S/ 2 - N): "); //Pergunta se deseja cadastrar outro Curso

                confirma = getUserInput();
                char valorOpcao = atoi(confirma);
                free(confirma);

                if (valorOpcao == 2)
                {
                    //fclose(arq);
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());// Apos inserido todos os cursos desejados basta apertaar ENTER para voltar ao menu
                    system("clear");
                    return cursos;
                } else if (valorOpcao != 1)
                {
                    printf(RED"Erro!!!\nDigite novamente\n");
                    printf(CYN"Deseja cadastrar outro Curso? (1 - S/ 2 - N): ");
                    confirma = getUserInput();
                    printf("%s\n", confirma);
                    valorOpcao = atoi(confirma);
                    free(confirma);
                }
            }
        } while (verificarCurso(cursos, indice) == 1);//do while() -- caso uma das informações inseridas estiver com algum erro o usuario devera inserir novamente
    }
    return cursos;
}

/**
 * @brief Limpa os dados do Curso que o usuario deseja excluir, deixando assim uma posicao livre no sistema (ainda é contado como total de cursos no sistema)
 *
 * @param cursos
 * @param indice
 * @return Curso
 */
Curso limparcursos(Curso cursos[], int indice)
{
    strcpy(cursos[indice].nome, "\0");
    cursos[indice].duracao = 0;
    cursos[indice].idCurso = 0;
    strcpy(cursos[indice].periodo, "\0");
    return cursos[indice];
}

/**
 * @brief Funcao que recebe o id/nome do Curso que o usuario deseja remover, faz a busca pelo mesmo e retorna 1 caso nao seja encontrado e 0 caso encontre
 *
 * @param cursos
 * @param nome
 * @param id
 * @param total
 * @return int
 */
int removerCurso(Curso cursos[], char nome[], int id, int total)
{
    char *confirmacao;
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(cursos[i].nome, nome) == 0 || cursos[i].idCurso == id)//Busca o Curso desejado
        {
            printf(YEL"As seguintes informacoes do Curso serao apagadas do registro:\n");
            printf(YEL"ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", cursos[i].idCurso, cursos[i].nome, cursos[i].duracao, cursos[i].periodo);
            printf(CYN"Deseja continuar ? 1 - Sim / 2 - Nao\n");
            setbuf(stdin, NULL);
            confirmacao = getUserInput();
            char valorOpcao = atoi(confirmacao);
            free(confirmacao);//Confirmacao para excluir
            if (valorOpcao == 2) {
                return 3;
            }
            else if (valorOpcao != 1) {
                printf(RED"Erro!!!\nDigite novamente\n");
                printf(CYN"Deseja continuar ? 1 - Sim / 2 - Nao\n");
                confirmacao = getUserInput();
                valorOpcao = atoi(confirmacao);
                free(confirmacao);
            }
            else {
                limparcursos(cursos, i);
                return 0;
            }
        }
    }
    return 1;
}

/**
 * @brief Pesquisar Curso desejado no sistema, se achar retorna 0 se nao retorna 1
 *
 * @param cursos
 * @param nome
 * @param id
 * @param total
 * @return int
 */
int pesquisarCurso(Curso *cursos, char *nome, int id, int total)
{
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(cursos[i].nome, nome) == 0 || cursos[i].idCurso == id)
        {
            printf(GRN"ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n"CYN, cursos[i].idCurso, cursos[i].nome, cursos[i].duracao, cursos[i].periodo);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Funcao para realizar a alteracao das informacoes do Curso desejado
 *
 * @param cursos
 * @param nome
 * @param id
 * @param total
 */
void alterarCurso(Curso cursos[], char nome[], int id, int total)
{
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(cursos[i].nome, nome) == 0 || cursos[i].idCurso == id)
        {
            do
            {
                printf(YEL"ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", cursos[i].idCurso, cursos[i].nome, cursos[i].duracao, cursos[i].periodo);//Mostra as informacoes atuais do Curso
                printf(CYN"Qual informacao deseja alterar do registro do Curso ?\n1 - Nome\n2 - Duracao\n3 - Periodo\n4 - Cancelar\n");//Opcoes de alteracao (ID nao pode ser alterado)

                char *opcao = getUserInput();

                if (strlen(opcao) != 1 || atoi(opcao) < 1 || atoi(opcao) > 7) {
                    printf(YEL"Opção inválida! Digite novamente:\n");
                    free(opcao);
                    continue;
                }
                char valorOpcao = atoi(opcao);
                free(opcao);

                switch (valorOpcao)
                {
                case 1:
                    printf(CYN"Nome: ");
                    setbuf(stdin, NULL);
                    fgets(cursos[i].nome, 50, stdin);
                    cursos[i].nome[strcspn(cursos[i].nome, "\n")] = '\0';
                    break;
                case 2:
                    printf("Duracao: ");
                    scanf("%d", &cursos[i].duracao);
                    break;
                case 3:
                    printf("Periodo: ");
                    setbuf(stdin, NULL);
                    fgets(cursos[i].periodo, 30, stdin);
                    cursos[i].periodo[strcspn(cursos[i].periodo, "\n")] = '\0';
                    break;
                case 4:
                    return;
                    break;
                default:
                    printf(YEL"Opcao invalida! Digite novamente\n");
                    break;
                }
                if (verificarCurso(cursos, i) == 1)//If() -- verifica se os dados do Curso foram alterados corretamente
                {
                    printf(RED"Erro!!! Preencha novamente\n");
                } else
                {
                    printf(GRN"Curso alterado no sistema!\n");
                }
            } while (verificarCurso(cursos, i) == 1);//Verificacao de preenchimento das informacoes
        }
    }
}

/**
 * @brief Lista cursos cadastrados no sistema
 *
 * @param cursos
 * @param total
 */
void listarCursos(Curso cursos[], int total)
{
    for (int i = 0; i < total; i++)
    {
        if (cursos[i].idCurso != 0)
        {
            printf("---------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf(CYN"ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", cursos[i].idCurso, cursos[i].nome, cursos[i].duracao, cursos[i].periodo);
        }

    }
    printf("Total de cursos registrados no sistema: %d\n", total);
    printf("Aperte ENTER para voltar ao menu\n");
    free(getUserInput());
    system("clear");
}

/**
 * @brief Salva as informacoes da memoria no arquivo
 *
 * @param arq
 * @param cursos
 * @param total
 * @return FILE*
 */
FILE *salvarArqCurso(FILE *arq, Curso *cursos, int *total)
{
    int aux;
    char nome[31] = {"./dataCurso.dat"};
    arq = fopen(nome, "r+b");

    printf(YEL"Salvando os dados...\nNao feche o programa!\n");
    usleep(200000);
    for (int i = 0; i < *total; i++)
    {
        fwrite(&cursos[i], sizeof(Curso), 1, arq); //Escreve os dados no arquivo
    }
    aux = ftell(arq);
    if (aux == 0)//Verifica se os dados foram salvos corretamente, se o arquivo estiver vazio eles nao foram salvos
    {
        printf(RED"Erro ao salvar! Tente novamente\n");
    } else
    {
        printf(GRN"Dados salvos com sucesso!\n");
        printf(CYN"Aperte ENTER para voltar ao menu\n");
        free(getUserInput());
        system("clear");
    }

    return arq;
}

/**
 * @brief Exporta os dados de cursos para um arquivo .csv
 *
 * @param cursos
 * @param total
 */
void exportarCursos(Curso *cursos, int total) {
    printf(YEL"Exportando dados dos cursos...\n");
    printf("Aguarde...\n");
    usleep(200000);
    char cursos_csv[50];
    sprintf(cursos_csv, "%s.csv", CURSO_CSV); //Formatar as informações
    FILE *arq_csv = fopen(cursos_csv, "w+");
    if (arq_csv == NULL) {
        printf(RED"Erro ao abrir o arquivo!\n");
        return;
    }
    fputs("ID, Nome, periodo, duracao\n", arq_csv); //Cabeçalho do arquivo csv
    for (int i = 0; i < total; i++)
    {
        fprintf(arq_csv, "%d, %s, %s, %d\n", cursos[i].idCurso, cursos[i].nome, cursos[i].periodo, cursos[i].duracao);
    }
    printf(GRN"Dados exportados com sucesso!\n");
    printf(CYN"Aperte ENTER para voltar ao menu\n");
    free(getUserInput());
    system("clear");
    fclose(arq_csv);
}