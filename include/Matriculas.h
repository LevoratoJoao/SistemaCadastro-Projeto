#ifndef MATRICULAS_H
#define MATRICULAS_H
#include "Alunos.h"
#include "Cursos.h"

typedef struct
{
    int idMatricula;
    Aluno idAluno;
    Curso idCurso;
    int anoMatricula;
    float coeficiente;
    int semestre;
} Matricula;

FILE *abrirArqMatricula(char *nome);
Matricula *getMatricula(FILE *arquivo, int *total);
Matricula *inserirMatricula(Matricula *matriculas, int *total);
int removerMatricula(Matricula *matriculas, char *nome, int id, int total);
int pesquisarMatricula(Matricula *matriculas, char *nome, int id, int total);
void alterarMatricula(Matricula *matriculas, char *nome, int id, int total);
void listarMatriculas(Matricula *matriculas, int total);
FILE *salvarArqMatricula(FILE *arq, Matricula *matriculas, int *total);

#endif
