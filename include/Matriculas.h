#ifndef MATRICULAS_H
#define MATRICULAS_H
#include "Alunos.h"
#include "Cursos.h"

typedef struct
{
    int idMatricula;
    Aluno aluno;
    Curso curso;
    int anoMatricula;
    float coeficiente;
    int semestre;
} Matricula;

FILE *abrirArqMatricula(char *nome);
Matricula *getMatricula(FILE *arquivo, int *total);
Matricula *inserirMatricula(Matricula *matriculas, Aluno *alunos, Curso *cursos, int *totalMatriculas, int *totalAlunos, int *totalCursos);
int removerMatricula(Matricula *matriculas, int id, int *total);
int pesquisarMatricula(Matricula *matriculas, int id, int total);
void alterarMatricula(Matricula *matriculas, int id, int total, Aluno *alunos, Curso *cursos, int *totalAlunos, int *totalCursos);
void listarMatriculas(Matricula *matriculas, int total);
FILE *salvarArqMatricula(FILE *arq, Matricula *matriculas, int *total);
void exportarMatriculas(Matricula *matriculas, int total);

#endif
