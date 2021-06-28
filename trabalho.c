#define QUANTIDADE_ALUNOS 1000
#define SOBRENOME 50
#define NOME 50

#include <stdio.h>
#include <string.h>

typedef struct data
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct aluno
{
    char nome[NOME];
    char sobrenome[SOBRENOME];

    data data_de_nascimento;
    
    long int prontuario;
    char     curso[4];

} aluno;

// cabeçalho de todas (com excessão da main) as funções do programa
void  atualizaArquivo(aluno alunos[]);
void  carregaArquivo(aluno alunos[]);
aluno inicializaLista(aluno alunos[]);
int   localizaUltimaPosicao(aluno alunos[]);
void  cadastrarAlunos();
void  listarAlunos(aluno alunos[]);
void  buscaOrdenada(aluno alunos[]);
void  buscaNomeSobrenome(aluno alunos[]);
void  mostraInfo(aluno alunos[], int i);
void  mostraInfoSobrenome(aluno alunos[], int i);
void  mostraInfoData(aluno alunos[], int i);
void  mostraInfoProntuario(aluno alunos[], int i);
void  mostraInfoCurso(aluno alunos[], int i);
void  buscaNome(aluno alunos[]);
void  buscaSobrenome(aluno alunos[]);
void  buscaProntuario(aluno alunos[]);
void  buscaNascimento(aluno alunos[]);
void  buscaCurso(aluno alunos[]);
void  apagarDados(aluno alunos[]);
void  confirmaApagarDados(aluno alunos[]);
void  marcarNome(aluno alunos[], int i);
void  listagemOrdenada(aluno alunos[]);
void  organizaPorTipo(aluno alunos[], int tipo);
int   menuOrdenacao();
void  selectionSort(aluno alunos[], int tipo );
void  setaTipoOrdenacao(aluno alunos[], int escolha, int tipo);
void  trocaPosicao(aluno *posicao1, aluno *posicao2);
void  mergeSort(aluno alunos[], int ini, int fim, int tipo);
void  intercalar(aluno alunos[], int ini, int meio, int fim, int tipo);
void  insertionSort(aluno alunos[], int tipo);
int   localizaPosicao(aluno alunos[], int ultimo, aluno elemento, int tipo);
void  deslocaSubVetor(aluno alunos[], int posicao, int ultimo);
int   verificaOrdenacao(aluno alunos[], int tipo);
void  buscaPorTipo(aluno alunos[], int tipo);
void  quickSort(aluno alunos[], int ini, int fim, int tipo);
int   particionar(aluno alunos[], int ini, int fim, int tipo);



void main()
{

    int   escolha;  // variável que recebe opção escolhido pelo usuário
    aluno alunos[QUANTIDADE_ALUNOS]; // vetor do tipo struct aluno
    inicializaLista(alunos); // função que inicializa todos os nomes do vetor alunos[]

    printf("\nFICHA INFORMACIONAL DE ALUNOS\n");
    do
    {
        printf("\nEscolha uma opcao:\n");
        printf("[ 1 ] - Cadastrar aluno\n");
        printf("[ 2 ] - Listar alunos\n");
        printf("[ 3 ] - Busca Ordenada\n");
        printf("[ 4 ] - Listagem Ordenada\n");
        printf("[ 5 ] - Sair\n");
        printf("Entre com a opcao correspondente ao item desejado: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1: cadastrarAlunos(alunos); break;
        case 2: listarAlunos(alunos);    break;
        case 3: buscaOrdenada(alunos);   break;
        case 4: listagemOrdenada(alunos);break;
        case 5: break;
        default: printf("\nErro! Opcao invalida.\n");
        }

    } while ( escolha != 5 );
    
}


// -------------------------------- ESPAÇO DAS ROTINAS -------------------------------------- //  


/* ===========================================================================================*/

/* ========================= rotinas para salvar e carregar dados ============================*/

/* ===========================================================================================*/

void atualizaArquivo(aluno alunos[])
{
    // esta função atualiza o arquivo na memória secundária

    FILE *ponteiro_arquivo; // cria ponteiro para a localização do arquivo
    int   i, resultado; // variável 'resultado' recebe um valor de tipo inteiro que indica sucesso ou falha ao ler ou gravar o arquivo

    ponteiro_arquivo = fopen("arquivo_cadastro", "wb"); // o arquivo é aberto em modo escrita, isto significa que apagará todos os dados contidos no arquivo original. Mas não é um problema porque os dados estão contidos de forma atualizada no vetor alunos[] de tipo aluno.

    if ( !ponteiro_arquivo ) // quando função fopen retorna 0, é indicação de falha na abertura do arquivo
    {
        printf("O arquivo não pode ser aberto.\n");
        return; // a função é encerrada sem atualizar o arquivo, podendo perder todos os dados salvos
    }

    rewind(ponteiro_arquivo); // rewind() reinicia o ponteiro de leitura dentro do arquivo, é necessário pois toda vez que for feita leituras no arquivos, foi estruturado para ler desde o início

    for( i=0 ; i<QUANTIDADE_ALUNOS ; i++ ) 
    {
        // strcmp retorna não 0 para valores diferentes
        if(strcmp(alunos[i].nome, ""))
        {
            // a string "" indica um indice vazio, logo não será salvo no arquivo
            resultado = fwrite(&alunos[i], sizeof(aluno), 1, ponteiro_arquivo);
            // quando função fwrite retorna 0, é indicação de falha na abertura do arquivo
            if (!resultado)
            {
                printf("\nErro de escrita no arquivo.\n");
                fclose(ponteiro_arquivo);
                return;
            }
        }
    }
    fclose(ponteiro_arquivo);
}

void carregaArquivo(aluno alunos[])
{
    // esta função carrega o arquivo na memória secundária em um struct de tipo aluno

    FILE *ponteiro_arquivo; // cria ponteiro para a localização do arquivo
    int   i, resultado; // variável 'resultado' recebe um valor de tipo inteiro que indica sucesso ou falha ao ler ou gravar o arquivo

    ponteiro_arquivo = fopen("arquivo_cadastro", "rb"); // o arquivo é aberto em modo leitura

    if ( !ponteiro_arquivo ) // quando função fopen retorna 0, é indicação de falha na abertura do arquivo
    {
        printf("\n\nErro! O arquivo ainda não foi criado\n\n");
        return;
    } 

    rewind(ponteiro_arquivo);  // rewind() reinicia o ponteiro de leitura dentro do arquivo, é necessário pois toda vez que for feita leituras no arquivos, foi estruturado para ler desde o início

    for( i=0 ; i<QUANTIDADE_ALUNOS ; i++ )
    {
        resultado = fread(&alunos[i], sizeof(aluno), 1, ponteiro_arquivo);

        // quando função fread retorna 0, é indicação de falha na abertura do arquivo
        if (!resultado)
        {   
            // pode ter dado falha por ter chegado ao final do arquivo
            // feof() retorna 0 se ainda existir dados, se não for o caso, então houve erro na leitura deste dado
            // caso retorne diferente de 0, então o erro do primeiro if foi causado por ter chegado ao final do arquivo. 
            if ( feof(ponteiro_arquivo) )
            {   
                // se for isso, apenas damos um break e saimos da função
                break;
            }
            printf("\n\nErro de leitura no arquivo.\n\n");
        }
    }
    fclose(ponteiro_arquivo);
}



/* ===========================================================================================*/

/* ===========================    rotinas  OPERACIONAIS    ===================================*/

/* ===========================================================================================*/

int localizaUltimaPosicao(aluno alunos[])
{
    // esta função localiza a última posição em que há um aluno cadastrado no vetor alunos[]
    // retorna na variável 'index' o indice dessa posição. 
    int i, index;
    for( i=0, index=0 ; i<QUANTIDADE_ALUNOS ; i++ )
    {
        if( strcmp(alunos[i].nome, "") != 0 )
        {
            index++;
        }
    } 
    // variável 'index' contendo a primeira ocorrência da string "", que indica o primeiro indice vazio para armazenar mais um aluno
    return index;
}

void mostraInfo(aluno alunos[], int i)
{
    // esta função mostra as informação do aluno passado por parâmetro.
    
    printf("\nAluno ----   %d   ---- ", i+1);
    printf("\nNome.........: %s", alunos[i].nome);
    printf("\nSobrenome....: %s", alunos[i].sobrenome);
    printf("\nNascimento...: %d/%d/%d", alunos[i].data_de_nascimento.dia, alunos[i].data_de_nascimento.mes, alunos[i].data_de_nascimento.ano);
    printf("\nProntuario...: %ld", alunos[i].prontuario);
    printf("\nCurso........: %s\n", alunos[i].curso);
}

void marcarNome(aluno alunos[], int i)
{
    // função responsavel por 'marcar' os itens que serão deletados caso o usuário queira
    // strcpy copia a segunda string, para a posição da primeira string
    // como essa lista é temporária, alunos[].nome com "deletar" só ficará enquanto a lista tiver dentro da função que chamar esta

    strcpy(alunos[i].nome, "deletar");
}

void confirmaApagarDados(aluno alunos[])
{
    // função responsável por CONFIRMAR se o usuário quer apagar os dados listados na busca ordenada

    int resposta;
    printf("\nGostaria de remover da lista os itens listados?");
    printf("\n[ 1 ] - SIM");
    printf("\n[ 2 ] - NAO");
    printf("\nDigite o numero correspondente ao item desejado:");
    scanf("%d", &resposta);
    if( resposta == 1 )
    {
        apagarDados(alunos); // apaga os dados que estiverm marcados como 'deletas pela função marcarNome()
        atualizaArquivo(alunos); // atualiza o arquivo na memória secundária com a nova lista atualizada
        printf("\nLISTA ATUALIZADA\n");
    }
}

void apagarDados(aluno alunos[])
{
    // função reponsável apagar os dados e reorganizar o vetor
    // para apagar um item de vetor, é necessário substituir o item desejado pelo seu sucessor
    // e o sucessor pelo sucessor, e por assim em diante até o final do vetor

    int i, j;
    // laço que percorre toda o vetor de alunos carregado na memória principal
    for( i=0 ; i<QUANTIDADE_ALUNOS ; i++ )
    {
        // se for achar um aluno marcado como 'deletar', então entra no if para fazer a operação
        if( !(strcmp(alunos[i].nome, "deletar"))) 
        {
            // 'j' recebe o indice que contém o item para deletar
            // o laço irá até a última posição do vetor (que contem alunos gravados)
            for( j=i ; j<localizaUltimaPosicao(alunos) ; j++ )
            {
                // aqui estamos substituindo o item desejado pelo seu sucessor
                // fazemos isso até o final da lista
                alunos[j] = alunos[j+1];
            }
            // após fazer uma operação de deletar, retornamos um indice do laço externo
            // desta forma não ocorre de pular um indice do vetor
            // pois pode acontecer de ter de apagar dois itens em sequência
            i--;
        }
    }
}

aluno inicializaLista(aluno alunos[])
{
    // esta função inicializa o vetor alunos[] colocando a string "" em todos os nomes do vetor
    // desta forma é possível localizar a última posição em que há alunos cadastrados 
    int i;
    for( i=0 ; i<QUANTIDADE_ALUNOS ; i++ )
    {
        strcpy(alunos[i].nome, "");
    }
}

void trocaPosicao(aluno *posicao1, aluno *posicao2)
{
    aluno aluno_aux = *posicao1;
    *posicao1 = *posicao2;
    *posicao2 = aluno_aux;
}

int verificaOrdenacao(aluno alunos[], int tipo)
{
    carregaArquivo(alunos);
    int index = localizaUltimaPosicao(alunos);
    int i, contador=0;

    for( i=0 ; i<(index-1) ; i++ )
    {
        if( tipo == 1 || tipo == 2 )
        {
            if( strcmp(alunos[i].nome, alunos[i+1].nome) <= 0 ) contador++;
        }
        else if ( tipo == 3 )
        {
            if( strcmp(alunos[i].sobrenome, alunos[i+1].sobrenome) <=0 ) contador++;
        }
        else if( tipo == 4 )
        {
            if( alunos[i].prontuario <= alunos[i+1].prontuario ) contador++;
        }
        else if( tipo == 5 )
        {
            if( alunos[i].data_de_nascimento.ano < alunos[i+1].data_de_nascimento.ano ) 
            contador++;

            else if( alunos[i].data_de_nascimento.ano == alunos[i+1].data_de_nascimento.ano &&
                     alunos[i].data_de_nascimento.mes <  alunos[i+1].data_de_nascimento.mes)
                     contador++;

            else if( alunos[i].data_de_nascimento.ano == alunos[i+1].data_de_nascimento.ano &&
                     alunos[i].data_de_nascimento.mes == alunos[i+1].data_de_nascimento.mes &&
                     alunos[i].data_de_nascimento.dia <= alunos[i+1].data_de_nascimento.dia)
                     contador ++;
        }
        else if( tipo == 6 )
        {
            if( strcmp(alunos[i].curso, alunos[i+1].curso) <= 0 ) contador++;
        }
    }
    if( contador == (index - 1) ) return 1;
    else return 0;
}




/* ===========================================================================================*/

/* ==========================   rotinas para CADASTRAR alunos   ==============================*/

/* ===========================================================================================*/

void cadastrarAlunos(aluno alunos[])
{
    carregaArquivo(alunos); // carrega da memória secundária dados já gravados
    int index = localizaUltimaPosicao(alunos); 

    setbuf(stdin, NULL);//limpa o buffer para a entrada de strings
    printf("\nINSIRA OS DADOS DO ALUNO!\n");
    
    setbuf(stdin, NULL);
    printf("Primeiro nome: ");
    gets(alunos[index].nome);
    
    setbuf(stdin, NULL);
    printf("Sobrenome: ");
    gets(alunos[index].sobrenome);

    printf("Data de Nascimento:\n");
    printf("Dia: ");
    scanf("%d", &alunos[index].data_de_nascimento.dia);
    printf("Mes: ");
    scanf("%d", &alunos[index].data_de_nascimento.mes);
    printf("Ano: ");
    scanf("%d", &alunos[index].data_de_nascimento.ano);

    printf("Prontuario: ");
    scanf("%ld", &alunos[index].prontuario);

    setbuf(stdin, NULL);
    printf("Curso: ");
    gets(alunos[index].curso);

    atualizaArquivo(alunos);
}



/* ===========================================================================================*/

/* ===========================   rotinas para LISTAR alunos   ================================*/

/* ===========================================================================================*/

void listarAlunos(aluno alunos[])
{
  // esta funçaõ lista para o usuário todos os alunos cadastrados

  carregaArquivo(alunos);
  int i;
  int index = localizaUltimaPosicao(alunos);

  printf("\nALUNOS REGISTRADOS: %d\n", index);
  for(i = 0; i < index; i++)
  {
    //a saída dos nomes está vindo com o ENTER
    mostraInfo(alunos, i); // mostra as informações do aluno em questão
  }
}



/* ===========================================================================================*/

/* ===========================   rotinas para BUSCAR alunos   ================================*/

/* ===========================================================================================*/

void buscaOrdenada(aluno alunos[])
{
    // esta função organiza o sub-menu referente a buscas
    int escolha; // variável que recebe opção escolhido pelo usuário
    printf("\nBUSCA ORDENADA DE ALUNOS\n");
    do
    {
        printf("\nEscolha uma opcao:\n");
        printf("[ 1 ] - Nome e Sobrenome\n");
        printf("[ 2 ] - Nome\n");
        printf("[ 3 ] - Sobrenome\n");
        printf("[ 4 ] - Prontuario\n");
        printf("[ 5 ] - Data de nascimento\n");
        printf("[ 6 ] - Curso\n");
        printf("[ 7 ] - Voltar ao menu principal\n");
        printf("Entre com a opcao correspondente ao item desejado: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1: buscaPorTipo(alunos, 1); break;
        case 2: buscaPorTipo(alunos, 2); break;
        case 3: buscaPorTipo(alunos, 3); break;
        case 4: buscaPorTipo(alunos, 4); break;
        case 5: buscaPorTipo(alunos, 5); break;
        case 6: buscaPorTipo(alunos, 6); break;
        case 7: break;
        default: printf("\nErro! Opcao invalida.\n");
        }

    } while ( escolha != 7 );
}

void buscaPorTipo(aluno alunos[], int tipo)
{
    carregaArquivo(alunos);

    char nome[50];
    if( tipo == 2 )
    {
        printf("\nBUSCA POR NOME\n");
        printf("Digite o nome: "); fflush(stdin); gets(nome);
    }
    char sobrenome[50];
    if(tipo == 3)
    {
        printf("\nBUSCA SOBRENOME\n");
        printf("Digite o sobrenome: "); fflush(stdin); gets(sobrenome);
    }

    if(tipo == 1)
    {
        printf("\nBUSCA POR NOME E SOBRENOME\n");
        printf("Digite o nome: "); fflush(stdin); gets(nome);
        printf("Digite o sobrenome: "); fflush(stdin); gets(sobrenome);
    }

    int  prontuario;
    if( tipo == 4 )
    {
        printf("\nBUSCA POR PRONTUARIO\n"); 
        printf("Digite o prontuario: "); scanf("%d", &prontuario);
    }

    int  dia, mes, ano;
    if( tipo == 5 )
    {
        printf("\nBUSCA POR NASCIMENTO\n"); // recebe a data de nascimento desejada
        printf("Digite o dia:"); scanf("%d", &dia);
        printf("Digite o mes:"); scanf("%d", &mes);
        printf("Digite o ano:"); scanf("%d", &ano);
    }

    char curso[10];
    if( tipo == 6 )
    {
        printf("\nBUSCA POR CURSO\n");
        printf("Digite o curso: "); fflush(stdin); gets(curso);
    }

    int i, contador=0;
    int index = localizaUltimaPosicao(alunos);


    if( verificaOrdenacao(alunos, tipo))
    {
        // busca binária
    }
    else 
    {
        for( i=0 ; i<index ; i++ )
        {
            if( tipo == 1 )
            {
                if(! (strcmp(alunos[i].nome, nome) || (strcmp(alunos[i].sobrenome, sobrenome))))
                {
                    mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
                    marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
                    contador++; // conta quantos itens foram mostrados
                }
            }
            else if( tipo == 2 )
            {
                if(!(strcmp(alunos[i].nome, nome))) // strcmp retorn 0 quando os valores passados são iguais
                {
                    mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
                    marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
                    contador++; // conta quantos itens foram mostrados
                }
            }
            else if( tipo == 3 )
            {
                if(!(strcmp(alunos[i].sobrenome, sobrenome))) //strcmp retorna 0 quando os valores passados são iguais
                {
                    mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
                    marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
                    contador++; // conta quantos itens foram mostrados
                }
            }
            else if( tipo == 4 )
            {
                if( alunos[i].prontuario == prontuario ) // se achar um prontuário, então é mostrado ao usuário
                {
                    mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
                    marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
                    contador++; // conta quantos itens foram mostrados 
                }
            }
            else if( tipo == 5 )
            {
                if( (alunos[i].data_de_nascimento.dia == dia) &&
                (alunos[i].data_de_nascimento.mes == mes) &&
                (alunos[i].data_de_nascimento.ano == ano))  // apenas se as três datas forem iguais
                {
                    mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
                    marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
                    contador++; // conta quantos itens foram mostrados
                }
            }
            else if( tipo == 6 )
            {
                if( ! (strcmp(alunos[i].curso, curso))) // strcmp retorn 0 quando os valores passados são iguais
                {
                    mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
                    marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
                    contador++; // conta quantos itens foram mostrados
                }
            }
        }
        if(!contador) // se o contador tiver em 0, não foi achado nenhum resultado
        {
            printf("\nNao foi encontrado aluno com este cadastro.\n");
        } else confirmaApagarDados(alunos);
    }

}



/* ===========================================================================================*/

/* ===========================   rotinas para LISTAR alunos   ================================*/

/* ===========================================================================================*/

void listagemOrdenada(aluno alunos[])
{
    // menu para escolher o tipo de listagem desejada
    //chama a função conforme a opção escolhida
    int escolha;

    printf("\nLISTAGEM ORDENADA DE ALUNOS\n");
    do
    {
        printf("\nEscolha uma opcao:\n");
        printf("[ 1 ] - Nome e sobrenome\n");
        printf("[ 2 ] - Sobrenome e nome\n");
        printf("[ 3 ] - Data de nascimento\n");
        printf("[ 4 ] - Prontuario\n");
        printf("[ 5 ] - Curso\n");
        printf("[ 6 ] - Voltar ao menu principal\n");
        printf("Entre com a opcao correspondente ao item desejado: ");
        scanf("%d", &escolha);

        //chama a função conforme a opção escolhida
        switch (escolha)
        {
        case 1: organizaPorTipo(alunos, 1);  break;
        case 2: organizaPorTipo(alunos, 2);  break;
        case 3: organizaPorTipo(alunos, 3);  break;
        case 4: organizaPorTipo(alunos, 4);  break;
        case 5: organizaPorTipo(alunos, 5);  break;
        case 6:                              break;
        default: printf("\nErro! Opcao invalida.\n");
        }

    } while ( escolha != 6 );
}

void organizaPorTipo(aluno alunos[], int tipo)
{

    int i;
    int escolha   = menuOrdenacao();
    
    setaTipoOrdenacao(alunos, escolha, tipo);
    
    int index     = localizaUltimaPosicao(alunos);
    carregaArquivo(alunos);
    for(i = 0; i < index; i++)
    {
        //a saída dos nomes está vindo com o ENTER
        mostraInfo(alunos, i); // mostra as informações do aluno em questão
    }
}



/* ===========================================================================================*/

/* =========================   rotinas para ORDENAR vetores   ================================*/

/* ===========================================================================================*/

void setaTipoOrdenacao(aluno alunos[], int escolha, int tipo)
{
    int tam = localizaUltimaPosicao(alunos);

    if( escolha == 1 ) selectionSort(alunos, tipo);
    if( escolha == 2 ) insertionSort(alunos, tipo);
    if( escolha == 3 ) mergeSort(alunos, 0, tam, tipo);
    if( escolha == 4 ) quickSort(alunos, 0, tam, tipo);
}

int menuOrdenacao()
{
    int escolha = 0;
    do
    {
        printf("\n[ 1 ] - Ordenar por Selecao          (Selection Sort)\n");
        printf("[ 2 ] - Ordenar por Insercao         (Insertion Sort)\n");
        printf("[ 3 ] - Ordenar por Intercalacao     (Merge Sort) \n");
        printf("[ 4 ] - Ordenar por Particionamento  (Quick Sort) \n");

        printf("Digite a opcao desejada: "); scanf("%d", &escolha);

    } while ( escolha < 1 || escolha > 4 );

    return escolha;
}

void selectionSort(aluno alunos[], int tipo )
{

    carregaArquivo(alunos);
    int index = localizaUltimaPosicao(alunos);
    int i, j;
  
    for ( i = 0; i < index; i++)
    {
        for ( j = i+1; j < index; j++)
        {
            if( tipo == 1 )
            {
                if(strcmp(alunos[i].nome, alunos[j].nome) > 0)
                {
                    trocaPosicao(&alunos[i], &alunos[j]);
                }
            } 

            else 
            if( tipo == 2 )
            {
                if(strcmp(alunos[i].sobrenome, alunos[j].sobrenome) > 0)
                {    
                    trocaPosicao(&alunos[i], &alunos[j]);
                }
            }

            else
            if( tipo == 3 )
            {
                if(alunos[i].data_de_nascimento.ano > alunos[j].data_de_nascimento.ano)
                {
                    trocaPosicao(&alunos[i], &alunos[j]);
                }
            
                else if((alunos[i].data_de_nascimento.ano == alunos[j].data_de_nascimento.ano) &&
                        (alunos[i].data_de_nascimento.mes > alunos[j].data_de_nascimento.mes))
                        {
                            trocaPosicao(&alunos[i], &alunos[j]);
                        }
            
                else if((alunos[i].data_de_nascimento.ano == alunos[j].data_de_nascimento.ano) &&
                        (alunos[i].data_de_nascimento.mes == alunos[j].data_de_nascimento.mes) &&
                        (alunos[i].data_de_nascimento.dia > alunos[j].data_de_nascimento.dia))
                        {
                        trocaPosicao(&alunos[i], &alunos[j]);
                        }
            }

            else
            if( tipo == 4 )
            {
                if(alunos[i].prontuario > alunos[j].prontuario)
                {
                    trocaPosicao(&alunos[i], &alunos[j]);
                }
            }

            else
            if( tipo == 5 )
            {
                if(strcmp(alunos[i].curso, alunos[j].curso) > 0)
                {
                    trocaPosicao(&alunos[i], &alunos[j]);
                }
            }
        }
    }
    atualizaArquivo(alunos);
}

void mergeSort(aluno alunos[], int ini, int fim, int tipo)
{   
    carregaArquivo(alunos);
    int meio;

    if (ini < fim)
    {
        meio = (ini + fim)/2;
        mergeSort(alunos, ini, meio, tipo);
        mergeSort(alunos, meio+1, fim, tipo);
        intercalar(alunos, ini, meio, fim, tipo);
    }
    
    atualizaArquivo(alunos);
}

void intercalar(aluno alunos[], int ini, int meio, int fim, int tipo)
{
    aluno aux[QUANTIDADE_ALUNOS];
    int i = ini;
    int j = meio + 1;
    int k = 0; // marca a posição que é colocado os valores em aux
    
    if ( tipo == 1 )
    {
        while (i <= meio && j <= fim)
        {
            if (strcmp(alunos[i].nome, alunos[j].nome) <= 0)
                aux[k++] = alunos[i++];
            else
                aux[k++] = alunos[j++];
        }

        while (i <= meio)
            aux[k++] = alunos[i++];
        while (j <= fim)
            aux[k++] = alunos[j++];

        for(i = ini, k = 0; i <= fim; i++, k++)
            alunos[i] = aux[k];
    }
    if ( tipo == 2 )
    {
        while (i <= meio && j <= fim)
        {
            if (strcmp(alunos[i].sobrenome, alunos[j].sobrenome) <= 0)
                aux[k++] = alunos[i++];
            else
                aux[k++] = alunos[j++];
        }

        while (i <= meio)
            aux[k++] = alunos[i++];
        while (j <= fim)
            aux[k++] = alunos[j++];

        for(i = ini, k = 0; i <= fim; i++, k++)
            alunos[i] = aux[k];
    }
    if ( tipo == 3 )
    {
        while (i <= meio && j <= fim)
        {
            if(alunos[i].data_de_nascimento.ano < alunos[j].data_de_nascimento.ano){ aux[k++] = alunos[i++];}

            else if((alunos[i].data_de_nascimento.ano == alunos[j].data_de_nascimento.ano) &&
                    (alunos[i].data_de_nascimento.mes < alunos[j].data_de_nascimento.mes)){ aux[k++] = alunos[i++];}

            else if((alunos[i].data_de_nascimento.ano == alunos[j].data_de_nascimento.ano) &&
                    (alunos[i].data_de_nascimento.mes == alunos[j].data_de_nascimento.mes) &&
                    (alunos[i].data_de_nascimento.dia < alunos[j].data_de_nascimento.dia)){ aux[k++] = alunos[i++];}
            else
                aux[k++] = alunos[j++];
        }

        while (i <= meio)
            aux[k++] = alunos[i++];
        while (j <= fim)
            aux[k++] = alunos[j++];

        for(i = ini, k = 0; i <= fim; i++, k++)
            alunos[i] = aux[k];
    }
    if ( tipo == 4 )
    {
        while (i <= meio && j <= fim)
        {
            if (alunos[i].prontuario <= alunos[j].prontuario)
                aux[k++] = alunos[i++];
            else
                aux[k++] = alunos[j++];
        }

        while (i <= meio)
            aux[k++] = alunos[i++];
        while (j <= fim)
            aux[k++] = alunos[j++];

        for(i = ini, k = 0; i <= fim; i++, k++)
            alunos[i] = aux[k];
    }
    if ( tipo == 5 )
    {
        while (i <= meio && j <= fim)
        {
            if (strcmp(alunos[i].curso, alunos[j].curso) <= 0)
                aux[k++] = alunos[i++];
            else
                aux[k++] = alunos[j++];
        }

        while (i <= meio)
            aux[k++] = alunos[i++];
        while (j <= fim)
            aux[k++] = alunos[j++];

        for(i = ini, k = 0; i <= fim; i++, k++)
            alunos[i] = aux[k];
    }
    
}

void insertionSort(aluno alunos[], int tipo)
{
    carregaArquivo(alunos);
    int i, posicao;
    aluno elemento;

    for( i=1 ; i<localizaUltimaPosicao(alunos) ; i++ )
    {
        elemento = alunos[i];
        posicao  = localizaPosicao(alunos, i-1, elemento, tipo);
        deslocaSubVetor(alunos, posicao, i);
        alunos[posicao] = elemento;
        atualizaArquivo(alunos);
    }
}

int localizaPosicao(aluno alunos[], int ultimo, aluno elemento, int tipo)
{
    int i;
    for( i=0 ; i<=ultimo ; i++ )
    {
        if (tipo == 1)
        {   
            if( strcmp(elemento.nome, alunos[i].nome) < 0 )
            {
                return i;
            }
        } 

        else if (tipo == 2)
        {
            if( strcmp(elemento.sobrenome, alunos[i].sobrenome) < 0 ) return i;
        } 

        else if (tipo == 3)
        {
            if( elemento.data_de_nascimento.ano < alunos[i].data_de_nascimento.ano )
                return i;

            else if((elemento.data_de_nascimento.ano == alunos[i].data_de_nascimento.ano) &&
                    (elemento.data_de_nascimento.mes < alunos[i].data_de_nascimento.mes))
                        return i;

            else if((elemento.data_de_nascimento.ano == alunos[i].data_de_nascimento.ano) &&
                    (elemento.data_de_nascimento.mes == alunos[i].data_de_nascimento.mes) &&
                    (elemento.data_de_nascimento.dia < alunos[i].data_de_nascimento.dia)) 
                        return i;
        } 

        else if (tipo == 4)
        {
            if( elemento.prontuario < alunos[i].prontuario ) return i;
        } 

        else if (tipo == 5)
        {
            if( strcmp(elemento.curso, alunos[i].curso ) < 0 ) return i;
        }        
    }
    return i;
}

void deslocaSubVetor(aluno alunos[], int posicao, int ultimo)
{
    int i;
    for( i=ultimo ; i>posicao ; i-- )
    {
        alunos[i] = alunos[i-1];
    }
}

void quickSort(aluno alunos[], int ini, int fim, int tipo)
{   
    carregaArquivo(alunos);
    int idx_pivo;

    if ( ini <  fim )
    {
        idx_pivo = particionar(alunos, ini, fim, tipo);
        quickSort(alunos, ini, idx_pivo - 1, tipo);
        quickSort(alunos, idx_pivo, fim, tipo);
    }

    atualizaArquivo(alunos);
}

int particionar(aluno alunos[], int ini, int fim, int tipo)
{   
    int esq = ini;
    int dir = fim;
    aluno pivo = alunos[ini];

    while ( esq < dir )
    {
        while ( alunos[esq].prontuario <= pivo.prontuario )
            esq++;
        while ( alunos[dir].prontuario > pivo.prontuario )
            dir--;

        if( esq < dir ) { trocaPosicao( &alunos[esq], &alunos[dir] ); };   
    }

    alunos[ini] =  alunos[dir];
    alunos[dir] = pivo;

    return dir;
}