#include <stdio.h>
#include <stdlib.h>
#include "biblioListaEncad.h"
typedef struct lista{
    DadosAlunos dados;
    struct lista *prox;
}lista;

int main(){
    /*criando um ponteiro para um ponteiro,
     pois lista é do tipo ponteiro para uma estrutura*/
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
//implementando as funções:
//-------Criação-------
Lista* criaLista(){
    Lista* li=(Lista*) malloc(sizeof(Lista));
    if(li!=NULL)
        //o conteúdo dele é null no início
        *li=NULL;
    return li;
}
//-------liberação-------
void liberaLista(Lista* li){
    if(li!=NULL){
        lista* ponteiroAux;
        while((*li)!=NULL){
            /*
             -passa o conteúdo contido no vetor li para ele,
             para depois poder desalocar esse espaço
             -eu não desaloco diretamente porque esse meu ponteiro armazena
             o valor do próximo elemento da minha lista, então não pode.
             -serve como uma variável auxiliar para que eu possa modificar o valor de
             li sem perda de informações.
            */
            ponteiroAux= *li;
            //o ponteiro passa a apontar para o próximo, percorre a lista.
            *li = (*li)->prox;
            free(ponteiroAux);
        }
        //depois libera, quando o ponteiro passa apontar para o null
        free(li);
    }
}
//-------consultas sobre a lista-------
int tamanho(Lista* li){
    //verificação se a lista foi inicializada
    if(li==NULL)
        return 0;
    int tamanhoLista=0;
    lista *pontAux= *li;
    /*está fazendo um comparativo com o endereço e
     não com o conteúdo porque eu estou utilizando
    como referência o prox(ele armazena endereço de ponteiro*/
    while(pontAux!=NULL){
        /*
         -esse ponteiro armazena sempre o próximo endereço
         e caso ele aponte para o nulo significa que chegou
         no final da lista
         -tem que usar um vetor auxiliar se não irá modificar
         o ponteiro principal
        */
        pontAux= pontAux->prox;
        tamanhoLista++;
    }
    return tamanhoLista;
}
//não tem sentido, em lista dinâmica perguntar se a lista está cheia, porém está vazia é uma opção
int listaVazia(Lista* li){
    if(li==NULL)
        return 1;
    if(*li==NULL)
        return 1;
    return 0;
}
//--------inserção-------
int inserirDadosInicio(Lista* li, DadosAlunos Dados){
    if(li==NULL)
        return 0;
    lista* elemento=(lista*) malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    elemento->dados= Dados;
    /*aqui está dizendo que é a própria lista
    (é essa a simbologia para(*li)),desse modo,
    resolve todos os casos(se ela estiver vazia ou
    já com valores armazenados*/
    elemento->prox= (*li);
    //atribuindo o conteúdo do ponteiro li
    *li= elemento;
    return 1;
}
int inserirDadosMeio(Lista* li, DadosAlunos Dados){
    //criando um novo elemento e alocando[
    lista* elemento=(lista*) malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    //verificação de posição
    int i=0;
    /*como é ponteiro tem q verificar se é nulo
    e através de variáveis auxiliares fazer a comparação*/
    lista *ant, *atual=*li;
    while(atual!=NULL && atual->dados.matricula< Dados.matricula ){
        ant= atual;
        atual= atual->prox;
    }
    //atribuir os valores do meu novo elemento e fazer
    elemento->dados= Dados;
    //lógica para saber onde irá add esse novo elemento:
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
    //verificar se dá para fazer assim para não ser big O(n)(*li)= elemento;
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
//remoção
int removerInicio(Lista *li){
    //verificação se a lista não foi inicializada ou está vazia
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
    //verificação se a lista não foi inicializada ou está vazia
    if(li==NULL || *li==NULL)
        return 0;
    //criando elemento auxiliar para liberar o elemento
    lista *ant, *aux=*li;
    while(aux!=NULL && aux->dados.matricula!=Dados.matricula){
        ant=aux;
        aux=aux->prox;
    }
    //verificando se chegou no fim da lista e não encontrou
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
    //verificação se a lista não foi inicializada ou está vazia
    if(li==NULL)
        return 0;
    if(*li==NULL)
        return 0;
    lista *ant, *aux= *li;
    /*pra remover é necessário não sair da última posição
    diferentemente do processo de inserção e a função de visualizar
    o tamanho por isso eu utilizo o aux->prox!=NULL ao invés de
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

//procurando se naquela posição existe aquela matrícula
int consultaPosicaoElemento(int posicao, Lista* li, DadosAlunos Dados){
    //verificar se a lista existe e foi inicializada
    if(li == NULL || (*li)==NULL || posicao<0)
        return 0;
    //declarando um contador e ponteiro auxiliar para percorrer a lista
    int count=0;
    lista *aux=*li;
    // verificando se naquela posição existe o mesmo valor dado
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
    // verificando se naquela posição existe o mesmo valor dado
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
//buscando só pelo elemento
int BuscaElemAluno(Lista* li, DadosAlunos *Dados, int matricula){
    //verificar se a lista existe e foi inicializada
    if(li == NULL || (*li)==NULL )
        return 0;
    //declarando um contador e ponteiro auxiliar para percorrer a lista
    lista *aux=*li;
    // verificando se naquela posição existe o mesmo valor dado
    while(aux!=NULL && aux->dados.matricula != matricula)
        aux= aux->prox;
    if(aux==NULL)
        return 0;
    else
        *Dados= aux->dados;
        return 1;
}
