#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Cursos.h"
#define MAX 10

FILE *abrirArqCurso(char nome[], Curso infoCurso[])
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
        fread(infoCurso, sizeof(Curso), MAX, arq);
    }
    return arq;
}

Curso *inserirCurso(Curso infoCurso[], int quantDuracao, int total[])
{
    int indice = 0;//indice

    printf("Inserir Curso no sistema\n");
    printf("- Preencha os campos abaixo com as informacoes do Curso: \n");
    setbuf(stdin, NULL);
    if (infoCurso[total[1]].idCurso != 0)
    {
        int realocador = realocador + (MAX + 10);
        infoCurso = (Curso*) realloc(infoCurso, realocador * sizeof(Curso));
    }
    while (indice < MAX)
    {
        if (infoCurso[indice].idCurso == 0)//If() -- Verifica se o Curso na posição do indice esta vazio, se estiver pode ser registrao um Curso nessaa posição, se nao passa para a proxima
        {
            quantDuracao = quantDuracao + indice;//Soma a quantDuracao de Cursos que o usuario o sistema quer inserir com o indice, dessa forma caso alguma posição já estiver sendo ocupada a quantDuracao de usuarios a serem inserios permace a mesma
            total[1] = quantDuracao;//total de Cursos recebe a quantDuracao total
            for (int i = indice; i < quantDuracao; i++)//i recebe o valor de indice para que a ordem de inserção dos dados seja de acordo com o que já esta registrado no sistema
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
                    setbuf(stdin, NULL);
                    printf("Periodo: ");
                    fgets(infoCurso[i].periodo, 30, stdin);
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
            getchar();// Apos inserido todos os Cursos desejados basta apertaar ENTER para voltar ao menu
            setbuf(stdin, NULL);
            break;
        }
        indice++;
    }
    return infoCurso;
}

Curso limparCursos(Curso infoCurso[], int indice)
{
    strcpy(infoCurso[indice].nome, "\0");
    infoCurso[indice].duracao = 0;
    infoCurso[indice].idCurso = 0;
    strcpy(infoCurso[indice].periodo, "\0");
    return infoCurso[indice];
}

int removerCurso(Curso infoCurso[], char nome[], int id, int total[])
{
    char confirmacao;
    for (int i = 0; i < total[1]; i++)
    {
        if (strcasecmp(infoCurso[i].nome, nome) == 0 || infoCurso[i].idCurso == id)
        {
            printf("As seguintes informacoes do Curso serao apagadas do registro:\n");
            printf("ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", infoCurso[i].idCurso, infoCurso[i].nome, infoCurso[i].duracao, infoCurso[i].periodo);
            printf("Deseja continuar ? S - Sim / N - Nao\n");
            setbuf(stdin, NULL);
            scanf("%c", &confirmacao);
            confirmacao = toupper(confirmacao);
            if (confirmacao == 'S')
            {
                limparCursos(infoCurso, i);
                return 0;
            }
            else
            {
                printf("Operacao finalizada\n");
                printf("Aperte ENTER para voltar ao menu\n");
                getchar();// Apos inserido todos os Cursos desejados basta apertaar ENTER para voltar ao menu
                setbuf(stdin, NULL);

                return 0;
            }
        }
    }
    return 1;
}

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

void alterarCurso(Curso infoCurso[], char nome[], int id, int total[])
{
    int opcao;
    for (int i = 0; i < total[1]; i++)
    {
        if (strcasecmp(infoCurso[i].nome, nome) == 0 || infoCurso[i].idCurso == id)
        {
            do
            {
                printf("ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", infoCurso[i].idCurso, infoCurso[i].nome, infoCurso[i].duracao, infoCurso[i].periodo);
                printf("Qual informacao deseja alterar do registro do Curso ?\n1 - Nome\n2 - Duracao\n3 - Periodo\n4 - Cancelar\n");
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
                default:
                    printf("Opcao invalida! Digite novamente\n");
                    break;
                }
            } while (opcao != 4 || strcasecmp(infoCurso[i].nome, "\0") == 0 || infoCurso[i].duracao <= 0 || strcasecmp(infoCurso[i].periodo, "\0") == 0);
        }
    }
}

void listarCursos(Curso infoCurso[], int total[])
{
    for (int i = 0; i < total[1]; i++)
    {
        printf("ID: %d | Nome: %10s | Duracao: %d | Periodo: %10s\n", infoCurso[i].idCurso, infoCurso[i].nome, infoCurso[i].duracao, infoCurso[i].periodo);
    }
    printf("Total de alunos registrados no sistema: %d", total[1]);
    printf("Aperte ENTER para voltar ao menu\n");
    setbuf(stdin, NULL);
    getchar();// Apos inserido todos os Cursos desejados basta apertaar ENTER para voltar ao menu
}

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
    if (aux == 0)
    {
        printf("Erro ao salvar! Tente novamente\n");
    } else
    {
        printf("Dados salvos com sucesso!\n");
    }

    return arq;
}