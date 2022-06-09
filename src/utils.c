#include <utils.h>

#define BUFFER_SIZE 32

/* Faz a leitura de uma sequência de caracteres até achar o caracter de parada ou '\n' ou EOF.
 * Durante a leitura, suprime o '\r' caso houver.
 * Aloca em blocos de tamanho BUFFER_SIZE.
 * Caso encontre o EOF, altera 'fimArquivo' para true
 * Adiciona o '\0' no final da string criada.
 * Retorna a string.
 */
char *lerString(FILE *f, char parada) {
    char *linha = NULL, tmp;
    int cont = 0;

    do {
        tmp = getc(f);
        if (tmp == '\r') tmp = getc(f);

        if (cont % BUFFER_SIZE == 0) // Aloca em blocos de tamanho BUFFER_SIZE
            linha = realloc(linha, sizeof(char) * (cont + BUFFER_SIZE));

        if (tmp == parada) break;

        if ((tmp != '\n') && (tmp != EOF))
            linha[cont++] = tmp;

    } while ((tmp != '\n') && (tmp != EOF));

    linha[cont] = '\0';

    return linha;
}