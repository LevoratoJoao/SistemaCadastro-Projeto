/**
 * @file gerenciadorMatriculasCastaldi.c
 * @author João Vitor Levorato de Souza (joaosouza.2021@alunos.utfpr.edu.br)
 * @brief
 * @version 0.1
 * @date 2022-05-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    int numeroMatricua;
    char nome[51];
    int idade;
    Data nascimento;
    int anoMatricula;
    char curso[31];
} Aluno;

// void limparRegistro(Aluno *infoAluno, int indice)
// {
//     strcpy(infoAluno[indice].nome, "\0");
//     infoAluno[indice].idade = 0;
//     infoAluno[indice].nascimento.dia = 0;
//     infoAluno[indice].nascimento.mes = 0;
//     infoAluno[indice].nascimento.ano = 0;
//     infoAluno[indice].anoMatricula = 0;
//     strcpy(infoAluno[indice].curso, "\0");
// }

/**
 * @brief Função onde é feita o preenchimento das informações da matricula
 *
 * @param infoAluno
 * @param quantidade
 */
void inserirMatricula(Aluno infoAluno[], int quantidade)
{
    int indice = 0;//indice

    while (indice < MAX)
    {
        if (strcasecmp(infoAluno[indice].nome, "\0") == 0 || infoAluno[indice].idade <= 0 || infoAluno[indice].nascimento.dia <= 0 || infoAluno[indice].nascimento.mes <= 0 || infoAluno[indice].nascimento.ano <= 0 || infoAluno[indice].anoMatricula <= 0 || strcasecmp(infoAluno[indice].curso, "\0") == 0)
        {
            quantidade = quantidade + indice;
            for (int i = indice; i < quantidade; i++)
            {
                do
                {
                    infoAluno[i].numeroMatricua = i + 1;
                    printf("\nMatricula %i\n", i + 1);
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
                    printf("Ano da matricula: ");
                    scanf("%d", &infoAluno[i].anoMatricula);
                    setbuf(stdin, NULL);
                    printf("Curso: ");
                    fgets(infoAluno[i].curso, 30, stdin);
                    infoAluno[i].curso[strcspn(infoAluno[i].curso, "\n")] = '\0';
                    if (strcasecmp(infoAluno[i].nome, "\0") == 0 || infoAluno[i].idade <= 0 || infoAluno[i].nascimento.dia <= 0 || infoAluno[i].nascimento.mes <= 0 || infoAluno[i].nascimento.ano <= 0 || infoAluno[i].anoMatricula <= 0 || strcasecmp(infoAluno[i].curso, "\0") == 0)
                    {
                        printf("Erro!!! Preencha novamente\n");
                    } else
                    {
                        printf("Matricula cadastrada no sistema!\n");

                    }
                } while (strcasecmp(infoAluno[i].nome, "\0") == 0 || infoAluno[i].idade <= 0 || infoAluno[i].nascimento.dia <= 0 || infoAluno[i].nascimento.mes <= 0 || infoAluno[i].nascimento.ano <= 0 || infoAluno[i].anoMatricula <= 0 || strcasecmp(infoAluno[i].curso, "\0") == 0);
            }
            printf("Aperte ENTER para voltar ao menu\n");
            getchar();
            setbuf(stdin, NULL);
            break;
        }
        indice++;
    }
}

/**
 * @brief Função que exlcui uma matricula do sistema a partir do numero da matricula
 *
 * @param infoAluno
 * @param idAluno
 * @param quantidade
 */
void excluirMatricula(Aluno *infoAluno, int idAluno, int quantidade)
{
    char confirmacao;
    for (int i = 0; i < quantidade; i++)
    {
        if (infoAluno[i].numeroMatricua == idAluno)
        {
            setbuf(stdin, NULL);
            printf("Deseja mesmo excluir esta matricula ? S / N\n");
            scanf("%c", &confirmacao);
            setbuf(stdin, NULL);
            if (confirmacao == 'S')
            {
                printf("As seguintes informacoes da matricula serao excluidas\n");
                printf("Nome: %s\n", infoAluno[i].nome);
                printf("Idade: %d\n", infoAluno[i].idade);
                printf("Nascimento: %d/%d/%d\n", infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano);
                printf("Ano da matricula: %d\n", infoAluno[i].anoMatricula);
                printf("Curso: %s\n", infoAluno[i].curso);
                strcpy(infoAluno[idAluno].nome, "\0");
                infoAluno[idAluno].idade = 0;
                infoAluno[idAluno].nascimento.dia = 0;
                infoAluno[idAluno].nascimento.mes = 0;
                infoAluno[idAluno].nascimento.ano = 0;
                infoAluno[idAluno].anoMatricula = 0;
                strcpy(infoAluno[idAluno].curso, "\0");
                quantidade = quantidade - 1;
                infoAluno = realloc(infoAluno, (quantidade) * sizeof(Aluno));
                setbuf(stdin, NULL);
                printf("Aperte ENTER para voltar ao menu\n");
                getchar();
                setbuf(stdin, NULL);
            } else
            {
                printf("Operacao finalizada\nVoltando para o menu...\n");
                break;
            }
        }
    }
}

/**
 * @brief Lista todos os cadastros do sistema
 *
 * @param infoAluno
 * @param quantidade
 */
void listarMatriculas(Aluno *infoAluno)
{
    setbuf(stdin, NULL);
    printf("Listagem de todas as matriculas no sistema:\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("\nNome: %s\n", infoAluno[i].nome);
        printf("Idade: %d\n", infoAluno[i].idade);
        printf("Nascimento: %d/%d/%d\n", infoAluno[i].nascimento.dia, infoAluno[i].nascimento.mes, infoAluno[i].nascimento.ano);
        printf("Ano da matricula: %d\n", infoAluno[i].anoMatricula);
        printf("Curso: %s\n", infoAluno[i].curso);
    }
    setbuf(stdin, NULL);
    printf("Aperte ENTER para voltar ao menu\n");
    getchar();
    setbuf(stdin, NULL);
}

/**
 * @brief Coloca em ordem as matriculas a partir da idade (maior ao menor) e exibe elas
 *
 * @param infoAluno
 * @param quantidade
 */
void ordenarIdade(Aluno *infoAluno, int quantidade)
{
    Aluno trocaAluno[quantidade];

    for (int i = 0; i < quantidade; i++)
    {
        for (int j = 0; j < quantidade; j++)
        {
            if (infoAluno[j].idade < infoAluno[j].idade)
            {
                trocaAluno[i] = infoAluno[j];
            }
        }
    }
    for (int i = 0; i < quantidade; i++)
    {
        printf("\nAluno matriculado\n");
        printf("Nome: %s\n", trocaAluno[i].nome);
        printf("Idade: %d\n", trocaAluno[i].idade);
        printf("Nascimento: %d/%d/%d\n", trocaAluno[i].nascimento.dia, trocaAluno[i].nascimento.mes, trocaAluno[i].nascimento.ano);
        printf("Ano da matricula: %d\n", trocaAluno[i].anoMatricula);
        printf("Curso: %s\n", trocaAluno[i].curso);
        setbuf(stdin, NULL);
    }
    printf("Aperte ENTER para voltar ao menu\n");
    getchar();
    setbuf(stdin, NULL);
}

/**
 * @brief Coloca em ordem as matriculas a partir do ano da matricula (mais recente ao mais antigo) e exibe
 *
 * @param infoAluno
 * @param quantidade
 */
void ordenarMatricula(Aluno *infoAluno, int quantidade)
{
    Aluno trocaAluno[quantidade];

    for (int i = 0; i < quantidade; i++)
    {
        for (int j = 0; j < quantidade; j++)
        {
            if (infoAluno[i].anoMatricula < infoAluno[j].anoMatricula)
            {
                trocaAluno[i] = infoAluno[j];
            }
        }
    }
    for (int i = 0; i < quantidade; i++)
    {
        printf("\nAluno matriculado\n");
        printf("Nome: %s\n", trocaAluno[i].nome);
        printf("Idade: %d\n", trocaAluno[i].idade);
        printf("Nascimento: %d/%d/%d\n", trocaAluno[i].nascimento.dia, trocaAluno[i].nascimento.mes, trocaAluno[i].nascimento.ano);
        printf("Ano da matricula: %d\n", trocaAluno[i].anoMatricula);
        printf("Curso: %s\n", trocaAluno[i].curso);
        setbuf(stdin, NULL);
    }
    printf("Aperte ENTER para voltar ao menu\n");
    getchar();
    setbuf(stdin, NULL);
}

/**
 * @brief Faz a busca por uma matricula do sistema pelo numero dela
 *
 * @param infoAluno
 * @param idAluno
 * @param quantidade
 */


int main()
{
    Aluno* infoAluno;
    int opcao = 0;
    int quantidade;
    int numeroId;
    infoAluno = (Aluno*) calloc(MAX, sizeof(Aluno));
    do
    {
        printf("\nColegio Castaldi\nGerenciador de matricula\n");
        printf("\n");
        printf("Menu Inicial\n");
        printf("1 - Inserir matricula\n2 - Remover matricula\n3 - Listar matriculas\n4 - Pesquisar matricula\n5 - Sair do programa\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("\nDigite quantas matriculas deseja inserir no sistema: ");
            scanf("%d", &quantidade);
            inserirMatricula(infoAluno, quantidade);
            break;
        case 2:
            printf("Digite o numero da matricula que deseja excluir: ");
            scanf("%d", &numeroId);
            excluirMatricula(infoAluno, numeroId, quantidade);
        break;
        case 3:
            printf("1 - Listar todas\n2 - Ordenar por idade\n3 - Ordenar por ano de matricula\n");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 1:
                listarMatriculas(infoAluno);
                break;
            // case 2:
            //     ordenarIdade(infoAluno, &quantidade);
            //     break;
            // case 3:
            //     ordenarMatricula(infoAluno, &quantidade);
            //     break;
            // default:
            //     printf("Opcao invalida\n");
            //     break;
            }
        break;
        case 4:
            printf("Digite o numero da matricula que deseja pesquisar: ");
            scanf("%d", &numeroId);
            //pesquisarMatricula(infoAluno, numeroId, quantidade);
        break;
        case 5:
            printf("Saindo do programa...\n");
        default:
            printf("Opcao invalida\n");
            break;
        }
    } while (opcao != 5);

    return 0;
}