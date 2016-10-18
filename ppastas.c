#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// Struct sugerida para represnetar cada elemento da estrutura de dados
typedef struct sElemento{
    char nome[100];
    struct sElemento *vizinho;
    struct sElemento *filho;
} ELEMENTO;

// Função que recebe uma referência do primeiro elemento da estrutura (C:)
// e a tabulação para impressão identada dos diretórios e arquivos
void imprimir(ELEMENTO *p, char *tab){

// Ponteiro auxiliar para percorrer o filho e vizinhos do elemento a ser impresso
ELEMENTO *p_aux;

// Variável para aumentar o tabulação a cada chamada recursiva da função
char str[80];


strcpy (str,tab);
  strcat (str,"  ");

// Se o elemento tem filho, se tem subdiretórios
if(p->filho){
    // Ponteiro auxiliar recebe o endereço do filho, primeiro elemento
    p_aux = p->filho;
    // Enquanto o elemento tiver um endereço de memória alocada, ou seja, for diferente de NULL
    while(p_aux){
        // Imprime a tabulação e o nome do elemento
        printf("%s%s\n", str, p_aux->nome);
        // Chamada recursiva para continuar imprimindo os filhos do elemento, se houver (APLICAÇÃO INTERESSANTE DE RECURSIVIDADE)
        imprimir(p_aux, str);
        // Ponteiro auxiliar recebe o endereço do viznho, para continuar imprimindo até que não haja mais vizinhos
        p_aux = p_aux->vizinho;
    }
}


}

// Função que recebe uma referência do elemento a ser explorado
// e o nome do diretório completo (desde c:...) para abertura do mesmo
// Retorna o primeiro diretório filho do diretório explorado
// para continuar como referência de elemento corrente na função main
ELEMENTO * avance(ELEMENTO p, char nome){

// Ponteiro auxiliar para percorrer o filho e os vizinhos do elemento a ser explorado
ELEMENTO *p_aux;
// Variáveis para leitura dos diretórios e arquivos do windows
DIR *p_dir;
struct dirent *p_elemento; 
// Contador para identificar o primeiro diretório ou arquivo do elemento a ser explorado, ou seja, o filho
int first = 1;

// Guarda o endereço do elemento a ser explorado em um ponteiro auxiliar que será utilizado para 
// percorrer os demais sem perder a referência do elemento a ser explorado
p_aux = p;

// Abertura do diretório principal (C:\) e loop para percorrer todos os seus subdiretórios e arquivos
p_dir = opendir(nome);
while ( ( p_elemento = readdir(p_dir) ) != 0 ){

    // Se for o primeiro subdiretório ou arquivo, então aloca memória e guarda o endereço
    // de memória alocada no campo filho do elemento a ser explorado
    if(first){
        printf("%s\n", p_elemento->d_name);
        p_aux->filho = malloc(sizeof(ELEMENTO));
        // Atribui para o ponteiro auxiliar o endereço do elemento alocado
        p_aux = p_aux->filho;
        // Copia os valores para o elemento alocado
        strcpy(p_aux->nome, p_elemento->d_name);
        p_aux->vizinho = NULL;
        p_aux->filho = NULL;
        // Atribui zero para identificar que o primeiro elemento já foi alocado
        first = 0;
    }
    else{
        printf("%s\n", p_elemento->d_name);
        p_aux->vizinho = malloc(sizeof(ELEMENTO));
        p_aux = p_aux->vizinho;
        // Copia os valores para o elemento alocado
        strcpy(p_aux->nome, p_elemento->d_name);
        p_aux->vizinho = NULL;
        p_aux->filho = NULL;
    }
    

}
    // Fechar o diretório explorado
    closedir(p_dir);

// Retorno o primeiro diretório, ou seja, o filho do diretório explorado,
// para continuar como referência de elemento corrente na função main
return p->filho;


}

main(){

// Ponteiro para o primeiro elemento e ponteiros auxiliares para percorrer filhos e vizinhos
ELEMENTO *p, *p_aux, *p_aux_first;
// Variáveis para leitura dos diretórios e arquivos do windows
DIR *p_dir;
struct dirent *p_elemento;
// Contador para identificar o primeiro diretório ou arquivo, ou seja, o filho
int first = 1;
// Variáveis para armazenar o comando digitado pelo usuário e o nome do diretório a ser avançado
char comando[100], nome[100];

// Mensagens para o usuário
puts("Sistema Explorador de Arquivos [versao 1.0]");
puts("\n");
puts("EXPLORANDO C:\\");
puts("\n");

// Alocação de memória para o primeiro elemento (C:\)
p = malloc(sizeof(ELEMENTO));
strcpy(p->nome, "C:\\");
p->vizinho = NULL;
p->filho = NULL;

// Guarda o endereço do primeiro elemento em um ponteiro auxiliar que será utilizado para 
// percorrer os demais sem perder a referência do início da estrutura de dados
p_aux = p;

// Abertura do diretório principal (C:\) e loop para percorrer todos os seus subdiretórios e arquivos
p_dir = opendir(p->nome);
while ( ( p_elemento = readdir(p_dir) ) != 0 ){

    // Se for o primeiro subdiretório ou arquivo, então aloca memória e guarda o endereço
    // de memória alocada no campo filho do elemento principal (C:\)
    if(first){
        printf("%s\n", p_elemento->d_name);
        p_aux->filho = malloc(sizeof(ELEMENTO));
        // Atribui para o ponteiro auxiliar o endereço do elemento alocado
        p_aux = p_aux->filho;
        // Copia os valores para o elemento alocado
        strcpy(p_aux->nome, p_elemento->d_name);
        p_aux->vizinho = NULL;
        p_aux->filho = NULL;
        // Atribui zero para identificar que o primeiro elemento já foi alocado
        first = 0;
    }
    // Senão, aloca memória e guarda o endereço de memória alocada para o vizinho do elemento corrente
    else{
        printf("%s\n", p_elemento->d_name);
        p_aux->vizinho = malloc(sizeof(ELEMENTO));
        // Atribui para o ponteiro auxiliar o endereço do elemento alocado
        p_aux = p_aux->vizinho;
        // Copia os valores para o elemento alocado
        strcpy(p_aux->nome, p_elemento->d_name);
        p_aux->vizinho = NULL;
        p_aux->filho = NULL;
    }


}
  // Fechar o diretório explorado
  closedir(p_dir);

// Guarda no ponteiro auxiliar o endereço do primeiro elemento, filho do elemento principal (C:)
  p_aux = p->filho;

// Loop infinito
  for(;;){

// Opções do usuário
puts("\n");
  puts("AVANCAR ou IMPRIMIR");
  scanf("%s", comando);

  // Se a opção digitada for IMPRIMIR, então imprime o nome do elemento principal (C:\) chama a função de impressão
  if(stricmp(comando, "IMPRIMIR") == 0){
    puts("\n");
    puts("IMPRIMINDO ESTRUTURA DE DADOS CRIADA ...");
    puts("\n");
    printf("%s\n", p->nome);
    imprimir(p, "");
    // Sai do loop infinito e encerra o programa
        break;
    }
    else
    // Se a opção digitada for AVANCAR, então solicita ao usuário o caminho a ser avançado
    if(stricmp(comando, "AVANCAR") == 0){

        puts("Entre com o caminho (ex. C:\\Windows): ");
      scanf(" %[^\n]s", nome);

      // Guarda o endereço do primeiro elemento do diretório corrente para caso não encontrar o diretório digitado
      p_aux_first = p_aux;

      // Enquando o ponteiro auxiliar guardar um endereço de memória alocada, ou seja, não for NULL
      while(p_aux){

        // Testa se o nome do elemento corrente está contido no endereço digitado, a partir da última barra
            if(stricmp(p_aux->nome, strrchr(nome, '\\') + 1) == 0){
                puts("\n");
                printf("EXPLORANDO %s", nome);
                puts("\n");
                // Chama função para avançar, que faz seu trabalho e retorna o primeiro elemento do diretório avançado
                p_aux = avance(p_aux, nome);
                // Quebra o loop, sai do while
                break;
            }
            // Atualiza o ponteiro auxiliar para que o elemento corrente agora seja o seu vizinho
            p_aux = p_aux->vizinho;
        }
        // Se percorreu todos os vizinhos e não encontrou o diretório
        if(p_aux==NULL){
            puts("Diretorio Invalido");
            // Volta para o ponteiro auxiliar o endereço do primeiro elemento do diretório corrente
            p_aux = p_aux_first;
        }
    }

    else
        puts("Comando Invalido");   
}
