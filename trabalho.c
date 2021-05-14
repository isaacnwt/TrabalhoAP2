#include <stdio.h>
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
    
    int prontuarios;
    char curso[4];

} aluno;

void main()
{

    int escolha;
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
        printf("Entre com a opção correspondente ao item desejado:");
        scanf("%d", &escolha);

    } while ( escolha != 3 );

    switch (escolha)
    {
    case 1: cadastrarAlunos();
        break;
    case 2: listarAlunos();
        break;
    case 3: buscaOrdenada();
        break;
    case 4: listagemOrdenada();
        break;
    case 5: 
    
    default:
        break;
    }

}

void cadastrarAlunos(void)
{

}

void listarAlunos(void)
{

}

void buscaOrdenada(void)
{

}

void listagemOrdenada(void)
{

}