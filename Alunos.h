typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    int idAluno;
    char nome[51];
    int idade;
    char cidade[31];
    Data nascimento;
} Aluno;

FILE *abrirArqAluno(char nome[], Aluno infoAluno[]);
int inserirAluno(Aluno infoAluno[], int quantidade, int total[]);
void removerAluno(Aluno infoAluno[], char nome[], int id, int total[]);
void listarAlunos(Aluno infoAluno[], int total[]);
FILE *salvarArqAluno(FILE *arq, Aluno alunos[], int total[]);


