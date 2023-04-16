#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "listaCircular.h"
typedef struct lista{
    Agenda cadAgenda;
    struct lista *prox;
}lista;
int main(){
    //---PROJETO AGENDA MENSAL---
    setlocale(LC_ALL, "portuguese");
    Lista* li=criaLista();
    Agenda dados, dadosResult;
    int escolha,dia, controle;
    TELA:
     do{
        printf("Escolha uma opera��o:\n");
        printf("1-Criar novo evento\n");
        printf("2-Deletar evento\n");
        printf("3-Consultar evento\n");
        printf("4-verificar quantidade de eventos\n");
        scanf("%d", &escolha);
    }while(escolha<1 && escolha>4);
    switch(escolha){
        case 1:
            do{
                printf("-----Criar um novo evento-----\n");
                printf("Escolha a op��o:\n");
                printf("Seu evento ocorrer� no:\n");
                printf("1-inicio do m�s\n");
                printf("2-meio do m�s\n");
                printf("3-fim do m�s\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);

            printf("Digite o nome do evento:\n");
            scanf("%s", dados.evento);
            printf("Digite o dia:");
            scanf("%d", &dados.dia);

            if(escolha==1){
                    controle=insereInicio(li, dados);
                    if(controle)
                        printf("Inserido com sucesso!\n");
                    else
                        printf("Erro ao inserir\n");
            }
            else
                if(escolha==2){
                    controle=insereMeio(li, dados);
                    if(controle)
                        printf("Inserido com sucesso!\n");
                    else
                        printf("Erro ao inserir\n");
                }
                else{
                    controle=insereFim(li, dados);
                    if(controle)
                        printf("Inserido com sucesso!\n");
                    else
                        printf("Erro ao inserir\n");
                }
        break;
        case 2:
            do{
                printf("Voc� deseja:\n");
                printf("1-Deletar primeiro evento do m�s\n");
                printf("2-Deletar �ltimo evento do m�s\n");
                printf("3-Deletar evento espec�fico\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);
            if(escolha==1)
                    removeInicio(li);
            else
                if(escolha==2)
                    removeFim(li);
                else{
                    printf("Digite o dia do evento\n");
                    scanf("%d", &dia);
                    removeMeio(li, dia);
                }
        break;
        case 3:
            do{
                printf("Voc� deseja:\n");
                printf("1-buscar um evento em espec�fico\n");
                printf("2-buscar a posic�o do evento(ex.: 1� evento que ocorrer� no m�s)\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>2);

            if(escolha==1){
                if(tamanho(li)>0){
                    printf("Digite o dia do evento\n");
                    scanf("%d", &dia);
                    buscaElem(li, dia, &dadosResult);
                    printf("nome do evento: %s\n", dadosResult.evento);

                }else
                    printf("Erro ao iniciar opera��o, verifique se h� eventos cadastrados!\n");
            }
            else
                if(escolha==2){
                    int posicao;
                    printf("Digite o n�mero da posi��o do evento\n");
                    scanf("%d", &posicao);
                    buscaPosicao(li, posicao, &dadosResult);
                    printf("nome do evento: %s\n", dadosResult.evento);
                    printf("dia do evento: %d\n", dadosResult.dia);
                }
        break;
        case 4:
            do{
                printf("Voc� deseja:\n");
                printf("1-Verificar quantidade total de eventos\n");
                printf("2-Verificar se atingiu o limite m�ximo de eventos\n");
                printf("3-Verificar se a agenda  mensal de eventos est� vazia\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);

            if(escolha==1){
                if(tamanho(li)>=0)
                    printf("total de eventos no m�s: %d\n", tamanho(li));
                else
                    printf("Erro ao realizar a opera��o!\n");
            }
            else
                if(escolha==2){
                    if(listaCheia(li))
                        printf("N�o h� espa�o dispon�vel para armazenar eventos!\n");
                    printf("Ainda h� espa�o dispon�vel para armazenar eventos!\n");
                }
                else
                    if(listaVazia(li))
                        printf("Agenda vazia!\n");
                    else
                        printf("Agenda j� possui eventos cadastrados!\n");
    }

    do{
        printf("Realizar outra opera��o?\n");
        printf("1-Sim\n");
        printf("2-N�o\n");
        scanf("%d", &escolha);
    }while(escolha<1 && escolha>2);
    if(escolha==1){
        system("cls");
        goto TELA;
    }
    liberaLista(li);
    return 0;
}
//-----cria e libera lista-----
Lista* criaLista(){
    Lista* li= (Lista*)malloc(sizeof(Lista));
    if(li!= NULL)
        *li= NULL;
    return li;
}
void liberaLista(Lista* li){
    if(li!=NULL && (*li)!=NULL){
        lista *aux, *copia=*li;
        while((*li)!=copia->prox){
            aux= copia;
            copia=copia->prox;
            free(aux);
        }
        free(copia);
        free(li);
    }
}
//-----informa��es da lista-----
int tamanho(Lista* li){
    if(li==NULL || (*li)==NULL)
        return -1;
    lista* aux= *li;
    int cont=0;
    do{
        aux= aux->prox;
        cont++;
    }while((*li)!=aux);
    return cont;
}
int listaCheia(Lista* li){
    return 0;
}
int listaVazia(Lista* li){
    if(li==NULL || (*li)==NULL)
        return 1;
    return 0;
}
//-----Inser��o-----
int insereInicio(Lista* li, Agenda dados){
    if(li==NULL)
        return 0;
    lista* elemento= (lista*)malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    elemento->cadAgenda= dados;
    if((*li)==NULL){
        *li= elemento;
        elemento->prox=elemento;
    }else{
        lista* aux= *li;
        while(aux->prox!=(*li))
            aux= aux->prox;
        aux->prox=elemento;
        //depois de fazer o elemento apontar para o inicio, modificou quem era o 1� elemento
        elemento->prox= *li;
        *li=elemento;
    }
    return 1;

}
int insereMeio(Lista* li, Agenda dados){
    if(li==NULL)
        return 0;
    lista* elemento= (lista*)malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    elemento->cadAgenda= dados;
    //verifica��o se a lista t� vazia
    if((*li)==NULL){
        *li= elemento;
        elemento->prox=elemento;
    }
    //verifica��o se vai inserir no inicio
    if((*li)->cadAgenda.dia> dados.dia){
        lista* aux= *li;
        while(aux->prox!=(*li))
            aux= aux->prox;
        aux->prox=elemento;
        //depois de fazer o elemento apontar para o inicio, modificou quem era o 1� elemento
        elemento->prox= *li;
        *li=elemento;
    }else{
        lista *ant=*li, *atual= (*li)->prox;
        while(atual!=(*li) && atual->cadAgenda.dia<dados.dia){
            ant= atual;
            atual=atual->prox;
        }
        //como ele gira uma �ltima vez no qual o atual fica maior que elemento, por isso o c�digo fica assim:
        ant->prox= elemento;
        elemento->prox= atual;
    }
    //opera��o para inserir em um canto qualquer(no meio)
    return 1;
}
int insereFim(Lista* li, Agenda dados){
    if(li==NULL)
        return 0;
    lista* elemento= (lista*)malloc(sizeof(lista));
    if(elemento==NULL)
        return 0;
    elemento->cadAgenda= dados;
    if((*li)==NULL){
        *li= elemento;
        elemento->prox=elemento;
    }else{
        lista* aux= *li;
        while(aux->prox!=(*li))
            aux= aux->prox;
        aux->prox=elemento;
        elemento->prox= *li;
        //n�o modifica quem � o primeiro elemento, s� adiciona
    }

    return 1;
}
//-----Remo��o------
int removeInicio(Lista* li){
    //verificando se a lista foi iniciada ou se tem algo nela
    if(li==NULL || (*li)==NULL)
        return 0;
    //verificando se s� tem 1 elemento
    if((*li)==(*li)->prox){
        free(*li);
        *li= NULL;
        return 1;
    }
    //achando �ltimo elemento
    lista *ult= *li;
    while(ult->prox!=*li)
        ult= ult->prox;
    //mudando o inicio e desalocando
    lista* primeiro= *li;
    ult->prox=primeiro->prox;
    *li=primeiro->prox;
    free(primeiro);
    return 1;
}
int removeMeio(Lista* li, int day){
    if(li==NULL || (*li)==NULL)
        return 0;
    //achando �ltimo elemento(desse jeito aqui, caso for o melhor caso, n entra no while
    lista* primeiro= *li;
    lista *pen=primeiro,*ult= primeiro->prox;
    while(ult->prox!=*li){
        pen= ult;
        ult= ult->prox;
    }
    //verificando se s� tem 1 elemento ou o primeiro elemento � o que ser� removido
    if(primeiro->cadAgenda.dia== day){
        if(primeiro==primeiro->prox){
            free(primeiro);
            *li= NULL;
            return 1;
        }
        //para caso ele for o primeiro elemento e a lista tiver mais itens:
        else{
            ult->prox=(*li)->prox;
            *li= (*li)->prox;
            free(primeiro);
            return 1;
        }
    }
    else{
        if(ult==*li)
            return 0;
        pen->prox=ult->prox;
        free(ult);
        return 1;
    }
}
int removeFim(Lista* li){
    if(li==NULL || (*li)==NULL)
        return 0;
    //verificando se s� tem 1 elemento
    if((*li)==(*li)->prox){
        free(*li);
        *li= NULL;
        return 1;
    }
    //achando �ltimo elemento
    lista *pen,*ult= *li;
    while(ult->prox!=*li){
        pen= ult;
        ult= ult->prox;
    }
    pen->prox=ult->prox;
    free(ult);
    return 1;
}
//-----Consultas-----
int buscaPosicao(Lista* li, int posicao, Agenda *dados){
    if(li==NULL || (*li)==NULL ||posicao<=0)
        return 0;
    lista* aux= *li;
    int cont=1;
    while((*li)!=aux->prox && cont<posicao){
        aux= aux->prox;
        cont++;
    }
    //por causa dessa condi��o o meu cont tem q iniciar com 1 e n�o com zero
    if (cont!= posicao)
        return 0;
    *dados= aux->cadAgenda;
    return 1;
}
int buscaElem(Lista* li, int day, Agenda *dados){
    if(li==NULL || (*li)==NULL)
        return 0;
    lista* aux= *li;
    while((*li)!=aux->prox && aux->cadAgenda.dia!=day)
        aux= aux->prox;

    if(aux->cadAgenda.dia!=day)
        return 0;
    else
        *dados= aux->cadAgenda;
    return 1;

}
