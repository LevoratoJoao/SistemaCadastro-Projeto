#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <Alunos.h>
#include <utils.h>

#define ALUNO_CSV "./dataAluno.csv"

#define MAX 10
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"
#define BLU "\x1B[34m"

/**
 * @brief Abre o arquivo que estao salvos as informacoes dos alunos
 *
 * @param nome
 * @param alunos
 * @return FILE*
 */
FILE *abrirArqAluno(char *nome)
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
 * @brief Le o arquivo de alunos e armazena os dados em um vetor de alunos
 *
 * @param arquivo
 * @param total
 * @return Aluno*
 */
Aluno *getAlunos(FILE *arquivo, int *total) {
    Aluno *alunos = NULL;
    int cont = 0;
    int tmp;
    while (!feof(arquivo)) { // enquanto não chegar no fim do arquivo
        if (cont % 10 == 0) { // se o contador for divisivel por 10 realoca o vetor
            alunos = (Aluno*) realloc(alunos, (cont + 10) * sizeof(Aluno));
        }
        tmp = fread(&alunos[cont], sizeof(Aluno), 1, arquivo); // le o arquivo e armazena os dados em um vetor de alunos
        if (tmp == 0) { // Diminui o contador pois nao há mais alunos no arquivo, isso ocorre por feof pega uma linha a mais do arquivo entao total de alunos no arquivo viria com um a mais o que daria problemas na exibicao e insercao de novos
            cont--;
        }
        cont++;
    }
    for (int i = cont; i <= cont + MAX; i++) { // Indica que as posições estão vazias
        alunos[i].idAluno = 0;
    }
    *total = cont;
    fclose(arquivo);
    return alunos;
}

/**
 * @brief If() -- verifica se os dados do aluno foram inseridos corretamente
 *
 * @param alunos
 * @param indice
 * @return int
 */
int verificarAluno(Aluno alunos[], int indice)
{
    if (strcasecmp(alunos[indice].nome, "\0") == 0 || alunos[indice].idade <= 0 || alunos[indice].nascimento.dia <= 0 || alunos[indice].nascimento.mes <= 0 || alunos[indice].nascimento.ano <= 0 || strcasecmp(alunos[indice].cidade, "\0") == 0)
    {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Funcao para inserir as informacoes do aluno
 *
 * @param alunos
 * @param quantidade
 * @param total
 * @return Aluno*
 */
Aluno *inserirAluno(Aluno *alunos, int *total)
{
    int indice = 0; //indice
    char *confirma = NULL; //confirmacao
    //Verifica se tem um espaço disponível (id = 0)
    int valorOpcao = 0;
    // char nome[31] = {"./dataAluno.dat"};
    // FILE *arq = fopen(nome, "a+b"); //Abre o arquivo para escrita no final dele
    // if (arq == NULL)
    // {
    //     printf("Erro ao abrir arquivo!!!\n");
    //     // exit(1);
    //     return NULL;
    // }
    while (valorOpcao != 2) //Enquanto não for escolhido a opção de sair
    {
        for (int i = 1; i <= *total; i++) { //Verifica se tem um espaço disponível (id = 0)
            if (alunos[i].idAluno == 0) {
                indice = i;
                break;
            }
        }
        if (indice == *total + MAX) //Se não houver espaço disponível realoca o vetor
        {
            printf(RED"Nao ha espaco disponivel...\nRealocando...\n");
            int realocador = MAX;
            realocador += 10;
            alunos = (Aluno*) realloc(alunos, realocador * sizeof(Aluno)); //realoca alunos para preencher mais
            if (alunos == NULL)
            {
                printf(RED"Erro: memoria insuficiente\n");
                return NULL;//return -1;
            }
        }

        do {
            alunos[indice].idAluno = indice + 1;
            printf(CYN"\nAluno %i\n", indice + 1);
            setbuf(stdin, NULL);
            printf("Nome: ");
            fgets(alunos[indice].nome, 50, stdin);
            alunos[indice].nome[strcspn(alunos[indice].nome, "\n")] = '\0';
            printf("Idade: ");
            scanf("%d", &alunos[indice].idade);
            printf("Data de nascimento: dd/mm/aa\n");
            scanf("%d", &alunos[indice].nascimento.dia);
            scanf("%d", &alunos[indice].nascimento.mes);
            scanf("%d", &alunos[indice].nascimento.ano);
            setbuf(stdin, NULL);
            printf("Cidade em que nasceu: ");
            fgets(alunos[indice].cidade, 30, stdin);
            alunos[indice].cidade[strcspn(alunos[indice].cidade, "\n")] = '\0';
            setbuf(stdin, NULL);
            if (verificarAluno(alunos, indice) == 1) { //verifica se os dados foram preenchidos corretamente
                printf(RED"Erro!!! Preencha novamente\n");
            }
            else {
                printf(GRN"Aluno cadastrado no sistema!\n");
                (*total)++;

                printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", alunos[indice].idAluno, alunos[indice].nome, alunos[indice].idade, alunos[indice].nascimento.dia, alunos[indice].nascimento.mes, alunos[indice].nascimento.ano, alunos[indice].cidade);//Mostra as informacoes atuais do aluno

                printf(CYN"Deseja cadastrar outro aluno? (1 - S/ 2 - N): "); //Pergunta se deseja cadastrar outro aluno

                confirma = getUserInput();
                char valorOpcao = atoi(confirma);
                free(confirma);

                if (valorOpcao == 2)
                {
                    //fclose(arq);
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
                    return alunos;
                } else if (valorOpcao != 1)
                {
                    printf(YEL"Erro!!!\nDigite novamente\n");
                    printf(CYN"Deseja cadastrar outro aluno? (1 - S/ 2 - N): ");
                    confirma = getUserInput();
                    printf("%s\n", confirma);
                    valorOpcao = atoi(confirma);
                    free(confirma);
                }
            }
        } while (verificarAluno(alunos, indice) == 1);//do while() -- caso uma das informações inseridas estiver com algum erro o usuario devera inserir novamente
    }
    return alunos;
}

/**
 * @brief Limpa os dados do aluno que o usuario deseja excluir, deixando assim uma posicao livre no sistema
 *
 * @param alunos
 * @param indice
 * @return Aluno
 */
Aluno limparAlunos(Aluno alunos[], int indice)
{
    strcpy(alunos[indice].nome, "\0");
    alunos[indice].idade = 0;
    alunos[indice].idAluno = 0;
    alunos[indice].nascimento.dia = 0;
    alunos[indice].nascimento.mes = 0;
    alunos[indice].nascimento.ano = 0;
    strcpy(alunos[indice].cidade, "\0");
    return alunos[indice];
}

/**
 * @brief Funcao que recebe o id/nome do aluno que o usuario deseja remover, faz a busca pelo mesmo e retorna 1 caso nao seja encontrado e 0 caso encontre
 *
 * @param alunos
 * @param nome
 * @param id
 * @param total
 * @return int
 */
int removerAluno(Aluno alunos[], char nome[], int id, int *total)
{
    char *confirmacao;
    for (int i = 0; i < *total; i++)
    {
        if (strcasecmp(alunos[i].nome, nome) == 0 || alunos[i].idAluno == id)//Busca o aluno desejado
        {
            printf(YEL"As seguintes informacoes do aluno serao apagadas do registro:\n");
            printf(CYN"ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", alunos[i].idAluno, alunos[i].nome, alunos[i].idade, alunos[i].nascimento.dia, alunos[i].nascimento.mes, alunos[i].nascimento.ano, alunos[i].cidade);
            printf("Deseja continuar ? 1 - Sim / 2 - Nao\n");
            setbuf(stdin, NULL);
            confirmacao = getUserInput();
            char valorOpcao = atoi(confirmacao);
            free(confirmacao);//Confirmacao para excluir
            if (valorOpcao == 2) {
                printf(GRN"Operacao finalizada\n");
                printf(CYN"Aperte ENTER para voltar ao menu\n");
                free(getUserInput());
                return 3;

            }
            else if (valorOpcao != 1) {
                printf(YEL"Erro!!!\nDigite novamente\n");
                printf(CYN"Deseja continuar ? 1 - Sim / 2 - Nao\n");
                confirmacao = getUserInput();
                valorOpcao = atoi(confirmacao);
                free(confirmacao);
            }
            else {
                limparAlunos(alunos, i);
                return 0;
            }
        }
    }
    return 1;
}

/**
 * @brief Pesquisar aluno desejado no sistema, se achar retorna 0 se nao retorna 1
 *
 * @param alunos
 * @param nome
 * @param id
 * @param total
 * @return int
 */
int pesquisarAluno(Aluno *alunos, char *nome, int id, int total)
{
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(alunos[i].nome, nome) == 0 || alunos[i].idAluno == id)
        {
            printf(CYN"ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", alunos[i].idAluno, alunos[i].nome, alunos[i].idade, alunos[i].nascimento.dia, alunos[i].nascimento.mes, alunos[i].nascimento.ano, alunos[i].cidade);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Funcao para realizar a alteracao das informacoes do aluno desejado
 *
 * @param alunos
 * @param nome
 * @param id
 * @param total
 */
void alterarAluno(Aluno alunos[], char nome[], int id, int total)
{
    system("clear");
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(alunos[i].nome, nome) == 0 || alunos[i].idAluno == id)
        {
            do
            {
                printf(CYN"ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", alunos[i].idAluno, alunos[i].nome, alunos[i].idade, alunos[i].nascimento.dia, alunos[i].nascimento.mes, alunos[i].nascimento.ano, alunos[i].cidade);//Mostra as informacoes atuais do aluno
                printf("Qual informacao deseja alterar do registro do aluno ?\n1 - Nome\n2 - Idade\n3 - Nascimento\n4 - Cidade\n5 - Cancelar\n");//Opcoes de alteracao (ID nao pode ser alterado)

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
                    fgets(alunos[i].nome, 50, stdin);
                    alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';
                    break;
                case 2:
                    printf("Idade: ");
                    scanf("%d", &alunos[i].idade);
                    break;
                case 3:
                    printf("Data de nascimento: dd/mm/aa\n");
                    scanf("%d", &alunos[i].nascimento.dia);
                    scanf("%d", &alunos[i].nascimento.mes);
                    scanf("%d", &alunos[i].nascimento.ano);
                    break;
                case 4:
                    printf("Cidade em que nasceu: ");
                    setbuf(stdin, NULL);
                    fgets(alunos[i].cidade, 30, stdin);
                    alunos[i].cidade[strcspn(alunos[i].cidade, "\n")] = '\0';
                    break;
                case 5:
                    return;
                    break;
                default:
                    printf(YEL"Opcao invalida! Digite novamente\n");
                    break;
                }
                if (verificarAluno(alunos, i) == 1)//If() -- verifica se os dados do aluno foram alterados corretamente
                {
                    printf(RED"Erro!!! Preencha novamente\n");
                } else
                {
                    printf("Aluno alterado no sistema!\n");
                }
            } while (verificarAluno(alunos, i) == 1);//Verificacao de preenchimento das informacoes
        }
    }
}

/**
 * @brief Lista alunos cadastrados no sistema
 *
 * @param alunos
 * @param total
 */
void listarAlunos(Aluno alunos[], int total)
{
    for (int i = 0; i < total; i++)
    {
        printf(CYN"ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", alunos[i].idAluno, alunos[i].nome, alunos[i].idade, alunos[i].nascimento.dia, alunos[i].nascimento.mes, alunos[i].nascimento.ano, alunos[i].cidade);
    }
    printf("Total de alunos registrados no sistema: %d\n", total);
    printf("Aperte ENTER para voltar ao menu\n");
    free(getUserInput());
}

/**
 * @brief Salva as informacoes da memoria no arquivo
 *
 * @param arq
 * @param alunos
 * @param total
 * @return FILE*
 */
FILE *salvarArqAluno(FILE *arq, Aluno *alunos, int *total)
{
    int aux;
    char nome[31] = {"./dataAluno.dat"};
    arq = fopen(nome, "r+b");

    printf(YEL"Salvando os dados...\nNao feche o programa!\n");
    for (int i = 0; i < *total; i++)
    {
        fwrite(&alunos[i], sizeof(Aluno), 1, arq);
    }
    aux = ftell(arq);
    if (aux == 0)//Verifica se os dados foram salvos corretamente, se o arquivo estiver vazio eles nao foram salvos
    {
        printf(RED"Erro ao salvar! Tente novamente\n");
    } else
    {
        printf(GRN"Dados salvos com sucesso!\n");
        usleep(5000000);
    }

    return arq;
}

void exportarAlunos(Aluno *alunos, int total) {
    printf(YEL"Exportando dados dos alunos...\n");
    printf("Aguarde...\n");
    usleep(100000);
    char alunos_csv[50];
    sprintf(alunos_csv, "%s.csv", ALUNO_CSV);
    FILE *arq_csv = fopen(alunos_csv, "w+");
    fputs("ID, Nome, Idade, Cidade, Nascimento\n", arq_csv); //Cabeçalho do arquivo csv
    for (int i = 0; i < total; i++)
    {
        fprintf(arq_csv, "%d, %s, %d, %s, %d/%d/%d\n", alunos[i].idAluno, alunos[i].nome, alunos[i].idade, alunos[i].cidade, alunos[i].nascimento.dia, alunos[i].nascimento.mes, alunos[i].nascimento.ano);
    }
    printf(GRN"Dados exportados com sucesso!\n");
    printf(CYN"Aperte ENTER para voltar ao menu\n");
    free(getUserInput());
    fclose(arq_csv);
}