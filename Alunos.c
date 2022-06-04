#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Alunos.h"
#define MAX 10

FILE *abrirArqAluno(char nome[], Aluno infoAluno[])
{
    FILE *arq = fopen(nome, "rb");
    if (arq == NULL)
    {
        printf("Arquivo nao esta no sistema!\nCriando arquivo...\n");
        FILE *arq = fopen(nome, "wb");
        if (arq == NULL)
        {
            printf("Erro ao abrir arquivo!!!\n");
            exit(1);
        }
    }
    for (int i = 0; i < MAX; i++)
    {
        fread(infoAluno, sizeof(Aluno), MAX, arq);
    }
    return arq;
}


int inserirAluno(Aluno infoAluno[], int quantidade, int total[])
{
    int indice = 0;//indice

    printf("Inserir aluno no sistema\nAguarde...\n");//Carregando sistema
    printf("- Preencha os campos abaixo com as informacoes do aluno: \n");
    setbuf(stdin, NULL);
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
    return total[0];
}

void removerAluno(Aluno infoAluno[], char nome[], int id, int total[])
{
    for (int i = 0; i < total[0]; i++)
    {
        if (strcasecmp(infoAluno[i].nome, nome) == 0 || infoAluno[i].idAluno == id)
        {
            printf("Acerto");
        }
    }
}

void listarAlunos(Aluno infoAluno[], int total[])
{
    for (int i = 0; i < MAX; i++)
    {
        printf("ID: %d | Nome: %10s | Idade: %d | Nascimento: %d/%d/%d | Cidade: %10s\n", infoAluno[i].idAluno, infoAluno[i].nome, infoAluno[i].idade, infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano, infoAluno[i].cidade);
    }
}

FILE *salvarArqAluno(FILE *arq, Aluno alunos[], int total[])
{
    printf("Salvando os dados...\nNao feche o programa!\n");
    for (int i = 0; i < total[0]; i++)
    {
        fwrite(alunos, sizeof(Aluno), MAX, arq);
    }
    return arq;
}