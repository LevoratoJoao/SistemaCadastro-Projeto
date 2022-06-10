typedef struct
{
    char usuario[31];
    char senha[31];
} User;

FILE *abrirArqUser(char nome[], User usuario[]);
