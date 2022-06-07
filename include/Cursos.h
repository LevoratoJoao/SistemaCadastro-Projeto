typedef struct
{
    int idCurso;
    char nome[51];
    char periodo[11];
    int duracao;
} Curso;

FILE *abrirArqCurso(char nome[], Curso infoCurso[]);
Curso *inserirCurso(Curso infoCurso[], int quantidade, int total[]);
int removerCurso(Curso infoCurso[], char nome[], int id, int total[]);
int pesquisarCurso(Curso infoCurso[], char nome[], int id, int total[]);
void alterarCurso(Curso infoCurso[], char nome[], int id, int total[]);
void listarCursos(Curso infoCurso[], int total[]);
FILE *salvarArqCurso(FILE *arq, Curso cursos[], int total[]);