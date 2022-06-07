#ifndef CSVFILE_H
#define CSVFILE_H

#include <stdio.h>

FILE *openCSV();
void writeLineFile(FILE *f, char *line);
char *headerCSV();
void fillCSV(char **nameList);

#endif