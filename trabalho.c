#include <stdio.h>
#include <string.h>
#define TAMNOME 50
#define TAMSOBRENOME 50


typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct registro
{
    char nome[TAMNOME];
    char sobrenome[TAMSOBRENOME];

    data data_de_nascimento;
    
    long int prontuario;
    char curso[4];

} aluno;


void cadastrarAlunos(aluno alunos[], int index)
{
  setbuf(stdin, NULL);//limpa o buffer para a entrada de stings
  printf("\nINSIRA OS DADOS DO ALUNO!\n");
  
  setbuf(stdin, NULL);
  printf("Nome: ");
  fgets(alunos[index].nome, 50, stdin);
  
  setbuf(stdin, NULL);
  printf("Sobrenome: ");
  fgets(alunos[index].sobrenome, 50, stdin);

  printf("Data de Nascimento:\n");
  printf("Dia: ");
  scanf("%d", &alunos[index].data_de_nascimento.dia);
  printf("Mês: ");
  scanf("%d", &alunos[index].data_de_nascimento.mes);
  printf("Ano: ");scanf("%d", &alunos[index].data_de_nascimento.ano);

  printf("Prontuário: ");
  scanf("%ld", &alunos[index].prontuario);

  setbuf(stdin, NULL);
  printf("Curso: ");
  fgets(alunos[index].curso, 50, stdin);
  
}

void listarAlunos(aluno alunos[], int index)
{
  int i;

  printf("\nALUNOS REGISTRADOS:\n");
  for(i = 0; i < index; i++)
  {
    //a saída dos nomes está vindo com o ENTER
    printf("\nNome: %s %s", alunos[i].nome, alunos[i].sobrenome);
    printf("\nData de Nascimento: %d/%d/%d", alunos[i].data_de_nascimento.dia, alunos[i].data_de_nascimento.mes, alunos[i].data_de_nascimento.ano);
    printf("\nProntuário: %ld", alunos[i].prontuario);
    printf("\nCurso: %s", alunos[i].curso);
  }
}

void buscaOrdenada(void)
{

}

void listagemOrdenada(void)
{

}

int main()
{

    int escolha;
    int cont_alunos = 0; //passada como parâmetro para cadastrar alunos na matriz
    aluno alunos[1000];

    printf("\nCADASTRO DE ALUNOS!\n");

    do
    {
        printf("\nEscolha uma opção:\n");
        printf("[ 1 ] - Cadastrar aluno\n");
        printf("[ 2 ] - Listar alunos\n");
        printf("[ 3 ] - Busca Ordenada\n");
        printf("[ 4 ] - Listagem Ordenada\n");
        printf("[ 5 ] - Sair\n");
        printf("Entre com a opção correspondente ao item desejado: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1: cadastrarAlunos(alunos, cont_alunos);
            cont_alunos++;//muda a var toda vez que um aluno é cadastrado
            break;
        case 2: listarAlunos(alunos, cont_alunos);
            break;
        case 3: buscaOrdenada();
            break;
        case 4: listagemOrdenada();
            break;
        default: return 0;
            break;
        }

    } while ( escolha != 3 );
    
  return 0;
}
