#include <stdio.h>
#include <stdlib.h>
#include "pilhaDina.h"
int main()
{
    printf("Hello world!\n");
    return 0;
}
Pilha* criaPilha(){
    Pilha* pi= (Pilha*)malloc(sizeof(Pilha));
    if(pi!=NULL)
        *pi=NULL;
    return pi;
}
void liberaPilha(Pilha* pi){
    if(pi!=NULL){
        Elem* ponteiroAux;
        while((*pi)!=NULL){
            ponteiroAux= *pi;
            //o ponteiro passa a apontar para o próximo, percorre a lista.
            *pi = (*pi)->prox;
            free(ponteiroAux);
        }
        //depois libera, quando o ponteiro passa apontar para o null
        free(pi);
    }
}
int tamanho (Pilha* pi){
    if(pi==NULL)
        return -1;
    Elem *aux= *pi;
    int tam=0;
    while(aux!=NULL){
        aux = aux->prox;
        tam++;
    }
    return tam;
}
int pilhaCheia(Pilha* pi){
    return 0;
}
int pilhaVazia(Pilha* pi){
    if(pi==NULL || (*pi)==NULL)
        return 1;
    return 0;
}
int inserir(Pilha* pi, Aluno dadosCad){
    if(pi==NULL)
        return 0;
    Elem* elemento= (Elem*)malloc(sizeof(Elem));
    if(elemento==NULL)
        return 0;
    elemento->dados= dadosCad;
    elemento->prox= (*pi);
    *pi= elemento;
    return 1;

}
int remover(Pilha* pi){
    if(pi==NULL || (*pi)==NULL)
        return 0;
    Elem *aux= *pi;
    //recebe o antigo valor antes do que já estava
    *pi= aux->prox;
    free(aux);
    return 1;
}
int consulta(Pilha* pi, Aluno *dadosConsul ){
    if(pi==NULL || (*pi)==NULL)
        return 0;
    *dadosConsul= (*pi)->dados;
    return 1;
}
