#include <stdio.h>
#include <stdlib.h>
#include "ListaduplaEncad.h"
#include <locale.h>
int main()
{
    setlocale(LC_ALL, "portuguese");
    int escolha, i, j=0, mat;
    float count=0;
    Lista* li= criaLista();
    DadosAlunos alunoCad,dadosResult;

    TELA:
    do{
        printf("Escolha a operação:\n");
        printf("1- Inserção\n");
        printf("2- Remoção\n");
        printf("3- Consulta\n");
        scanf("%d", &escolha);
    }while(escolha<1 && escolha>3);
    switch(escolha){
        int teste;
        case 1:
            do{
                printf("Escolha a operação:\n");
                printf("1- Inserir no início\n");
                printf("2- Inserir no meio\n");
                printf("3- Inserir no fim\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);
            printf("----digite seus dados----\n");
            printf("NOME:\n");
            scanf("%s", &alunoCad.nome);
            printf("MATRÍCULA:\n");
            scanf("%d", &alunoCad.matricula);
            for(i=0; i<4;i++){
                printf("DIGITE A %dª NOTA:\n", i+1);
                scanf("%f", &alunoCad.nota[i]);
                count+= alunoCad.nota[i];
            }
            alunoCad.media= count/4;
            count=0;
            if(escolha==1)
                insereInicio(li, alunoCad);
            else
                if(escolha==2)
                    insereMeio(li, alunoCad);
                else
                    insereFim(li, alunoCad);
            printf("Inserido com sucesso!\n");
            break;
        case 2:
            do{
                printf("Escolha a operação:\n");
                printf("1- Remover no início\n");
                printf("2- Remover no meio\n");
                printf("3- Remover no fim\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);
            if(escolha==1)
                    removeInicio(li);
            else
                if(escolha==2){
                    printf("Digite o número de matrícula para fazer a remoção:\n");
                    scanf("%d", &mat);
                    removeMeio(li, mat);
                }
                else
                    removeFim(li);
            printf("Removido com sucesso!\n");
            break;
        case 3:
            do{
                printf("Escolha a operação:\n");
                printf("1- Consultar tamanho da lista\n");
                printf("2- Consultar status da lista(cheia ou vazia)\n");
                printf("3- Buscar elemento da lista\n");
                printf("4- Buscar por posição da lista\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>4);
            if(escolha==1)
                printf("Tamanho da lista: %d\n",tamanho(li));
            else
                if(escolha==2){
                    if(listaVazia(li))
                        printf("lista vazia!\n");
                    else
                        printf("Ainda pode inserir elementos!\n");
                }
                else
                    if(escolha==3){
                        printf("Digite o número da matrícula:");
                        scanf("%d", &mat);
                        if(buscaElemento(li, mat, &dadosResult)){
                            printf("NOME= %s\n", dadosResult.nome);
                            printf("MATRÍCULA= %d\n", dadosResult.matricula);
                            printf("MÉDIA= %2.f\n", dadosResult.media);
                        }
                        else
                            printf("Aluno não encontrado!\n");
                    }else{
                        int pos;
                        printf("Digite a posição:\n");
                        scanf("%d", &pos);
                        if(buscaPosicao(li, pos, &dadosResult)){
                            printf("NOME= %s\n", dadosResult.nome);
                            printf("MATRÍCULA= %d\n", dadosResult.matricula);
                            printf("MÉDIA= %2.f\n", dadosResult.media);
                        }
                        else
                            printf("Posição vazia ou inválida!\n");
                    }

    }
    do{
        printf("Deseja fazer outra operação?\n");
        printf("1-SIM\n");
        printf("2-NÃO\n");
        scanf("%d", &escolha);
    }while(escolha<1&&escolha>2);
    if(escolha==1){
        system("cls");
        goto TELA;
    }
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
            ponteiroAux= *li;
            //o ponteiro passa a apontar para o próximo, percorre a lista.
            *li = (*li)->prox;
            free(ponteiroAux);
        }
        //depois libera, quando o ponteiro passa a apontar para o null
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

    while(pontAux!=NULL){
        pontAux= pontAux->prox;
        tamanhoLista++;
    }
    return tamanhoLista;
}
int listaCheia(Lista* li){
    return 0;
}
int listaVazia(Lista* li){
    if(li==NULL)
        return 1;
    if(*li==NULL)
        return 1;
    return 0;
}
int insereInicio(Lista* li, DadosAlunos dados){
    if(li==NULL)
        return 0;
    lista* elemento= (lista*)malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    elemento->ant= NULL;
    elemento->dados= dados;
    elemento->prox= NULL;

    /*verificando se a lista não estava vazia anteriormente.
    se não tiver, mudar direção para onde o primeiro apontava*/
    if((*li)!= NULL)
        (*li)->ant= elemento;
    *li= elemento;
    return 1;
}
int insereMeio(Lista* li, DadosAlunos dados){
    if(li==NULL)
        return 0;
    lista* elemento= (lista*)malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    elemento->dados= dados;

    if((*li)==NULL){
        elemento->ant=NULL;
        elemento->prox=NULL;
        *li= elemento;
    }
    else{
        lista *ant, *atual=*li;
        while(atual!=NULL && atual->dados.matricula<dados.matricula){
            ant= atual;
            atual= atual->prox;
        }
        elemento->prox= ant->prox;
        elemento->ant= ant;
        ant->prox= elemento;
        if(atual!= NULL)
            atual->ant= elemento;
    }
    return 1;
}
int insereFim(Lista* li, DadosAlunos dados){
    if(li==NULL)
        return 0;
    lista* elemento= (lista*)malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;

    elemento->dados= dados;
    elemento->prox= NULL;

    if((*li)==NULL){
        elemento->ant=NULL;
        *li= elemento;
    }
    else{
        lista* aux=*li;
        while(aux->prox!=NULL)
            aux= aux->prox;
        aux->prox=elemento;
        elemento->ant= aux;
    }
    return 1;
}
//consultas
int buscaPosicao(Lista* li, int posicao, DadosAlunos *dados){
    if(li==NULL)
        return 0;
    lista* aux= *li;
    int cont=1;
    while(aux!= NULL && cont<posicao){
        aux= aux->prox;
        cont++;
    }
    if(aux==NULL)
        return 0;
    else
        *dados= aux->dados;
    return 1;
}
int buscaElemento(Lista* li, int mat, DadosAlunos *dados){
    if(li==NULL)
        return 0;
    lista* ponte= *li;
    while(ponte!= NULL && ponte->dados.matricula != mat)
        ponte= ponte->prox;
    if(ponte==NULL)
        return 0;
    else
        *dados= ponte->dados;
        return 1;
}

//remover
int removeInicio(Lista* li){
    if(li==NULL|| *li==NULL)
        return 0;
    lista *aux=*li;
    *li= (*li)->prox;
    if(*li!=NULL)
        (*li)->ant= NULL;
    free(aux);
    return 1;
}
int removeMeio(Lista* li, int matricula){
    if(li==NULL ||*li==NULL)
        return 0;
    lista *aux=*li;
    while(aux->prox!= NULL && aux->dados.matricula!= matricula){
        aux= aux->prox;
    }
    if(aux==NULL)
        //não encontrou
        return 0;
    if(aux->ant==NULL)
        *li= aux->prox;
    aux->ant->prox= aux->prox;
    if(aux->prox!=NULL)
        aux->prox->ant=aux->ant;
    free(aux);
}
int removeFim(Lista* li){
    if(li==NULL ||*li==NULL)
        return 0;
    lista *atual=*li;
    while(atual->prox!= NULL){
        atual= atual->prox;
    }
    if(atual==*li)
    //ou if(atual->ant==NULL)
        *li=atual->prox;
    atual->ant->prox= atual->prox;
    //ou atual->ant->prox= NULL;
    free(atual);
    return 1;
}
