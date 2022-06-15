#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Alunos.h>

#define MAX 10

/**
 * @brief Abre o arquivo que estao salvos as informacoes dos alunos
 *
 * @param nome
 * @param infoAluno
 * @return FILE*
 */
FILE *abrirArqAluno(char nome[], Aluno infoAluno[])
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
    for (int i = 0; i < MAX; i++)
    {
        //armazena as infformacoes do arquivo na variavel
        fread(&infoAluno[i], sizeof(Aluno), 1, arq);
        printf("Lendo os dados do arquivo...\n");
    }

    return arq;
}

/**
 * @brief Funcao para inserir as informacoes do aluno
 *
 * @param infoAluno
 * @param quantidade
 * @param total
 * @return Aluno*
 */
int inserirAluno(Aluno infoAluno[], int quantidade, int total)
{
    
    //Verifica se tem um espaço disponível (id = 0)
    while()


    //Se saiu do while pq acabou o vetor  indice == total-> realloc


    //Insere no indice "indice"
    
    int indice = 0;//indice

    printf("Inserir aluno no sistema\n");
    printf("- Preencha os campos abaixo com as informacoes do aluno: \n");
    setbuf(stdin, NULL);

    int realocador = MAX; // #######################################

    if (quantidade > MAX)
    {
        realocador += 10; // #######################################

        infoAluno = (Aluno*) realloc(infoAluno, realocador * sizeof(Aluno));//realoca infoAluno para preencher mais
        //realloc ainda nao esta funcionando
        if (infoAluno == NULL)
        {
            printf("Erro: memoria insuficiente\n");
            exit(1);
        }
    }

    while (indice < MAX)
    {
        if (infoAluno[indice].idAluno == 0)//If() -- Verifica se o aluno na posição do indice esta vazio, se estiver pode ser registrao um aluno nessaa posição, se nao passa para a proxima
        {
            quantidade = quantidade + indice;//Soma a quantidade de alunos que o usuario o sistema quer inserir com o indice, dessa forma caso alguma posição já estiver sendo ocupada a quantidade de usuarios a serem inserios permace a mesma
            total = quantidade;//total de alunos recebe a quantidade total
            for (int i = indice; i < quantidade; i++)//i recebe o valor de indice para que a ordem de inserção dos dados seja de acordo com o que já esta registrado no sistema
            {
                do
                {
                    infoAluno[i].idAluno = i + 1;
                    printf("\nAluno %i\n", i + 1);
                    setbuf(stdin, NULL);
                    printf("Nome: ");
                    fgets(infoAluno[i].nome, 50, stdin);
                    infoAluno[i].nome[strcspn(infoAluno[i].nome, "\n")] = '\0';
                    printf("Idade: ");
                    scanf("%d", &infoAluno[i].idade);
                    printf("Data de nascimento: dd/mm/aa\n");
                    scanf("%d", &infoAluno[i].nascimento.dia);
                    scanf("%d", &infoAluno[i].nascimento.mes);
                    scanf("%d", &infoAluno[i].nascimento.ano);
                    setbuf(stdin, NULL);
                    printf("Cidade em que nasceu: ");
                    fgets(infoAluno[i].cidade, 30, stdin);
                    infoAluno[i].cidade[strcspn(infoAluno[i].cidade, "\n")] = '\0';
                    setbuf(stdin, NULL);
                    if (strcasecmp(infoAluno[i].nome, "\0") == 0 || infoAluno[i].idade <= 0 || infoAluno[i].nascimento.dia <= 0 || infoAluno[i].nascimento.mes <= 0 || infoAluno[i].nascimento.ano <= 0 || strcasecmp(infoAluno[i].cidade, "\0") == 0)//If() -- verifica se os dados do aluno foram inseridos corretamente
                    {
                        printf("Erro!!! Preencha novamente\n");
                    } else
                    {
                        printf("Aluno cadastrado no sistema!\n");
                        printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);//Mostra as informacoes atuais do aluno
                    }
                } while (strcasecmp(infoAluno[i].nome, "\0") == 0 || infoAluno[i].idade <= 0 || infoAluno[i].nascimento.dia <= 0 || infoAluno[i].nascimento.mes <= 0 || infoAluno[i].nascimento.ano <= 0 || strcasecmp(infoAluno[i].cidade, "\0") == 0);//do while() -- caso uma das informações inseridas estiver com algum erro o usuario devera inserir novamente
            }
            printf("Aperte ENTER para voltar ao menu\n");
            setbuf(stdin, NULL);
            getchar();// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
            break;
        }
        indice++;
    }

    return total;
}

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
FILE *salvarArqAluno(FILE *arq, Aluno alunos[], int total)
{
    int aux;

    printf("Salvando os dados...\nNao feche o programa!\n");
    for (int i = 0; i < total; i++)
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