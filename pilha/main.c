#include <stdio.h>
#include <stdlib.h>
#include "BiblioPilha.h"
int main()
{

    return 0;
}
//criacao e liberacao
Pilha* criaPilha(){
    Pilha* pi= (Pilha*)malloc(sizeof(Pilha));
    if(pi!=NULL)
        pi->qtdd=0;
    return pi;
}
void liberaPilha(Pilha* pi){
    free(pi);
}
//consultas sobre a pilha
int tamanho(Pilha* pi){
    if(pi== NULL)
        return -1;
    return pi->qtdd;
}
int pilhaCheia(Pilha* pi){
    if(pi== NULL)
        return -1;
    return (pi->qtdd== MAX);
}
int pilhaVazia(Pilha* pi){
    if(pi== NULL)
        return -1;
    return (pi->qtdd==0);
}
//insercao
int inserir(Pilha* pi, AlunoCad dadosCad){
    if(pi== NULL|| pi->qtdd==MAX)
        return 0;
    pi->dados[pi->qtdd]= dadosCad;
    pi->qtdd++;
    return 1;
}
//remocao
int remover(Pilha* pi){
    if(pi== NULL || pi->qtdd==0)
        return 0;
    pi->qtdd--;
    return 1;
}
//consultar pilha
int consulta(Pilha* pi, AlunoCad *dadosCad){
    if(pi== NULL || pi->qtdd==0)
        return 0;
    *dadosCad= pi->dados[pi->qtdd-1];
    return 1;
}
//funcao de comparacao
int compare(Pilha* pi[], int qtddElem[]){
    int i, cont=0, dadosPiUm, dadosPiDois;
    //verificando primeira hipotese: se tamanho eh diferente
    //c1= 1
    if(tamanho(pi[0])!= tamanho(pi[1])){
        printf("NAO");
        return 0;
    }
    //consultando e armazenando o conteudo da pilha em uma variavel auxiliar
    //c2= n
    for(i=0; i<qtddElem[0]; i++){
        consulta(pi[0], &dadosPiUm);
        remover(pi[0]);
        consulta(pi[1], &dadosPiDois);
        remover(pi[1]);
        //caso o conteudo retornado seja igual, acrescenta +1 ao contador
        //c3=1
        if(dadosPiUm==dadosPiDois){
            cont++;
        }
    }
    //se contador for igual ao numero de elementos, implica que percorreu toda a pilha e todos sao iguais
    //c4= 1
    if(cont==qtddElem[0])
        printf("SIM");
    //se nao,pilhas consultadas sao diferentes
    else
        printf("NAO");

    /*
    analise de algoritmo:

    custo: c1, c2, c3 e c4
    funcao: 1+n+1+1= n+3
    complexidade: O(n)
    */
    return 1;

}
