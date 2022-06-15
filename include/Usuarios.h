typedef struct
{
    char nome[31];
    char senha[31];
} User;

FILE *abrirArqUser(char nome[], User usuario[]);
void cadastrarUser(User usuario[]);
int logarUser(User usuario[]);
