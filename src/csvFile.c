#include <csvFile.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *openCSV() {
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

char *headerCSV() {
    char *defaultHeader = strdup("alunos,cursos\n");

    return defaultHeader;
}

void fillCSV(char **nameList) {
    FILE *f = openCSV();

    if (f == NULL) return;

    writeLineFile(f, headerCSV());

    for (int i = 0; i < 10; i++) {
        writeLineFile(f, nameList[i]);
    }

    fclose(f);
}

