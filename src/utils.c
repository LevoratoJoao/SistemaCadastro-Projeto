#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

#define TAMANHO 10

/* Faz a leitura de uma sequência de caracteres até achar o caracter de parada ou '\n' ou EOF.
 * Durante a leitura, suprime o '\r' caso houver.
 * Aloca em blocos de tamanho TAMANHO.
 * Caso encontre o EOF, altera 'fimArquivo' para verdadeiro
 * Adiciona o '\0' no final da string criada.
 * Retorna a string.
 */
char *lerString(FILE *f, char parada) {
    char *linha = NULL, tmp; //variavel temporaria
    int cont = 0; //contador

    do {
        tmp = getc(f);
        if (tmp == '\r') {
            tmp = getc(f);
        }

        if (cont % TAMANHO == 0) { // Aloca em blocos de tamanho TAMANHO
            linha = realloc(linha, sizeof(char) * (cont + TAMANHO));
        }

        if (tmp == parada) {
            break;
        }

        if ((tmp != '\n') && (tmp != EOF)) {
            linha[cont++] = tmp;
        }

    } while ((tmp != '\n') && (tmp != EOF));

    linha[cont] = '\0';

    return linha;
}

char *getUserInput() {
    char *input = lerString(stdin, '\n');

    return input;
}