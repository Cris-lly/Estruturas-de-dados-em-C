#include <stdio.h>
#include <stdlib.h>
//arquivo.h
typedef struct NO *arvAVL;
typedef struct NO No;
//prototipo das funcoes:
//----criacao----
arvAVL* criaArv_Avl();
//----liberar----
void liberaRaiz(arvAVL* raiz);
void liberaNo(struct NO* no);
//----informacoes sobre a arvore----
int vaziaArvBin(arvAVL* raiz);
int alturaNo(struct NO* no);
int fatorBalance_no(struct NO* no);
No* balancear(No *raiz);
int maior(int x, int y);
int alturaArv_Avl(arvAVL* raiz);
int totalNoArv_Avl(arvAVL* raiz);
//----percorrendo a arvore----
void preOrdemArv_Avl(arvAVL *raiz);
void emOrdemArv_Avl(arvAVL *raiz);
void posOrdemArv_Avl(arvAVL *raiz);
//----rotacoes da arvore----
No* rotacaoDireita(No* raiz);
No* rotacaoEsquerda(No* raiz);
No* rotacaoDireitaEsquerda(No* raiz);
No* rotacaoEsquerdaDireita(No* raiz);
//----insercao----
No* inserir(No *raiz, int x);
//remocao
No* removeAvl (No* raiz, int valor);
struct NO* procuraMenor(struct NO* atual);
//----busca----
int consulta_arvBin(arvAVL *raiz, int valor);
struct NO{
    struct NO *esq;
    //diferente da arvore binaria
    int alt;
    int info;
    struct NO *dir;
};
int main()
{
    arvAVL* raiz= criaArv_Avl();
    int i, qtddElem,elemRemove,elem;
    scanf("%d", &qtddElem);
    scanf("%d", &elemRemove);
    for(i=0; i<qtddElem; i++){
        scanf("%d", &elem);
        (*raiz)=inserir((*raiz), elem);
    }

    for(i=0; i<elemRemove; i++){
        scanf("%d", &elem);
        (*raiz)=removeAvl((*raiz), elem);
    }

    preOrdemArv_Avl(raiz);
    printf("\n");
    posOrdemArv_Avl(raiz);
    printf("\n");

    return 0;
}
//----criacao----
arvAVL* criaArv_Avl(){
    arvAVL* raiz= (arvAVL*)malloc(sizeof(arvAVL));
    if(raiz!=NULL)
        *raiz= NULL;
    return raiz;
}
//----liberar----
void liberaRaiz(arvAVL* raiz){
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
int vaziaArvBin(arvAVL* raiz){
    if(raiz==NULL || *raiz==NULL)
        return 1;
    return 0;
}
//altura do no
int alturaNo(struct NO* no){
    if(no==NULL)
        return -1;
    return no->alt;
}
//fator de balanceamento do no
int fatorBalance_no(struct NO* no){
    return alturaNo(no->esq)- alturaNo(no->dir);
}
No* balancear(No *raiz){
    short fb= fatorBalance_no(raiz);
    //rotacao a esquerda
    if(fb< -1 && fatorBalance_no(raiz->dir)<=0)
        raiz= rotacaoEsquerda(raiz);
    //rotacao a direita
    else
        if(fb>1 &&fatorBalance_no(raiz->esq)>=0)
            raiz= rotacaoDireita(raiz);
    //rotacao dupla a esquerda
        else
            if(fb>1 &&fatorBalance_no(raiz->esq)<0)
                raiz= rotacaoEsquerdaDireita(raiz);
    //rotacao dupla a direita
            else
                if(fb<-1 && fatorBalance_no(raiz->dir)>0)
                    raiz= rotacaoDireitaEsquerda(raiz);
    return raiz;
}
//maior valor
int maior(int x, int y){
    if(x>y)
        return x;
    else
        return y;
}
//altura da arvore
int alturaArv_Avl(arvAVL* raiz){
    if(raiz==NULL || *raiz==NULL)
        return 0;
    int alt_esq= alturaArv_Avl(&((*raiz)->esq));
    int alt_dir= alturaArv_Avl(&((*raiz)->dir));
    if(alt_esq>alt_dir)
        return(alt_esq+1);
    else
        return(alt_dir+1);
}
//Quantidade de no
int totalNoArv_Avl(arvAVL* raiz){
    if(raiz==NULL || *raiz==NULL)
        return 0;
    int alt_esq= totalNoArv_Avl(&((*raiz)->esq));
    int alt_dir= totalNoArv_Avl(&((*raiz)->dir));
    return(alt_esq+alt_dir+1);
}
//----percorrendo a arvore----
//pre-ordem
void preOrdemArv_Avl(arvAVL *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        printf("%d ", (*raiz)->info);
        preOrdemArv_Avl(&((*raiz)->esq));
        preOrdemArv_Avl(&((*raiz)->dir));
    }
}
//em-ordem
void emOrdemArv_Avl(arvAVL *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        emOrdemArv_Avl(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        emOrdemArv_Avl(&((*raiz)->dir));
    }
}
//pos-ordem
void posOrdemArv_Avl(arvAVL *raiz){
    if(raiz==NULL)
        return;
    if(*raiz!=NULL){
        posOrdemArv_Avl(&((*raiz)->esq));
        posOrdemArv_Avl(&((*raiz)->dir));
        printf("%d ", (*raiz)->info);
    }
}
//----rotacoes da arvore----
//rotacao LL-simples a direita
No* rotacaoDireita(No* raiz){
    No *no1,*filhoNo1;
    //atribuindo os valores
    no1= raiz->esq;
    filhoNo1= no1->dir;

    no1->dir= raiz;
    raiz->esq= filhoNo1;

    raiz->alt= maior(alturaNo(raiz->esq), alturaNo(raiz->dir))+1;
    no1->alt= maior(alturaNo(no1->esq), alturaNo(no1->dir))+1;

    return no1;
}
//rotacao LR- simples a esquerda
No* rotacaoEsquerda(No* raiz){
    No *no1,*filhoNo1;
    no1= raiz->dir;
    filhoNo1= no1->esq;

    no1->esq= raiz;
    raiz->dir= filhoNo1;

    raiz->alt= maior(alturaNo(raiz->esq), alturaNo(raiz->dir))+1;
    no1->alt= maior(alturaNo(no1->esq), alturaNo(no1->dir))+1;

    return no1;
}
//rotacao direita esquerda
No* rotacaoDireitaEsquerda(No* raiz){
    raiz->dir= rotacaoDireita(raiz->dir);
    return rotacaoEsquerda(raiz);
}
//rotacao esquerda direita
No* rotacaoEsquerdaDireita(No* raiz){
    raiz->esq= rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
}


//----insercao----
No* inserir(No *raiz, int x){

    if(raiz==NULL){
        //criando o novo no da minha arvore
        struct NO* novo;
        novo= (struct NO*)malloc(sizeof(struct NO));
        if(novo==NULL)
            return NULL;
        //setando os dados do novo no
        novo->info= x;
        novo->alt=0;
        novo->dir= NULL;
        novo->esq= NULL;
        return novo;
    }

    else{ // insercao sera a esquerda ou a direita
        if(x < raiz->info)
            raiz->esq = inserir(raiz->esq, x);
        else if(x > raiz->info)
            raiz->dir = inserir(raiz->dir, x);
        else
            return raiz;
    }

    // Recalcula a altura de todos os nos entre a raiz e o novo no inserido
    raiz->alt = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

    // verifica a necessidade de rebalancear a arvore
    raiz = balancear(raiz);

    return raiz;
}
//----remocao----
No* removeAvl (No* raiz, int valor) {
    if (raiz == NULL)
        return 0;

    if (valor < raiz->info)
        raiz->esq = removeAvl(raiz->esq, valor);
    else if (valor > raiz->info)
        raiz->dir = removeAvl(raiz->dir, valor);
    else {
        // Caso tenha 0 ou 1 filhos:
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            No *aux = raiz->esq ? raiz->esq : raiz->dir;

            // para 0 filhos:
            if (aux == NULL) {
                aux = raiz;
                raiz = NULL;
            }
            else //caso 1 filho:
                *raiz = *aux;
            free(aux);
        }
        //se tiver 2:
        else  {
            No* aux = procuraMenor(raiz->dir);
            raiz->info = aux->info;
            raiz->dir = removeAvl(raiz->dir, aux->info);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->alt = maior(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

    raiz = balancear(raiz);
    return raiz;
}
struct NO* procuraMenor(struct NO* atual){
    //funcao responsavel por tratar a remocao de um no com 2 filhos
    //procura pelo no mais a esquerda
    struct NO* no1=atual;
    struct NO* no2=atual->esq;
    while(no2!=NULL){
        no1=no2;
        no2= no2->esq;
    }
    return no1;
}
//----busca----
int consulta_arvBin(arvAVL *raiz, int valor){
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
