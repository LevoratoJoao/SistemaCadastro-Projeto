#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Cursos.h"
#define MAX 10

/**
 * @brief Abre o arquivo que estao salvos as informacoes dos cursos
 *
 * @param nome
 * @param infoCurso
 * @return FILE*
 */
FILE *abrirArqCurso(char nome[], Curso infoCurso[])
{
    FILE *arq = fopen(nome, "rb");
    if (arq == NULL)
    {
        //se o arquivo nao existe ele cria um novo
        printf("Arquivo nao esta no sistema!\nCriando arquivo...\n");
        arq = fopen(nome, "wb");
        if (arq == NULL)
        {
            printf("Erro ao abrir arquivo!!!\n");
            exit(1);
        }
    }
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo!!!\n");
        exit(1);
    }
    for (int i = 0; i < MAX; i++)
    {
        //armazena as informacoes do arquivo na variavel
        fread(infoCurso, sizeof(Curso), MAX, arq);
    }
    return arq;
}

/**
 * @brief Funcao para inserir as informacoes do curso
 *
 * @param infoCurso
 * @param quantidade
 * @param total
 * @return Curso*
 */
Curso *inserirCurso(Curso infoCurso[], int quantidade, int total[])
{
    int indice = 0;//indice

    printf("Inserir curso no sistema\n");
    printf("- Preencha os campos abaixo com as informacoes do Curso: \n");
    setbuf(stdin, NULL);
    if (infoCurso[total[1] - 1].idCurso != 0)//Verifica se a ultima posicao do vetor esta preenchida (vetor total[1] com total de cursos menos 1)
    {
        int realocador = realocador + (MAX + 10);
        infoCurso = (Curso*) realloc(infoCurso, realocador * sizeof(Curso));//realoca infoCurso para preencher mais
        //realloc ainda nao esta funcionando
        if (infoCurso == NULL)
        {
            printf("Erro: memoria insuficiente\n");
            exit(1);
        }
    }
    while (indice < MAX)
    {
        if (infoCurso[indice].idCurso == 0)//If() -- Verifica se o Curso na posição do indice esta vazio, se estiver pode ser registrao um Curso nessaa posição, se nao passa para a proxima
        {
            quantidade = quantidade + indice;//Soma a quantidade de Cursos que o usuario do sistema quer inserir com o indice, dessa forma caso alguma posição já estiver sendo ocupada a quantidade de usuarios a serem inserios permace a mesma
            total[1] = quantidade;//total de Cursos recebe a quantidade total
            for (int i = indice; i < quantidade; i++)//i recebe o valor de indice para que a ordem de inserção dos dados seja de acordo com o que já esta registrado no sistema
            {
                do
                {
                    infoCurso[i].idCurso = i + 1;
                    printf("\nCurso %i\n", i + 1);
                    setbuf(stdin, NULL);
                    printf("Nome: ");
                    fgets(infoCurso[i].nome, 50, stdin);
                    infoCurso[i].nome[strcspn(infoCurso[i].nome, "\n")] = '\0';
                    printf("Duracao (semestres): ");
                    scanf("%d", &infoCurso[i].duracao);
                    printf("Periodo: ");
                    setbuf(stdin, NULL);
                    fgets(infoCurso[i].periodo, 10, stdin);
                    infoCurso[i].periodo[strcspn(infoCurso[i].periodo, "\n")] = '\0';
                    setbuf(stdin, NULL);
                    if (strcasecmp(infoCurso[i].nome, "\0") == 0 || infoCurso[i].duracao <= 0 || strcasecmp(infoCurso[i].periodo, "\0") == 0)//If() -- verifica se os dados do Curso foram inseridos corretamente
                    {
                        printf("Erro!!! Preencha novamente\n");
                    } else
                    {
                        printf("Curso cadastrado no sistema!\n");
                    }
                } while (strcasecmp(infoCurso[i].nome, "\0") == 0 || infoCurso[i].duracao <= 0 || strcasecmp(infoCurso[i].periodo, "\0") == 0);//do while() -- caso uma das informações inseridas estiver com algum erro o usuario devera inserir novamente
            }
            printf("Aperte ENTER para voltar ao menu\n");
            setbuf(stdin, NULL);
            getchar();//Apos inserido todos os Cursos desejados basta apertaar ENTER para voltar ao menu
            break;
        }
        indice++;
    }
    return infoCurso;
}

/**
 * @brief Limpa os dados do Curso que o usuario deseja excluir, deixando assim uma posicao livre no sistema
 *
 * @param infoCurso
 * @param indice
 * @return Curso
 */
Curso limparCursos(Curso infoCurso[], int indice)
{
    strcpy(infoCurso[indice].nome, "\0");
    infoCurso[indice].duracao = 0;
    infoCurso[indice].idCurso = 0;
    strcpy(infoCurso[indice].periodo, "\0");
    return infoCurso[indice];
}

/**
 * @brief Funcao que recebe o id/nome do curso que o usuario deseja remover, faz a busca pelo mesmo e retorna 1 caso nao seja encontrado e 0 caso encontre
 *
 * @param infoCurso
 * @param nome
 * @param id
 * @param total
 * @return int
 */
int removerCurso(Curso infoCurso[], char nome[], int id, int total[])
{
    char confirmacao;
    for (int i = 0; i < total[1]; i++)
    {
        if (strcasecmp(infoCurso[i].nome, nome) == 0 || infoCurso[i].idCurso == id)//Busca o curso desejado
        {
            printf("As seguintes informacoes do Curso serao apagadas do registro:\n");
            printf("ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", infoCurso[i].idCurso, infoCurso[i].nome, infoCurso[i].duracao, infoCurso[i].periodo);
            printf("Deseja continuar ? S - Sim / N - Nao\n");
            setbuf(stdin, NULL);
            scanf("%c", &confirmacao);
            confirmacao = toupper(confirmacao);//Confirmacao para excluir
            if (confirmacao == 'S')
            {
                limparCursos(infoCurso, i);//funcao
                return 0;
            }
            else
            {
                printf("Operacao finalizada\n");
                printf("Aperte ENTER para voltar ao menu\n");
                getchar();
                setbuf(stdin, NULL);
                return 0;
            }
        }
    }
    return 1;
}

/**
 * @brief Pesquisar curso desejado no sistema, se achar retorna 0 se nao retorna 1
 *
 * @param infoCurso
 * @param nome
 * @param id
 * @param total
 * @return int
 */
int pesquisarCurso(Curso infoCurso[], char nome[], int id, int total[])
{
    for (int i = 0; i < total[1]; i++)
    {
        if (strcasecmp(infoCurso[i].nome, nome) == 0 || infoCurso[i].idCurso == id)
        {
            printf("ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", infoCurso[i].idCurso, infoCurso[i].nome, infoCurso[i].duracao, infoCurso[i].periodo);

            return 0;
        }
    }
    return 1;
}

/**
 * @brief Funcao para realizar a alteracao das informacoes do curso desejado
 *
 * @param infoCurso
 * @param nome
 * @param id
 * @param total
 */
//OBS: apos alterar o pritf mostra os dados alterados, isso comprova que dentro da função os dados são armazenados de forma correta mas ao voltar para a main eles são apagados
void alterarCurso(Curso infoCurso[], char nome[], int id, int total[])
{
    int opcao;
    for (int i = 0; i < total[1]; i++)
    {
        if (strcasecmp(infoCurso[i].nome, nome) == 0 || infoCurso[i].idCurso == id)//Busca o curso desejado
        {
            do
            {
                printf("ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", infoCurso[i].idCurso, infoCurso[i].nome, infoCurso[i].duracao, infoCurso[i].periodo);//Mostra as informacoes atuais do curso
                printf("Qual informacao deseja alterar do registro do Curso ?\n1 - Nome\n2 - Duracao\n3 - Periodo\n4 - Cancelar\n");//Opcoes de alteracao (ID nao pode ser alterado)
                scanf("%d", &opcao);
                printf("Preencha o campo:\n");
                switch (opcao)
                {
                case 1:
                    printf("Nome: ");
                    setbuf(stdin, NULL);
                    fgets(infoCurso[i].nome, 50, stdin);
                    infoCurso[i].nome[strcspn(infoCurso[i].nome, "\n")] = '\0';
                    break;
                case 2:
                    printf("Duracao (semestres): ");
                    scanf("%d", &infoCurso[i].duracao);
                    break;
                case 3:
                    printf("Periodo: ");
                    setbuf(stdin, NULL);
                    fgets(infoCurso[i].periodo, 10, stdin);
                    infoCurso[i].periodo[strcspn(infoCurso[i].periodo, "\n")] = '\0';
                    break;
                case 4:
                    break;
                default:
                    printf("Opcao invalida! Digite novamente\n");
                    break;
                }
                if (strcasecmp(infoCurso[i].nome, "\0") == 0 || infoCurso[i].duracao <= 0 || strcasecmp(infoCurso[i].periodo, "\0") == 0)//If() -- verifica se os dados do Curso foram alterados corretamente
                {
                    printf("Erro!!! Preencha novamente\n");
                } else
                {
                    printf("Curso alterado no sistema!\n");
                }
            } while (opcao != 4 || strcasecmp(infoCurso[i].nome, "\0") == 0 || infoCurso[i].duracao <= 0 || strcasecmp(infoCurso[i].periodo, "\0") == 0);//Verificacao de preenchimento das informacoes
        }
    }
}

/**
 * @brief Lista cursos cadastrados no sistema
 *
 * @param infoCurso
 * @param total
 */
void listarCursos(Curso infoCurso[], int total[])
{
    for (int i = 0; i < total[1]; i++)
    {
        printf("ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", infoCurso[i].idCurso, infoCurso[i].nome, infoCurso[i].duracao, infoCurso[i].periodo);
    }
    printf("Total de cursos registrados no sistema: %d\n", total[1]);
    printf("Aperte ENTER para voltar ao menu\n");
    setbuf(stdin, NULL);
    getchar();
}

/**
 * @brief Salva as informacoes da memoria no arquivo
 *
 * @param arq
 * @param cursos
 * @param total
 * @return FILE*
 */
FILE *salvarArqCurso(FILE *arq, Curso cursos[], int total[])
{
    int aux;

    printf("Salvando os dados...\nNao feche o programa!\n");
    for (int i = 0; i < total[1]; i++)
    {
        fwrite(cursos, sizeof(Curso), MAX, arq);
    }
    fseek(arq, 0, SEEK_END);
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