
#include <stdio.h>
#include <string.h>
#define NOME 50
#define SOBRENOME 50
#define QUANTIDADE_ALUNOS 1000


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
void  mergeSort(aluno alunos[], int tipo);
void  ordenaIntercalacao(aluno alunos[], int ini, int fim, int tipo);
void  intercalar(aluno alunos[], int ini, int meio, int fim, int tipo);


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
        case 1: buscaNomeSobrenome(alunos); break;
        case 2: buscaNome(alunos);          break;
        case 3: buscaSobrenome(alunos);     break;
        case 4: buscaProntuario(alunos);    break;
        case 5: buscaNascimento(alunos);    break;
        case 6: buscaCurso(alunos);         break;
        case 7: break;
        default: printf("\nErro! Opcao invalida.\n");
        }

    } while ( escolha != 7 );
}

void buscaCurso(aluno alunos[])
{
    // função responsável por buscar e listar por: curso

    carregaArquivo(alunos); // carrega da memória secundária arquivo com os dados já cadastrados
    char curso[10]; // vetor que recebe o curso que o usuário deseja listar
    int  i, contador=0; // variárel 'contador' conta quantos alunos foram listados
    int  index = localizaUltimaPosicao(alunos); // variavel index recebe o indice da ultima posição do vetor alunos[]

    printf("\nBUSCA POR CURSO\n");
    printf("Digite o curso: "); fflush(stdin); gets(curso); // recebe o curso desejado pelo usuário

    for( i=0 ; i<index ; i++ ) // laço para encontrar os itens desejados
    {
        if( ! (strcmp(alunos[i].curso, curso))) // strcmp retorn 0 quando os valores passados são iguais
        {
            mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
            marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
            contador++; // conta quantos itens foram mostrados
        }
    }
    if(!contador) // se o contador tiver em 0, não foi achado nenhum resultado
    {
        printf("\nNao foi encontrado aluno relacionado a este curso.\n");
    } else confirmaApagarDados(alunos); // pergunta ao usuário se quer apagar os dados listados
}

void buscaNascimento(aluno alunos[])
{
    // função responsável por buscar e listar por: curso

    carregaArquivo(alunos); // carrega da memória secundária arquivo com os dados já cadastrados
    int dia, mes, ano; // recebe a data de nascimento para fazer a busca
    int i, contador=0;  // variárel 'contador' conta quantos alunos foram listados
    int index = localizaUltimaPosicao(alunos); // variavel index recebe o indice da ultima posição do vetor alunos[]

    printf("\nBUSCA POR NASCIMENTO\n"); // recebe a data de nascimento desejada
    printf("Digite o dia:"); scanf("%d", &dia);
    printf("Digite o mes:"); scanf("%d", &mes);
    printf("Digite o ano:"); scanf("%d", &ano);

    for( i=0 ; i<index ; i++ ) // laço para encontrar os itens desejados
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
    if(!contador) // se o contador tiver em 0, não foi achado nenhum resultado
    {
        printf("\nNão foi encontrado aluno com esta data de nascimento.\n");
    } else confirmaApagarDados(alunos); // pergunta ao usuário se quer apagar os dados listados
}

void buscaProntuario(aluno alunos[])
{

    // função responsável por buscar e listar por: prontuário

    carregaArquivo(alunos); // carrega da memória secundária arquivo com os dados já cadastrados
    int prontuario; // variável que recebe o curso que o usuário deseja listar
    int i, contador=0; // variável 'contador' conta quantos alunos foram listados
    int index = localizaUltimaPosicao(alunos); // variavel index recebe o indice da ultima posição do vetor alunos[]

    printf("\nBUSCA POR PRONTUARIO\n"); 
    printf("Digite o prontuario: "); scanf("%d", &prontuario); // recebe o curso desejado pelo usuário

    for( i=0 ; i<index ; i++ ) // laço para encontrar os itens desejados
    {
        if( alunos[i].prontuario == prontuario ) // se achar um prontuário, então é mostrado ao usuário
        {
            mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
            marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
            contador++; // conta quantos itens foram mostrados 
        }
    }
    if(!contador) // se o contador tiver em 0, não foi achado nenhum resultado
    {
        printf("\nNao foi encontrado aluno relacionado a este prontuario.\n");
    } else confirmaApagarDados(alunos); // pertunta ao usuário se quer apagar os dados listados
}

void marcarNome(aluno alunos[], int i)
{
    // função responsavel por 'marcar' os itens que serão deletados caso o usuário queira
    // strcpy copia a segunda string, para a posição da primeira string
    // como essa lista é temporária, alunos[].nome com "deletar" só ficará enquanto a lista tiver dentro da função que chamar esta

    strcpy(alunos[i].nome, "deletar");
}

void buscaSobrenome(aluno alunos[])
{
    // função responsável por buscar e listar por: sobrenome

    carregaArquivo(alunos); // carrega da memória secundária arquivo com os dados já cadastrados
    char sobrenome[50]; // vetor que recebe o sobrenome que o usuário deseja listar
    int  i, contador=0; // variável 'contador' conta quantos alunos foram listados
    int  index = localizaUltimaPosicao(alunos); // variavel index recebe o indice da ultima posição do vetor alunos[]

    printf("\nBUSCA POR SOBRENOME\n");
    printf("Digite o sobrenome: "); fflush(stdin); gets(sobrenome); //recebe o sobrenome desejado

    for( i=0 ; i<index ; i++ )
    {
        if(!(strcmp(alunos[i].sobrenome, sobrenome))) //strcmp retorna 0 quando os valores passados são iguais
        {
            mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
            marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
            contador++; // conta quantos itens foram mostrados
        }
    }
    if(!contador) // se o contador tiver em 0, não foi achado nenhum resultado
    {
        printf("\nNao foi encontrado aluno relacionado a este sobrenome.\n");
    } else confirmaApagarDados(alunos); // pergunta ao usuário se quer apagar os dados listados
}


void buscaNomeSobrenome(aluno alunos[])
{
    // função resonsável por buscar e listar por: nome e sobrenome

    carregaArquivo(alunos); // carrega da memória secundária arquivo com os dados já cadastrados
    char nome[50];
    char sobrenome[50];
    int  i, contador=0; // variável contador conta quantos alunos foram listados
    int  index = localizaUltimaPosicao(alunos); // variavel index recebe o indice da ultima posição do vetor alunos[]

    printf("\nBUSCA POR NOME E SOBRENOME\n");
    printf("Digite o nome: "); fflush(stdin); gets(nome);
    printf("Digite o sobrenome: "); fflush(stdin); gets(sobrenome);

    for( i=0 ; i<index ; i++ )
    {
        // strcmp retorna 0 quando os valores passados são iguais
        // para passar no if, as duas strcmp precisa retornar 0
        if(! (strcmp(alunos[i].nome, nome) || (strcmp(alunos[i].sobrenome, sobrenome))))
        {
            mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
            marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
            contador++; // conta quantos itens foram mostrados
        }
    }
    if(!contador) // caso o contador tiver em 0, não foi achado nenhum resultado
    {
        printf("\nNao foi encontrado aluno relacionado a este nome e sobrenome.\n");
    } else confirmaApagarDados(alunos); // pergunta ao usuário se quer apagar os dados listados
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

void buscaNome(aluno alunos[])
{
    // função responsável por buscar e listar por: nome

    carregaArquivo(alunos); // carrega da memória secundária arquivo com os dados já cadastrados
    char nome_busca[50];
    int  i, contador=0;
    int  index = localizaUltimaPosicao(alunos); // index recebe o indice da ultima posição do vetor alunos[]

    printf("\nBUSCA POR NOME\n");
    printf("Digite o nome: "); fflush(stdin); gets(nome_busca); // recebe o curso desejado pelo usuário

    for( i=0 ; i<index ; i++ )
    {
        if(!(strcmp(alunos[i].nome, nome_busca))) // strcmp retorn 0 quando os valores passados são iguais
        {
            mostraInfo(alunos, i); // mostra para o usuário o resultado da busca
            marcarNome(alunos, i); // marca o resultado achado, para caso o usuário queira deletar depois
            contador++; // conta quantos itens foram mostrados
        }
    }
    if(!contador) // se o contador tiver em 0, não foi achado nenhum resultado
    {
        printf("\nNao foi encontrado aluno relacionado a este nome.\n");
    } else confirmaApagarDados(alunos); // pergunta ao usuário se quer apagar os dados listados
}


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
    int index     = localizaUltimaPosicao(alunos);
    
    setaTipoOrdenacao(alunos, escolha, tipo);

    carregaArquivo(alunos);
    for(i = 0; i < index; i++)
    {
        //a saída dos nomes está vindo com o ENTER
        mostraInfo(alunos, i); // mostra as informações do aluno em questão
    }
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
                    (alunos[i].data_de_nascimento.mes == alunos[j].data_de_nascimento.mes)  &&
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

void trocaPosicao(aluno *posicao1, aluno *posicao2)
{
    aluno aluno_aux = *posicao1;
    *posicao1 = *posicao2;
    *posicao2 = aluno_aux;
}

int menuOrdenacao()
{
    int escolha = 0;
    do
    {

        printf("\n[ 1 ] - Ordenar por Selecao\n");
        printf("[ 2 ] - Ordenar por Insercao\n");
        printf("[ 3 ] - Ordernar por Intercalacao (merge sort) \n");
        printf("[ 4 ] - Ordernar por Particionamento (quick sort) \n");

        printf("Digite a opção desejada:"); scanf("%d", &escolha);

    } while ( escolha < 1 || escolha > 4 );

    return escolha;
}

void setaTipoOrdenacao(aluno alunos[], int escolha, int tipo)
{
    switch(escolha)
    {
        case 1: selectionSort(alunos, tipo); break;
        // case 2: insertionSort(alunos, tipo); break;
        case 3: mergeSort(alunos, tipo); break;
        // case 4: quickSort(alunos, tipo); break;
        default: break;
    }
}


void mergeSort(aluno alunos[], int tipo)
{
    carregaArquivo(alunos);
    int tam = localizaUltimaPosicao(alunos);
    
    if ( tipo == 1 )
    {
        ordenaIntercalacao(alunos, 0, tam, tipo);
    }
    else
    if ( tipo == 2)
    {
        ordenaIntercalacao(alunos, 0, tam, tipo);
    }
    else
    if ( tipo == 3)
    {
        ordenaIntercalacao(alunos, 0, tam, tipo);
    }
    else
    if ( tipo == 4)
    {
        ordenaIntercalacao(alunos, 0, tam, tipo);
    }
    else
    if ( tipo == 5)
    {
        ordenaIntercalacao(alunos, 0, tam, tipo);
    }


}

void ordenaIntercalacao(aluno alunos[], int ini, int fim, int tipo)
{
    int meio;

    if ( ini < fim )
    {
        meio = (ini + fim) / 2;
        ordenaIntercalacao(alunos, ini, meio, tipo);
        ordenaIntercalacao(alunos, meio+1, fim, tipo);
        intercalar(alunos, ini, meio, fim, tipo);
    }
}

void intercalar(aluno alunos[], int ini, int meio, int fim, int tipo)
{
    aluno alunos_aux[QUANTIDADE_ALUNOS];
    int i = ini;
    int j = meio + 1;
    int k = 0;
    
    switch (tipo)
    {
    case 1:
        while (i <= meio && j <= fim)
        {
            if (strcmp(alunos[i].nome, alunos[j].nome) < 0) 
                alunos_aux[k++] = alunos[i++];
            else                                            
                alunos_aux[k++] = alunos[j++];
        }

        while (i <= meio) alunos_aux[k++] = alunos[i++];
        while (j <= fim)  alunos_aux[k++] = alunos[j++];

        for ( i = ini, k = 0; i <= fim; k++) 
        alunos[i] = alunos_aux[k];

    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        /* code */
        break;
    
    default:
        break;
    }
    
    
}