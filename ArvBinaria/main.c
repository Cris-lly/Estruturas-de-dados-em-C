#include <stdio.h>
#include <stdlib.h>
int acumulador=0, comparar=0;
//arquivo.h
typedef struct NO *arvBin;
//prototipo das funcoes:
//----criacao----
arvBin* criaArvBin();
//----liberar----
void liberaRaiz(arvBin* raiz);
void liberaNo(struct NO* no);
//----informacoes sobre a arvore----
int vaziaArvBin(arvBin* raiz);
int alturaArvBin(arvBin* raiz);
int totalNO_ArvBin(arvBin* raiz);
//----percorrendo a arvore----
void preOrdem_ArvBin(arvBin *raiz);
void emOrdem_ArvBin(arvBin *raiz);
void posOrdem_ArvBin(arvBin *raiz);
//----insercao----
int insere_arvBin(arvBin* raiz, int valor);
//remocao
int remove_arvBin(arvBin *raiz, int valor);
struct NO* removeAtualDir(struct NO* atual);
struct NO* removeAtualEsq(struct NO* atual);
//----busca----
int consulta_arvBin(arvBin *raiz, int valor);
//--resposta--
int resposta(arvBin *raiz, int parada);
int verificacaoAvl(arvBin* raiz);
struct NO{
    struct NO *esq;
    int info;
    struct NO *dir;
};
int main()
{
    arvBin* raiz= criaArvBin();
    int i, qtddElem,elem;
    int parada;
    scanf("%d", &qtddElem);
    for(i=0; i<qtddElem; i++){
        scanf("%d", &elem);
        insere_arvBin(raiz, elem);
    }
    scanf("%d", &parada);
    resposta(raiz, parada);
    emOrdem_ArvBin(raiz);
    printf("%d", acumulador);
    return 0;
}
//----criacao----
arvBin* criaArvBin(){
    arvBin* raiz= (arvBin*)malloc(sizeof(arvBin));
    if(raiz!=NULL)
        *raiz= NULL;
    return raiz;
}
//----liberar----
void liberaRaiz(arvBin* raiz){
    if(raiz==NULL)
        return;
    //libera cada no, como a funcao eh recursiva, entao ela nao utiliza loop
    liberaNo(*raiz);
    free(raiz);
}
void liberaNo(struct NO* no){
    if(no==NULL)
        return;
    liberaNo(no->esq);
    liberaNo(no->dir);
    free(no);
    no=NULL;
}
//----informacoes sobre a arvore----
//verificando se esta vazia
int vaziaArvBin(arvBin* raiz){
    if(raiz==NULL || *raiz==NULL)
        return 1;
    return 0;
}
//altura da arvore
int alturaArvBin(arvBin* raiz){
    if(raiz==NULL || *raiz==NULL)
        return 0;
    int alt_esq= alturaArvBin(&((*raiz)->esq));
    int alt_dir= alturaArvBin(&((*raiz)->dir));
    if(alt_esq>alt_dir)
        return(alt_esq+1);
    else
        return(alt_dir+1);
}
//Quantidade de nó
int totalNO_ArvBin(arvBin* raiz){
    if(raiz==NULL || *raiz==NULL)
        return 0;
    int alt_esq= totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir= totalNO_ArvBin(&((*raiz)->dir));
    return(alt_esq+alt_dir+1);
}
//----percorrendo a arvore----
//pre-ordem
void preOrdem_ArvBin(arvBin *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        printf("%d ", (*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}
//em-ordem
void emOrdem_ArvBin(arvBin *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d ", (*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}
//pos-ordem
void posOrdem_ArvBin(arvBin *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d ", (*raiz)->info);
    }
}
//----insercao----
int insere_arvBin(arvBin* raiz, int valor){
    if(raiz==NULL)
        return 0;
    //criando o novo no da minha arvore
    struct NO* novo;
    novo= (struct NO*)malloc(sizeof(struct NO));
    if(novo==NULL)
        return 0;
    //setando os dados do novo no
    novo->info= valor;
    novo->dir= NULL;
    novo->esq= NULL;
    //procurando onde inserir(se for maior vai para direita, se for menor, para a esquerda
    //se tiver nenhum elemento:
    if(*raiz==NULL)
        *raiz= novo;
    //se tiver um ou mais:
    else{
        //tentando localizar o ultimo no folha da direita e da esquerda p/inserir
        struct NO* atual= *raiz;
        struct NO* ant= NULL;
        while(atual!=NULL){
            ant=atual;
            //se o valor ja existe, nao ira inserir
            if(valor==atual->info){
                free(novo);
                return 0;
            }
            //verificando para qual lado do no devera ir
            if(valor>atual->info)
                atual= atual->dir;
            else
                atual= atual->esq;
        }
        if(valor>ant->info)
            ant->dir=novo;
        else
            ant->esq=novo;
    }
    return 1;
}
//----remocao----
int remove_arvBin(arvBin *raiz, int valor){
    if(raiz==NULL)
        return 0;
    struct NO* atual= *raiz;
    struct NO* ant= NULL;
    while(atual!=NULL){
        if(valor==atual->info){
            //remocao de uma arvore que tem apenas um no
            if(atual==*raiz)
                *raiz= removeAtualEsq(atual);
            else{
                //verificando se eh o no da esquerda ou da direita
                if(ant->dir==atual)
                    ant->dir=removeAtualEsq(atual);
                else
                    ant->esq=removeAtualEsq(atual);
            }
            return 1;
        }
        //caso o valor ainda nao eh o que eu quero, nas linhas abaixo ele atualiza e continua procurando
        ant=atual;
        if(valor>atual->info)
            atual= atual->dir;
        else
            atual= atual->esq;
    }
    return 0;
}
//pela direita:
struct NO* removeAtualDir(struct NO* atual){
    //tratando o caso de no com um filho ou zero filhos
    struct NO *no1, *no2;
    if(atual->esq==NULL){
        no2=atual->dir;
        free(atual);
        return no2;
    }
    //caso tenha mais de um, abaixo ira procurar o no mais a direita para colocar na posicao do que sera removido
    no1= atual;
    no2= atual->esq;
    while(no2->dir!= NULL){
        no1= no2;
        no2= no2->dir;
    }
    //coloca no lugar:
    if(no1!=atual){
        no1->dir= no2->esq;
        no2->esq= atual->esq;
    }
    //libera:
    no2->dir=atual->dir;
    free(atual);
    return no2;
}
//pela esquerda:
struct NO* removeAtualEsq(struct NO* atual){
    //tratando o caso de no com zero filhos
    struct NO *no1, *no2;
    //com um filho:
    if(atual->dir==NULL){
        no2=atual->esq;
        free(atual);
        return no2;
    }
    if(atual->esq==NULL){
        no2=atual->dir;
        free(atual);
        return no2;
    }
    //caso tenha mais de um, abaixo ira procurar o no mais a direita para colocar na posicao do que sera removido
    no1= atual;
    no2= atual->dir;
    while(no2->esq!= NULL){
        no1= no2;
        no2= no2->esq;
    }
    //coloca no lugar:
    if(no1!=atual){
        no1->esq= no2->dir;
        no2->dir= atual->dir;
    }
    //libera:
    no2->esq=atual->esq;
    free(atual);
    return no2;
}
//----busca----
int consulta_arvBin(arvBin *raiz, int valor){
    if(raiz== NULL)
        return 0;
    struct NO* atual=*raiz;
    while(atual!=NULL){
        //retorna 1 se encontrou o valor
        if(valor==atual->info)
            return 1;
        //caso nao tenha encontrado, continua percorrendo
        if(valor>atual->info)
            atual= atual->dir;
        else
            atual=atual->esq;
    }
    return 0;
}
/*
//----solucao----
int resposta(arvBin *raiz){
    if(raiz== NULL)
        return 0;
    struct NO* atual=*raiz;
    int acumulador=0;

    while(atual!=NULL){
        printf("atual=%d\n",atual->info );
        printf("dir =%d\n", atual->dir->info);

        if(atual->info<atual->dir){
            atual= atual->dir;
        }
        else{
            atual=atual->esq;
        }
    }

    return 1;
}
*/
int resposta(arvBin *raiz, int parada){
    if(raiz==NULL)
        return;

    if(*raiz!=NULL ){


        if((*raiz)->info==parada){
            return 1;
        }
        resposta(&((*raiz)->esq), parada);
        if(&((*raiz)->esq)!=NULL && (&((*raiz)->dir)!=NULL)){
            acumulador= acumulador+ (*raiz)->esq->info+(*raiz)->dir->info;
        }
        resposta(&((*raiz)->dir), parada);

    }
    return 1;

}
