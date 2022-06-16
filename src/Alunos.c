#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Alunos.h>
#include <utils.h>

#define MAX 10


Aluno *getAlunos(FILE *arquivo, int *total) {
    Aluno *alunos = NULL;

    char tmp; //variavel temporaria para ler o arquivo
    int pos = 0;
    do {
        tmp = getc(arquivo);
        // fread(&tmp, sizeof(char), 1, arquivo);
        // printf("%c\n", tmp);
        printf("%ld\n", ftell(arquivo));

        if (tmp == EOF) break;

        fseek(arquivo, -1, ftell(arquivo)); // Reposiciona a cabeça de leitora para -1 em relação ao atual

        if (pos % MAX == 0) {
            alunos = realloc(alunos, sizeof(Aluno) * (pos + MAX));

            for (int i = pos; i < pos + MAX; i++) { // Indica que as posições estão vazias
                alunos[i].idAluno = 0;
            }
        }

        fread(&alunos[pos], sizeof(Aluno), 1, arquivo);

        pos++;
    } while (tmp != EOF);

    *total = pos;

    return alunos;
}






























/**
 * @brief Abre o arquivo que estao salvos as informacoes dos alunos
 *
 * @param nome
 * @param infoAluno
 * @return FILE*
 */
FILE *abrirArqAluno(char *nome)
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
    printf("Arquivo aberto\n");

    return arq;
}

// void lerArquivo(FILE *arq, Aluno infoAluno[]) {
//     for (int i = 0; i < MAX; i++)
//     {
//         //armazena as infformacoes do arquivo na variavel
//         fread(&infoAluno[i], sizeof(Aluno), 1, arq);
//         printf("Lendo os dados do arquivo...\n");
//     }
// }

int verificarPreenchimento(Aluno infoAluno[], int indice)
{
    if (strcasecmp(infoAluno[indice].nome, "\0") == 0 || infoAluno[indice].idade <= 0 || infoAluno[indice].nascimento.dia <= 0 || infoAluno[indice].nascimento.mes <= 0 || infoAluno[indice].nascimento.ano <= 0 || strcasecmp(infoAluno[indice].cidade, "\0") == 0)//If() -- verifica se os dados do aluno foram inseridos corretamente
    {
        return 1;
    } else {
        return 0;
    }
}


/**
 * @brief Funcao para inserir as informacoes do aluno
 *
 * @param infoAluno
 * @param quantidade
 * @param total
 * @return Aluno*
 */
Aluno *inserirAluno(Aluno *infoAluno, int *total)
{
    int indice = 0; //indice
    char *confirma = NULL; //confirmacao
    //Verifica se tem um espaço disponível (id = 0)
    int valorOpcao = 0;
    while (valorOpcao != 2)
    {

        for (int i = 0; i < *total; i++) {
            if (infoAluno[i].idAluno == 0) {
                indice = i;
                break;
            }
        }


        // while (indice < total) //verifica se o indice é menor que o total
        // {
        //     if (infoAluno[indice].idAluno == 0)
        //     {
        //         break;
        //     }
        //     indice++;
        // }

        if (indice == *total)
        {
            printf("Nao ha espaco disponivel...\nRealocando...\n");
            *total += 10;
            infoAluno = (Aluno*) realloc(infoAluno, (*total) * sizeof(Aluno)); //realoca infoAluno para preencher mais
            if (infoAluno == NULL)
            {
                printf("Erro: memoria insuficiente\n");
                exit(1);//return -1;
            }
        }

        do {
            infoAluno[indice].idAluno = indice + 1;
            printf("\nAluno %i\n", indice + 1);
            setbuf(stdin, NULL);
            printf("Nome: ");
            fgets(infoAluno[indice].nome, 50, stdin);
            infoAluno[indice].nome[strcspn(infoAluno[indice].nome, "\n")] = '\0';
            printf("Idade: ");
            scanf("%d", &infoAluno[indice].idade);
            printf("Data de nascimento: dd/mm/aa\n");
            scanf("%d", &infoAluno[indice].nascimento.dia);
            scanf("%d", &infoAluno[indice].nascimento.mes);
            scanf("%d", &infoAluno[indice].nascimento.ano);
            setbuf(stdin, NULL);
            printf("Cidade em que nasceu: ");
            fgets(infoAluno[indice].cidade, 30, stdin);
            infoAluno[indice].cidade[strcspn(infoAluno[indice].cidade, "\n")] = '\0';
            setbuf(stdin, NULL);
            if (verificarPreenchimento(infoAluno, indice) == 1) { //verifica se os dados foram preenchidos corretamente
                printf("Erro!!! Preencha novamente\n");
            }
            else {
                printf("Aluno cadastrado no sistema!\n");
                (*total)++;
                printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[indice].idAluno, infoAluno[indice].nome, infoAluno[indice].idade, infoAluno[indice].nascimento.dia, infoAluno[indice].nascimento.mes, infoAluno[indice].nascimento.ano, infoAluno[indice].cidade);//Mostra as informacoes atuais do aluno
                printf("Deseja cadastrar outro aluno? (1 - S/ 2 - N): ");
                confirma = getUserInput();
                printf("%s\n", confirma);
                char valorOpcao = atoi(confirma);
                free(confirma);

                if (valorOpcao == 2)
                {
                    printf("Aperte ENTER para voltar ao menu\n");
                    free(getUserInput());// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
                    return infoAluno;
                } else if (valorOpcao != 1)
                {
                    printf("Erro!!!\nDigite novamente\n");
                    printf("Deseja cadastrar outro aluno? (1 - S/ 2 - N): ");
                    confirma = getUserInput();
                    printf("%s\n", confirma);
                    valorOpcao = atoi(confirma);
                    free(confirma);
                }
            }
        } while (verificarPreenchimento(infoAluno, indice) == 1);//do while() -- caso uma das informações inseridas estiver com algum erro o usuario devera inserir novamente
    }

    return infoAluno;
}

    //while()


    //Se saiu do while pq acabou o vetor  indice == total-> realloc


    //Insere no indice "indice"




/**
 * @brief Limpa os dados do aluno que o usuario deseja excluir, deixando assim uma posicao livre no sistema
 *
 * @param infoAluno
 * @param indice
 * @return Aluno
 */
Aluno limparAlunos(Aluno infoAluno[], int indice)
{
    strcpy(infoAluno[indice].nome, "\0");
    infoAluno[indice].idade = 0;
    infoAluno[indice].idAluno = 0;
    infoAluno[indice].nascimento.dia = 0;
    infoAluno[indice].nascimento.mes = 0;
    infoAluno[indice].nascimento.ano = 0;
    strcpy(infoAluno[indice].cidade, "\0");
    return infoAluno[indice];
}

/**
 * @brief Funcao que recebe o id/nome do aluno que o usuario deseja remover, faz a busca pelo mesmo e retorna 1 caso nao seja encontrado e 0 caso encontre
 *
 * @param infoAluno
 * @param nome
 * @param id
 * @param total
 * @return int
 */
int removerAluno(Aluno infoAluno[], char nome[], int id, int total)
{
    char confirmacao;
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(infoAluno[i].nome, nome) == 0 || infoAluno[i].idAluno == id)//Busca o aluno desejado
        {
            printf("As seguintes informacoes do aluno serao apagadas do registro:\n");
            printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);
            printf("Deseja continuar ? S - Sim / N - Nao\n");
            setbuf(stdin, NULL);
            scanf("%c", &confirmacao);
            confirmacao = toupper(confirmacao);//Confirmacao para excluir
            if (confirmacao == 'S')
            {
                limparAlunos(infoAluno, i);
                return 0;
            }
            else
            {
                printf("Operacao finalizada\n");
                printf("Aperte ENTER para voltar ao menu\n");
                getchar();
                setbuf(stdin, NULL);
                return 3;
            }
        }
    }
    return 1;
}

/**
 * @brief Pesquisar aluno desejado no sistema, se achar retorna 0 se nao retorna 1
 *
 * @param infoAluno
 * @param nome
 * @param id
 * @param total
 * @return int
 */
int pesquisarAluno(Aluno infoAluno[], char nome[], int id, int total)
{
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(infoAluno[i].nome, nome) == 0 || infoAluno[i].idAluno == id)
        {
            printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);
            return 0;
        }
    }
    return 1;
    setbuf(stdin, NULL);
    printf("Aperte ENTER para voltar ao menu\n");
    getchar();
}

/**
 * @brief Funcao para realizar a alteracao das informacoes do aluno desejado
 *
 * @param infoAluno
 * @param nome
 * @param id
 * @param total
 */
void alterarAluno(Aluno infoAluno[], char nome[], int id, int total)
{
    int opcao;
    for (int i = 0; i < total; i++)
    {
        if (strcasecmp(infoAluno[i].nome, nome) == 0 || infoAluno[i].idAluno == id)
        {
            do
            {
                printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);//Mostra as informacoes atuais do aluno
                printf("Qual informacao deseja alterar do registro do aluno ?\n1 - Nome\n2 - Idade\n3 - Nascimento\n4 - Cidade\n5 - Cancelar\n");//Opcoes de alteracao (ID nao pode ser alterado)
                scanf("%d", &opcao);
                printf("Preencha o campo:\n");
                switch (opcao)
                {
                case 1:
                    printf("Nome: ");
                    setbuf(stdin, NULL);
                    fgets(infoAluno[i].nome, 50, stdin);
                    infoAluno[i].nome[strcspn(infoAluno[i].nome, "\n")] = '\0';
                    break;
                case 2:
                    printf("Idade: ");
                    scanf("%d", &infoAluno[i].idade);
                    break;
                case 3:
                    printf("Data de nascimento: dd/mm/aa\n");
                    scanf("%d", &infoAluno[i].nascimento.dia);
                    scanf("%d", &infoAluno[i].nascimento.mes);
                    scanf("%d", &infoAluno[i].nascimento.ano);
                    break;
                case 4:
                    printf("Cidade em que nasceu: ");
                    setbuf(stdin, NULL);
                    fgets(infoAluno[i].cidade, 30, stdin);
                    infoAluno[i].cidade[strcspn(infoAluno[i].cidade, "\n")] = '\0';
                    break;
                case 5:
                    return;
                    break;
                default:
                    printf("Opcao invalida! Digite novamente\n");
                    break;
                }
                if (strcasecmp(infoAluno[i].nome, "\0") == 0 || infoAluno[i].idade <= 0 || infoAluno[i].nascimento.dia <= 0 || infoAluno[i].nascimento.mes <= 0 || infoAluno[i].nascimento.ano <= 0 || strcasecmp(infoAluno[i].cidade, "\0") == 0)//If() -- verifica se os dados do aluno foram alterados corretamente
                {
                    printf("Erro!!! Preencha novamente\n");
                } else
                {
                    printf("Aluno alterado no sistema!\n");
                }
            } while (opcao != 5 || strcasecmp(infoAluno[i].nome, "\0") == 0 || infoAluno[i].idade <= 0 || infoAluno[i].nascimento.dia <= 0 || infoAluno[i].nascimento.mes <= 0 || infoAluno[i].nascimento.ano <= 0 || strcasecmp(infoAluno[i].cidade, "\0") == 0);//Verificacao de preenchimento das informacoes
        }
    }
}

/**
 * @brief Lista alunos cadastrados no sistema
 *
 * @param infoAluno
 * @param total
 */
void listarAlunos(Aluno infoAluno[], int total)
{
    for (int i = 0; i < MAX; i++)
    {
        printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);
    }
    printf("Total de alunos registrados no sistema: %d\n", total);
    printf("Aperte ENTER para voltar ao menu\n");
    setbuf(stdin, NULL);
    getchar();
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

    printf("Salvando os dados...\nNao feche o programa!\n");
    for (int i = 0; i < *total; i++)
    {
        fwrite(&alunos[i], sizeof(Aluno), 1, arq);
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