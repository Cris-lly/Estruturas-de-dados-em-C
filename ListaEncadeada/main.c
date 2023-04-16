#include <stdio.h>
#include <stdlib.h>
#include "biblioListaEncad.h"
//lista de vizinhos
typedef struct listaSecundaria{
    char nome_vertice;
    struct listaSecundaria *prox;
}lista_vizinho;

//lista principal
typedef struct lista_principal{
    Dados_vertice dado_vertice;
    //REFERÊNCIA PARA A LISTA DE VIZINHO
    struct lista_vizinho *vizinho;
    //PONTEIRO PARA O PRÓXIMO ELEMENTO
    struct lista_principal* prox_elem;
}lista_vertice;

int main(){
    //criando a lista principal
    ListaVertice *li_principal;
    li_principal=criaListaVertice();
    //criando a lista secundária
    ListaVizinho *li;
    li=criaListaVizinho();
    char nome, nomeRet;
    scanf("%c", &nome);
    inserirDadosFimVizinho(li, nome);
    inserirDadosFimVizinho(li, 'c');
    inserirDadosFimVizinho(li, 'd');
    Dados_vertice dado;
    dado.nome_vertice = 'a';
    dado.qtdd_vizinhos = 2;
    inserirDadosFimVertice(li_principal, li, dado);
    liberaListaVizinho(li);

    return 0;
}
//implementando as funções da lista de vizinhos:
//-------Criação-------
ListaVizinho* criaListaVizinho(){
    ListaVizinho* li=(ListaVizinho*) malloc(sizeof(ListaVizinho));
    if(li!=NULL)
        //o conteúdo dele é null no início
        *li=NULL;
    return li;
}
//-------liberação-------
void liberaListaVizinho(ListaVizinho* li){
    if(li!=NULL){
        lista_vizinho* ponteiroAux;
        while((*li)!=NULL){
            /*
             -passa o conteúdo contido no vetor li para ele,
             para depois poder desalocar esse espaço
             -eu não desaloco diretamente porque esse meu ponteiro armazena
             o valor do próximo elemento da minha lista_vizinho, então não pode.
             -serve como uma variável auxiliar para que eu possa modificar o valor de
             li sem perda de informações.
            */
            ponteiroAux= *li;
            //o ponteiro passa a apontar para o próximo, percorre a lista_vizinho.
            *li = (*li)->prox;
            free(ponteiroAux);
        }
        //depois libera, quando o ponteiro passa apontar para o null
        free(li);
    }
}
//-------consultas sobre a lista_vizinho-------
int tamanhoVizinho(ListaVizinho* li){
    //verificação se a lista_vizinho foi inicializada
    if(li==NULL)
        return 0;
    int tamanhoLista=0;
    lista_vizinho *pontAux= *li;
    /*está fazendo um comparativo com o endereço e
     não com o conteúdo porque eu estou utilizando
    como referência o prox(ele armazena endereço de ponteiro*/
    while(pontAux!=NULL){
        /*
         -esse ponteiro armazena sempre o próximo endereço
         e caso ele aponte para o nulo significa que chegou
         no final da lista_vizinho
         -tem que usar um vetor auxiliar se não irá modificar
         o ponteiro principal
        */
        pontAux= pontAux->prox;
        tamanhoLista++;
    }
    return tamanhoLista;
}
//não tem sentido, em lista_vizinho dinâmica perguntar se a lista_vizinho está cheia, porém está vazia é uma opção
int listaVaziaVizinho(ListaVizinho* li){
    if(li==NULL)
        return 1;
    if(*li==NULL)
        return 1;
    return 0;
}
//inserção
int inserirDadosFimVizinho(ListaVizinho* li, char nome ){
    if(li==NULL)
        return 0;
    lista_vizinho* elemento=(lista_vizinho*) malloc(sizeof(lista_vizinho));
    if(elemento==NULL)
        return 0;
    elemento->nome_vertice= nome;
    elemento->prox= NULL;
    //verificar se dá para fazer assim para não ser big O(n)(*li)= elemento;
    //verificar as duas possibilidades:
    if(*li==NULL){
        *li=elemento;
    }
    else{
        lista_vizinho* ponteAux= *li;
        while(ponteAux->prox!=NULL){
            ponteAux= ponteAux->prox;
        }
        ponteAux->prox= elemento;
    }
    return 1;
}
//remoção
int removerMeioVizinho(ListaVizinho* li, char nome){
    //verificação se a lista_vizinho não foi inicializada ou está vazia
    if(li==NULL || *li==NULL)
        return 0;
    //criando elemento auxiliar para liberar o elemento
    lista_vizinho *ant, *aux=*li;
    while(aux!=NULL && aux->nome_vertice!=nome){
        ant=aux;
        aux=aux->prox;
    }
    //verificando se chegou no fim da lista_vizinho e não encontrou
    if(aux==NULL)
        return 0;
    //verificando se tem que remover o primeiro
    if(aux== *li)
        *li=aux->prox;
    else
        ant->prox= aux->prox;
    free(aux);
    return 1;
}

//buscando só pelo elemento
int BuscaElemVizinho(ListaVizinho* li, char *nomeRetorno, char nome){
    //verificar se a lista_vizinho existe e foi inicializada
    if(li == NULL || (*li)==NULL )
        return 0;
    //declarando um contador e ponteiro auxiliar para percorrer a lista_vizinho
    lista_vizinho *aux=*li;
    // verificando se naquela posição existe o mesmo valor dado
    while(aux!=NULL && aux->nome_vertice != nome)
        aux= aux->prox;
    if(aux==NULL)
        return 0;
    else
        *nomeRetorno= aux->nome_vertice;
        return 1;
}

//implementando as funções da lista Principal:
//-------Criação-------
ListaVertice* criaListaVertice(){
    ListaVertice* li=(ListaVertice*) malloc(sizeof(ListaVertice));
    if(li!=NULL)
        //o conteúdo dele é null no início
        *li=NULL;
    return li;
}
//-------liberação-------
void liberaListaVertice(ListaVertice* li){
    if(li!=NULL){
        lista_vertice* ponteiroAux;
        while((*li)!=NULL){
            /*
             -passa o conteúdo contido no vetor li para ele,
             para depois poder desalocar esse espaço
             -eu não desaloco diretamente porque esse meu ponteiro armazena
             o valor do próximo elemento da minha lista_vertice, então não pode.
             -serve como uma variável auxiliar para que eu possa modificar o valor de
             li sem perda de informações.
            */
            ponteiroAux= *li;
            //o ponteiro passa a apontar para o próximo, percorre a lista_vertice.
            *li = (*li)->prox_elem;
            free(ponteiroAux);
        }
        //depois libera, quando o ponteiro passa apontar para o null
        free(li);
    }
}
//-------consultas sobre a lista_vertice-------
int tamanhoVertice(ListaVertice* li){
    //verificação se a lista_vertice foi inicializada
    if(li==NULL)
        return 0;
    int tamanhoLista=0;
    lista_vertice *pontAux= *li;
    /*está fazendo um comparativo com o endereço e
     não com o conteúdo porque eu estou utilizando
    como referência o prox(ele armazena endereço de ponteiro*/
    while(pontAux!=NULL){
        /*
         -esse ponteiro armazena sempre o próximo endereço
         e caso ele aponte para o nulo significa que chegou
         no final da lista_vertice
         -tem que usar um vetor auxiliar se não irá modificar
         o ponteiro principal
        */
        pontAux= pontAux->prox_elem;
        tamanhoLista++;
    }
    return tamanhoLista;
}
//não tem sentido, em lista_vertice dinâmica perguntar se a lista_vertice está cheia, porém está vazia é uma opção
int listaVaziaVertice(ListaVertice* li){
    if(li==NULL)
        return 1;
    if(*li==NULL)
        return 1;
    return 0;
}
//inserção
int inserirDadosFimVertice(ListaVertice* li, ListaVizinho* li_vizinho, Dados_vertice dados ){
    if(li==NULL)
        return 0;
    lista_vertice* elemento=(lista_vertice*) malloc(sizeof(lista_vertice));
    if(elemento==NULL)
        return 0;
    elemento->dado_vertice= dados;
    elemento->vizinho = *li_vizinho;
    lista_vizinho *aux= elemento->vizinho;
    // verificando se naquela posição existe o mesmo valor dado
    while(aux!=NULL ){
        printf("%c",aux->nome_vertice);
        aux= aux->prox;
    }

    elemento->prox_elem= NULL;
    //verificar se dá para fazer assim para não ser big O(n)(*li)= elemento;
    //verificar as duas possibilidades:
    if(*li==NULL){
        *li=elemento;
    }
    else{
        lista_vertice* ponteAux= *li;
        while(ponteAux->prox_elem!=NULL){
            ponteAux= ponteAux->prox_elem;
        }
        ponteAux->prox_elem= elemento;
    }
    return 1;
}
//remoção
int removerMeioVertice(ListaVertice* li, char nome){
    //verificação se a lista_vertice não foi inicializada ou está vazia
    if(li==NULL || *li==NULL)
        return 0;
    //criando elemento auxiliar para liberar o elemento
    lista_vertice *ant, *aux=*li;
    while(aux!=NULL && aux->dado_vertice.nome_vertice!=nome){
        ant=aux;
        aux=aux->prox_elem;
    }
    //verificando se chegou no fim da lista_vertice e não encontrou
    if(aux==NULL)
        return 0;
    //verificando se tem que remover o primeiro
    if(aux== *li)
        *li=aux->prox_elem;
    else
        ant->prox_elem= aux->prox_elem;
    free(aux);
    return 1;
}

//buscando só pelo elemento
int BuscaElemVertice(ListaVertice* li, char *nomeRetorno, char nome){
    //verificar se a lista_vertice existe e foi inicializada
    if(li == NULL || (*li)==NULL )
        return 0;
    //declarando um contador e ponteiro auxiliar para percorrer a lista_vertice
    lista_vertice *aux=*li;
    // verificando se naquela posição existe o mesmo valor dado
    while(aux!=NULL && aux->dado_vertice.nome_vertice != nome)
        aux= aux->prox_elem;
    if(aux==NULL)
        return 0;
    else
        *nomeRetorno= aux->dado_vertice.nome_vertice;
        return 1;
}
