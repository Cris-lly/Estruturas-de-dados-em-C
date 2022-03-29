#include <stdio.h>
#include <stdlib.h>
#include "biblioListaEncad.h"
typedef struct lista{
    DadosAlunos dados;
    struct lista *prox;
}lista;

int main(){
    /*criando um ponteiro para um ponteiro,
     pois lista � do tipo ponteiro para uma estrutura*/
    Lista *li;
    DadosAlunos Dados, Dados1;
    li=criaLista();
    scanf(" %[^\n]s", Dados.nome);
    Dados.matricula=245;
    Dados.nota[0]=6;
    Dados.nota[1]=6;
    Dados.nota[2]=6;
    Dados.nota[3]=6;
    Dados.media= 6;

    scanf(" %[^\n]s", Dados1.nome);
    Dados1.matricula=247;
    Dados1.nota[0]=6;
    Dados1.nota[1]=6;
    Dados1.nota[2]=6;
    Dados1.nota[3]=6;
    Dados1.media= 6;

    inserirDadosInicio(li, Dados1);
    inserirDadosMeio(li,Dados);

    int posicao=1;
    DadosAlunos dados_aluno;
    BuscaElemAluno( li, &dados_aluno, 245);

    printf("%f\n", dados_aluno.media);
    printf("%s\n", dados_aluno.nome);
    liberaLista(li);

    return 0;
}
//implementando as fun��es:
//-------Cria��o-------
Lista* criaLista(){
    Lista* li=(Lista*) malloc(sizeof(Lista));
    if(li!=NULL)
        //o conte�do dele � null no in�cio
        *li=NULL;
    return li;
}
//-------libera��o-------
void liberaLista(Lista* li){
    if(li!=NULL){
        lista* ponteiroAux;
        while((*li)!=NULL){
            /*
             -passa o conte�do contido no vetor li para ele,
             para depois poder desalocar esse espa�o
             -eu n�o desaloco diretamente porque esse meu ponteiro armazena
             o valor do pr�ximo elemento da minha lista, ent�o n�o pode.
             -serve como uma vari�vel auxiliar para que eu possa modificar o valor de
             li sem perda de informa��es.
            */
            ponteiroAux= *li;
            //o ponteiro passa a apontar para o pr�ximo, percorre a lista.
            *li = (*li)->prox;
            free(ponteiroAux);
        }
        //depois libera, quando o ponteiro passa apontar para o null
        free(li);
    }
}
//-------consultas sobre a lista-------
int tamanho(Lista* li){
    //verifica��o se a lista foi inicializada
    if(li==NULL)
        return 0;
    int tamanhoLista=0;
    lista *pontAux= *li;
    /*est� fazendo um comparativo com o endere�o e
     n�o com o conte�do porque eu estou utilizando
    como refer�ncia o prox(ele armazena endere�o de ponteiro*/
    while(pontAux!=NULL){
        /*
         -esse ponteiro armazena sempre o pr�ximo endere�o
         e caso ele aponte para o nulo significa que chegou
         no final da lista
         -tem que usar um vetor auxiliar se n�o ir� modificar
         o ponteiro principal
        */
        pontAux= pontAux->prox;
        tamanhoLista++;
    }
    return tamanhoLista;
}
//n�o tem sentido, em lista din�mica perguntar se a lista est� cheia, por�m est� vazia � uma op��o
int listaVazia(Lista* li){
    if(li==NULL)
        return 1;
    if(*li==NULL)
        return 1;
    return 0;
}
//--------inser��o-------
int inserirDadosInicio(Lista* li, DadosAlunos Dados){
    if(li==NULL)
        return 0;
    lista* elemento=(lista*) malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    elemento->dados= Dados;
    /*aqui est� dizendo que � a pr�pria lista
    (� essa a simbologia para(*li)),desse modo,
    resolve todos os casos(se ela estiver vazia ou
    j� com valores armazenados*/
    elemento->prox= (*li);
    //atribuindo o conte�do do ponteiro li
    *li= elemento;
    return 1;
}
int inserirDadosMeio(Lista* li, DadosAlunos Dados){
    //criando um novo elemento e alocando[
    lista* elemento=(lista*) malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    //verifica��o de posi��o
    int i=0;
    /*como � ponteiro tem q verificar se � nulo
    e atrav�s de vari�veis auxiliares fazer a compara��o*/
    lista *ant, *atual=*li;
    while(atual!=NULL && atual->dados.matricula< Dados.matricula ){
        ant= atual;
        atual= atual->prox;
    }
    //atribuir os valores do meu novo elemento e fazer
    elemento->dados= Dados;
    //l�gica para saber onde ir� add esse novo elemento:
    if((*li)==NULL){
        elemento->prox= NULL;
        *li=elemento;
    }else{
        elemento->prox= ant->prox;
        ant->prox= elemento;
    }
    return 1;
}
int inserirDadosFim(Lista* li, DadosAlunos Dados ){
    if(li==NULL)
        return 0;
    lista* elemento=(lista*) malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    elemento->dados= Dados;
    elemento->prox= NULL;
    //verificar se d� para fazer assim para n�o ser big O(n)(*li)= elemento;
    //verificar as duas possibilidades:
    if(*li==NULL){
        *li=elemento;
    }
    else{
        lista* ponteAux= *li;
        while(ponteAux->prox!=NULL){
            ponteAux= ponteAux->prox;
        }
        ponteAux->prox= elemento;
    }
    return 1;
}
//remo��o
int removerInicio(Lista *li){
    //verifica��o se a lista n�o foi inicializada ou est� vazia
    if(li==NULL)
        return 0;
    if(*li==NULL)
        return 0;
    //criando elemento auxiliar para liberar o elemento
    lista* elemento=*li;
    *li= elemento->prox;
    free(elemento);
    return 1;
}
int removerMeio(Lista* li, DadosAlunos Dados){
    //verifica��o se a lista n�o foi inicializada ou est� vazia
    if(li==NULL || *li==NULL)
        return 0;
    //criando elemento auxiliar para liberar o elemento
    lista *ant, *aux=*li;
    while(aux!=NULL && aux->dados.matricula!=Dados.matricula){
        ant=aux;
        aux=aux->prox;
    }
    //verificando se chegou no fim da lista e n�o encontrou
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
int removerFim(Lista* li){
    //verifica��o se a lista n�o foi inicializada ou est� vazia
    if(li==NULL)
        return 0;
    if(*li==NULL)
        return 0;
    lista *ant, *aux= *li;
    /*pra remover � necess�rio n�o sair da �ltima posi��o
    diferentemente do processo de inser��o e a fun��o de visualizar
    o tamanho por isso eu utilizo o aux->prox!=NULL ao inv�s de
     aux!=NULL3
          */
    while(aux->prox!=NULL){
        ant=aux;
        aux=aux->prox;
    }
    //verificar se aux saiu do canto(se a lista vai remover o primeiro)
    if(aux==*li)
        *li= NULL;//ou *li->aux->prox;
    else
        ant->prox= NULL;
    free(aux);
    return 1;
}
//-------busca-------

//procurando se naquela posi��o existe aquela matr�cula
int consultaPosicaoElemento(int posicao, Lista* li, DadosAlunos Dados){
    //verificar se a lista existe e foi inicializada
    if(li == NULL || (*li)==NULL || posicao<0)
        return 0;
    //declarando um contador e ponteiro auxiliar para percorrer a lista
    int count=0;
    lista *aux=*li;
    // verificando se naquela posi��o existe o mesmo valor dado
    while(count<posicao && aux->dados.matricula != Dados.matricula){
        aux= aux->prox;
        count++;
    }
    if(aux==NULL)
        return 0;
    else
        return 1;
}
//verificando o que tem em determinada posicao
int consultaPosicao(int posicao, Lista* li, DadosAlunos *Dados){
    //verificar se a lista existe e foi inicializada
    if(li == NULL || (*li)==NULL || posicao<0)
        return 0;
    //declarando um contador e ponteiro auxiliar para percorrer a lista
    int count=1;
    lista *aux=*li;
    // verificando se naquela posi��o existe o mesmo valor dado
    while(count<posicao && aux!=NULL){
        aux= aux->prox;
        count++;
    }
    if(aux==NULL)
        return 0;
    else
        *Dados= aux->dados;
    return 1;
}
//buscando s� pelo elemento
int BuscaElemAluno(Lista* li, DadosAlunos *Dados, int matricula){
    //verificar se a lista existe e foi inicializada
    if(li == NULL || (*li)==NULL )
        return 0;
    //declarando um contador e ponteiro auxiliar para percorrer a lista
    lista *aux=*li;
    // verificando se naquela posi��o existe o mesmo valor dado
    while(aux!=NULL && aux->dados.matricula != matricula)
        aux= aux->prox;
    if(aux==NULL)
        return 0;
    else
        *Dados= aux->dados;
        return 1;
}
