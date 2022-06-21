#ifndef CSVFILE_H
#define CSVFILE_H

#include <stdio.h>
#include <Alunos.h>

FILE *openCSValunos();
void writeLineFile(FILE *f, char *line);
void writeLineFileAluno(FILE *f, Aluno *line, int total);
char *headerCSValunos();
void fillCSValunos(Aluno *nameList, int total);

#endif