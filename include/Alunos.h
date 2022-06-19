#ifndef ALUNOS_H
#define ALUNOS_H

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    int idAluno;
    char nome[51];
    int idade;
    char cidade[31];
    Data nascimento;
} Aluno;

FILE *abrirArqAluno(char *nome);
Aluno *getAlunos(FILE *arquivo, int *total);
Aluno *inserirAluno(Aluno *alunos, int *total);
int removerAluno(Aluno *alunos, char *nome, int id, int *total);
int pesquisarAluno(Aluno *alunos, char *nome, int id, int total);
void alterarAluno(Aluno *alunos, char *nome, int id, int total);
void listarAlunos(Aluno *alunos, int total);
FILE *salvarArqAluno(FILE *arq, Aluno *alunos, int *total);


#endif