#include <csvFile.h>
#include <Alunos.h>
#include <Cursos.h>
#include <Matriculas.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *openCSValunos() {
    FILE *f = fopen("alunos.csv", "w+");

    if (f == NULL) return NULL;

    return f;
}

void writeLineFile(FILE *f, char *line) {
    if (f == NULL)  {
        free(line);
        return;
    }

    fwrite(line, sizeof(char), strlen(line), f);
    free(line);
}

void writeLineFileAluno(FILE *f, Aluno *line, int total) {
    if (f == NULL)  {
        free(line);
        return;
    }
    for (int i = 0; i < total; i++)
    {
        fwrite(&line[i], sizeof(Aluno), 1, f);
    }

    free(line);
}

char *headerCSValunos() {
    char *defaultHeader = strdup("id,nome,idade,cidade,dia,mes,ano\n");

    return defaultHeader;
}

void fillCSValunos(Aluno *nameList, int total) {
    FILE *f = openCSValunos();

    if (f == NULL) return;

    writeLineFile(f, headerCSValunos());


    writeLineFileAluno(f, nameList, total);


    fclose(f);
}

