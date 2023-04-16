#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "filaBiblio.h"
struct fila{
    int qtdd;
    int inicio;
    Agenda dados[MAX];
    int fim;
};
int main()
{
    setlocale(LC_ALL, "portuguese");
    int escolha;
    Fila* fi= criaFila();
    Agenda dados,dadosCons;
    TELA:
    do{
        printf("Escolha uma opera��o:\n");
        printf("1-Criar novo evento\n");
        printf("2-Deletar evento antigo\n");
        printf("3-Consultar evento\n");
        printf("4-verificar quantidade de eventos\n");
        printf("5-verificar se h� eventos ou chegou a capacidade m�xima\n");
        scanf("%d", &escolha);
    }while(escolha<1 && escolha>5);
    switch(escolha){
        case 1:
            printf("Digite o nome do evento:\n");
            scanf("%s", dados.evento);
            printf("Digite o dia:\n");
            scanf("%d", &dados.dia);
            inserir(fi, dados);
        break;
        case 2:
            if(remover(fi))
                printf("Removido com sucesso!\n");
            else
                printf("erro ao remover!\n");
        break;
        case 3:
            if(consulta(fi, &dadosCons))
                printf("nome do pr�ximo evento e dia: %s, %d\n", dadosCons.evento, dadosCons.dia);
            else
                printf("Erro ao consultar!\n");
        break;
        case 4:
            printf("Quantidade de eventos: %d\n", tamanho(fi));
        break;
        case 5:
            if(FilaCheia(fi))
                printf("limite m�ximo de eventos atingido!\n");
            else
                if(FilaVazia(fi))
                    printf("nenhum evento encontrado!\n");
                else
                    printf("erro ao executar opera��o!\n");
    }

    do{
        printf("Realizar outra opera��o?\n");
        printf("1-Sim\n");
        printf("2-N�o\n");
        scanf("%d", &escolha);
    }while(escolha<1 && escolha>2);
    if(escolha==1)
        goto TELA;
    return 0;
}

//-----criar e liberar-----
Fila* criaFila(){
    Fila* fi= (Fila*) malloc(sizeof(Fila));
    if(fi!=NULL){
        fi->inicio= 0;
        fi->qtdd= 0;
        fi->fim=0;
    }
    return fi;
}
void liberaFila(Fila* fi){
    free(fi);
}
//-----Info sobre a fila-----
int tamanho(Fila* fi){
    if(fi==NULL)
        return -1;
    return fi->qtdd;
}
int FilaCheia(Fila* fi){
    if(fi==NULL)
        return -1;
    return (fi->qtdd==MAX);
}
int FilaVazia(Fila* fi){
    if(fi==NULL)
        return -1;
    return (fi->qtdd==0);
}
//-----Inserir dados na fila-----
int inserir(Fila* fi, Agenda dadosCad){
    if(fi ==NULL || fi->qtdd==MAX)
        return 0;
    fi->dados[fi->fim]= dadosCad;
    /*- depois que ele chega no final, quando a fila n�o t� cheia
     e h� posi��es vagas no in�cio, ele insere na parte vaga, fazendo,assim
     a fila simular uma fila circular
     -n�o h� risco de inserir em posi��o j� alocada, porque quando a lista j� t� completa
     por causa da verifica��o anterior ele n�o deixa chegar nessa etapa*/
    fi->fim= (fi->fim+1)%MAX;
    fi->qtdd++;
    return 1;
}
int remover(Fila* fi){
    if(fi==NULL || fi->qtdd==0)
        return 0;
    //passando o novo valor do inicio
    fi->inicio= (fi->inicio+1)%MAX;
    /* em uma fila n�o precisa dizer qual � o dado,
    em qual posi��o ser� tirado, pois n�o importa, j� como a remo��o �
    sempre a mesma(remo��o inicial)*/
    fi->qtdd--;
    return 1;
}
//-----Consulta-----
int consulta(Fila* fi, Agenda *dadosCons){
    if(fi== NULL ||fi->qtdd==0)
        return 0;
    *dadosCons= fi->dados[fi->inicio];
    return 1;
}
