# SistemaCadastro-Projeto
Sistema de Cadastro - Projeto desenvolvido em Fundamentos de Programação 2

O tema do nosso projeto foi de um sistema de cadastro escolar, nele é possivel cadastrar um aluno, curso e uma matrícula.
### Makefile
```
make
make run
make valgrind
```
Foi criado um makefile para facilitar a execução de todos os arquivos .c do projeto e o valgrind para localizar memória desperdiçada durante a execução

## Aarquivos e Funções
### - User
  No projeto utilizamos um sistema de login de usuário, caso não tenha nenhuma data-base de usuarios é criado um arquivo "dataUser" e um primeiro login é solicitado, as senhas são armazenadas na base de dados de forma criptografada utilizando a Cifra de César mas para logar basta usar a senha normal do login que o programa irá criptografar e verificar se está correta (delete a base de dados de usuários para acessar o sistema).
Após feito o login o usuário pode cadastrar outros usuários ou entrar no sistema.

A "userInterface" é o menu inicial do sistema, nele é possivel acessar todas as base de dados presentes: Alunos, Cursos e Matriculas cada uma com sua respectiva função e opções:
- Inserir
- Remover
- Pesquisar
- Alterar
- Listar 
- Salvar os dados no arquivo da base de dados
- Exportar dados para um arquivo .csv

### - Alunos, Cursos e Matriculas
#### - Abrir arquivos e armazenar dados

  Ao entrar em uma das funções na userInterface, é aberto o arquivo onde estão salvos os dados cadastrados (se o arquivo não existir ele é criado) e armazenados nas structs, isso ocorre na função getAlunos, getCursos e getMatriculas que percorre o arquivo todo e sempre que for necessario realoca memoria para o vetor das structs, dessa forma podemos armazenar todos os dados presentes nos arquivos nas variaveis.

#### - Inserir

  Nessas funções é feita uma busca nas structs procurando id = 0 que significa que aquela posição está vazia e pode ser inserido dados nela, se após percorrer todo o vetor e não tiver nenhuma posição vazia o vetor passa por um realloc que realoca mais 10 de espaço na memória.
  
  É feita uma verificação de se os dados inseridos pelo usuários são validos, por exemplo: se caso algum dos campos estiver em branco ou com números negativos o usuário devera preencher novamente. Em matrículas as structs conversam entre si, para inserir uma matrícula é necessário informar o id do aluno e o id do curso, após isso é feita uma verificação de se o curso ou o aluno estão registrado no sistema, se estiver todos os dados são associados a matrícula, se não é iformado ao usuário retornado ao menu inicial do sistema.
  
  Ao final é perguntado se o usuário quer inserir mais, se sim o loop contínua, se não é retornado ao menu.
 
#### - Remover

  Nas funções de remoção o usuário deve informar o nome ou id do curso/aluno (para matrículas é o id da matrícula ou id do aluno) e é necessário uma confirmação para remoção dos dados, se confirmar todos os dados são removidos da memória, se não a operação é finalizada e retonar para o menu.
  
#### - Pesquisar

  Nas funções de pesquisar é preciso informar o id ou nome do curso/aluno (para matrículas é o id da matrícula ou id do aluno), a função percorre todo o vetor verificando se o que o usuário deseja buscar está no sistema, caso encontre é mostrado as informações do mesmo e se caso não encontre é infformado que não foi encontrado e retornado ao menu.

#### - Alterar

   Deve ser digitado o id ou nome do curso/aluno, após encontrar os dados desejados o usuário podera fazer alterações em todos os campos da struct com excessão do id, em matrículas as alterações em alunos e cursos são feitas apenas pelo id dos mesmos, ou seja, se caso deseja alterar alguma informação de aluno dentro da matrícula deverá alterar o id do aluno, campos específicos não é possível.
   
#### - Listar

   Lista todos os dados de acordo comm a base de dados que o usuário esta.
    
#### - Salvar

   Salva os dados da memória nos arquivos de base de dados, estes arquivos são arquivos bínarios .dat. É importante lembrar que qualquer operação feita no sistema seja ela remoção, alteração ou inserção de dados deve ser salvo, caso não seja ao sair das funções de Alunos, Cursos ou Matriculas e voltar ao mmenu inicial os dados serão perdidos.
   
#### - Exportar dados

   Exporta os dados para um arquivo .csv
   
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  Todas as opções do menu que o usuário digitar no programa passam por uma função de verificação chamada utils.c, nela é passado o input do usuário que é alocado dinamicamente com o realloc, dessa forma qualquer coisa que for digitada será lida, armazenada e verificada se é valida.
  
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Atualizações futuras:
```
- Opções de usuáio (alterar senha, remover usuário, etc...)
- Ordenar listagem (ordem alfabética, idade, etc...)
- Impedir usuário de tentar excluir os dados de um aluno ou curso que estão vinculados a uma matrícula.
- Ao alterar dados de alunos e cursos eles já serem alterados automaticamente na mmatrícula.
```
