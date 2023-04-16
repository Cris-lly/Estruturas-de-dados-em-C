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
        printf("Escolha a opera��o:\n");
        printf("1- Inser��o\n");
        printf("2- Remo��o\n");
        printf("3- Consulta\n");
        scanf("%d", &escolha);
    }while(escolha<1 && escolha>3);
    switch(escolha){
        int teste;
        case 1:
            do{
                printf("Escolha a opera��o:\n");
                printf("1- Inserir no in�cio\n");
                printf("2- Inserir no meio\n");
                printf("3- Inserir no fim\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);
            printf("----digite seus dados----\n");
            printf("NOME:\n");
            scanf("%s", &alunoCad.nome);
            printf("MATR�CULA:\n");
            scanf("%d", &alunoCad.matricula);
            for(i=0; i<4;i++){
                printf("DIGITE A %d� NOTA:\n", i+1);
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
                printf("Escolha a opera��o:\n");
                printf("1- Remover no in�cio\n");
                printf("2- Remover no meio\n");
                printf("3- Remover no fim\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);
            if(escolha==1)
                    removeInicio(li);
            else
                if(escolha==2){
                    printf("Digite o n�mero de matr�cula para fazer a remo��o:\n");
                    scanf("%d", &mat);
                    removeMeio(li, mat);
                }
                else
                    removeFim(li);
            printf("Removido com sucesso!\n");
            break;
        case 3:
            do{
                printf("Escolha a opera��o:\n");
                printf("1- Consultar tamanho da lista\n");
                printf("2- Consultar status da lista(cheia ou vazia)\n");
                printf("3- Buscar elemento da lista\n");
                printf("4- Buscar por posi��o da lista\n");
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
                        printf("Digite o n�mero da matr�cula:");
                        scanf("%d", &mat);
                        if(buscaElemento(li, mat, &dadosResult)){
                            printf("NOME= %s\n", dadosResult.nome);
                            printf("MATR�CULA= %d\n", dadosResult.matricula);
                            printf("M�DIA= %2.f\n", dadosResult.media);
                        }
                        else
                            printf("Aluno n�o encontrado!\n");
                    }else{
                        int pos;
                        printf("Digite a posi��o:\n");
                        scanf("%d", &pos);
                        if(buscaPosicao(li, pos, &dadosResult)){
                            printf("NOME= %s\n", dadosResult.nome);
                            printf("MATR�CULA= %d\n", dadosResult.matricula);
                            printf("M�DIA= %2.f\n", dadosResult.media);
                        }
                        else
                            printf("Posi��o vazia ou inv�lida!\n");
                    }

    }
    do{
        printf("Deseja fazer outra opera��o?\n");
        printf("1-SIM\n");
        printf("2-N�O\n");
        scanf("%d", &escolha);
    }while(escolha<1&&escolha>2);
    if(escolha==1){
        system("cls");
        goto TELA;
    }
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
            ponteiroAux= *li;
            //o ponteiro passa a apontar para o pr�ximo, percorre a lista.
            *li = (*li)->prox;
            free(ponteiroAux);
        }
        //depois libera, quando o ponteiro passa a apontar para o null
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

    /*verificando se a lista n�o estava vazia anteriormente.
    se n�o tiver, mudar dire��o para onde o primeiro apontava*/
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
        //n�o encontrou
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
