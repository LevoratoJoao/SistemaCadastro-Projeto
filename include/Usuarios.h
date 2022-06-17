typedef struct
{
    char nome[31];
    char senha[31];
} User;

FILE *abrirArqUser(char *nome);
User *getUsers(FILE *arqUser, int *total);
User *cadastrarUser(User *usuario, int *total);
int logarUser(User *usuario, int *total);
