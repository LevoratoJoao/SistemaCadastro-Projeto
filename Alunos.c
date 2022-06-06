#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Alunos.h"
#define MAX 5

FILE *abrirArqAluno(char nome[], Aluno infoAluno[])
{
    FILE *arq = fopen(nome, "rb");
    if (arq == NULL)
    {
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
        fread(infoAluno, sizeof(Aluno), MAX, arq);
    }
    return arq;
}

Aluno *inserirAluno(Aluno infoAluno[], int quantidade, int total[])
{
    int indice = 0;//indice

    printf("Inserir aluno no sistema\n");
    printf("- Preencha os campos abaixo com as informacoes do aluno: \n");
    setbuf(stdin, NULL);
    if (infoAluno[total[0]].idAluno != 0)
    {
        int realocador = realocador + (MAX + 10);
        infoAluno = (Aluno*) realloc(infoAluno, realocador * sizeof(Aluno));
    }
    while (indice < MAX)
    {
        if (infoAluno[indice].idAluno == 0)//If() -- Verifica se o aluno na posição do indice esta vazio, se estiver pode ser registrao um aluno nessaa posição, se nao passa para a proxima
        {
            quantidade = quantidade + indice;//Soma a quantidade de alunos que o usuario o sistema quer inserir com o indice, dessa forma caso alguma posição já estiver sendo ocupada a quantidade de usuarios a serem inserios permace a mesma
            total[0] = quantidade;//total de alunos recebe a quantidade total
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
                    }
                } while (strcasecmp(infoAluno[i].nome, "\0") == 0 || infoAluno[i].idade <= 0 || infoAluno[i].nascimento.dia <= 0 || infoAluno[i].nascimento.mes <= 0 || infoAluno[i].nascimento.ano <= 0 || strcasecmp(infoAluno[i].cidade, "\0") == 0);//do while() -- caso uma das informações inseridas estiver com algum erro o usuario devera inserir novamente
            }
            printf("Aperte ENTER para voltar ao menu\n");
            getchar();// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
            setbuf(stdin, NULL);
            break;
        }
        indice++;
    }
    return infoAluno;
}

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

int removerAluno(Aluno infoAluno[], char nome[], int id, int total[])
{
    char confirmacao;
    for (int i = 0; i < total[0]; i++)
    {
        if (strcasecmp(infoAluno[i].nome, nome) == 0 || infoAluno[i].idAluno == id)
        {
            printf("As seguintes informacoes do aluno serao apagadas do registro:\n");
            printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);
            printf("Deseja continuar ? S - Sim / N - Nao\n");
            setbuf(stdin, NULL);
            scanf("%c", &confirmacao);
            confirmacao = toupper(confirmacao);
            if (confirmacao == 'S')
            {
                limparAlunos(infoAluno, i);
                return 0;
            }
            else
            {
                printf("Operacao finalizada\n");
                printf("Aperte ENTER para voltar ao menu\n");
                getchar();// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
                setbuf(stdin, NULL);
            }
        }
    }
    return 1;
}

int pesquisarAluno(Aluno infoAluno[], char nome[], int id, int total[])
{
    for (int i = 0; i < total[0]; i++)
    {
        if (strcasecmp(infoAluno[i].nome, nome) == 0 || infoAluno[i].idAluno == id)
        {
            printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);
        }
    }
    return 1;
    setbuf(stdin, NULL);
    printf("Aperte ENTER para voltar ao menu\n");
    getchar();// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
}

void alterarAluno(Aluno infoAluno[], char nome[], int id, int total[])
{
    int opcao;
    for (int i = 0; i < total[0]; i++)
    {
        if (strcasecmp(infoAluno[i].nome, nome) == 0 || infoAluno[i].idAluno == id)
        {
            do
            {
                printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);
                printf("Qual informacao deseja alterar do registro do aluno ?\n1 - Nome\n2 - Idade\n3 - Nascimento\n4 - Cidade\n5 - Cancelar\n");
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
                default:
                    printf("Opcao invalida! Digite novamente\n");
                    break;
                }
            } while (opcao != 5 || strcasecmp(infoAluno[i].nome, "\0") == 0 || infoAluno[i].idade <= 0 || infoAluno[i].nascimento.dia <= 0 || infoAluno[i].nascimento.mes <= 0 || infoAluno[i].nascimento.ano <= 0 || strcasecmp(infoAluno[i].cidade, "\0") == 0);
        }
    }
}

void listarAlunos(Aluno infoAluno[], int total[])
{
    for (int i = 0; i < total[0]; i++)
    {
        printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);
    }
    printf("Total de alunos registrados no sistema: %d\n", total[0]);
    printf("Aperte ENTER para voltar ao menu\n");
    setbuf(stdin, NULL);
    getchar();// Apos inserido todos os alunos desejados basta apertaar ENTER para voltar ao menu
}

FILE *salvarArqAluno(FILE *arq, Aluno alunos[], int total[])
{
    int aux;

    printf("Salvando os dados...\nNao feche o programa!\n");
    for (int i = 0; i < total[0]; i++)
    {
        fwrite(alunos, sizeof(Aluno), MAX, arq);
    }
    fseek(arq, 0, SEEK_END);
    aux = ftell(arq);
    if (aux == 0)
    {
        printf("Erro ao salvar! Tente novamente\n");
    } else
    {
        printf("Dados salvos com sucesso!\n");
    }

    return arq;
}