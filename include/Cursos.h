#ifndef CURSOS_H
#define CURSOS_H

typedef struct
{
    int idCurso;
    char nome[51];
    char periodo[11];
    int duracao;
} Curso;

FILE *abrirArqCurso(char *nome);
Curso *getCursos(FILE *arquivo, int *total);
Curso *inserirCurso(Curso *cursos, int *total);
int removerCurso(Curso *cursos, char *nome, int id, int total);
int pesquisarCurso(Curso *cursos, char *nome, int id, int total);
void alterarCurso(Curso *cursos, char *nome, int id, int total);
void listarCursos(Curso *cursos, int total);
FILE *salvarArqCurso(FILE *arq, Curso *cursos, int *total);
void exportarCursos(Curso *alunos, int total);

#endif