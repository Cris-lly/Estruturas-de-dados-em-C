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
        printf("Escolha uma operação:\n");
        printf("1-Criar novo evento\n");
        printf("2-Deletar evento antigo\n");
        printf("3-Consultar evento\n");
        printf("4-verificar quantidade de eventos\n");
        printf("5-verificar se há eventos ou chegou a capacidade máxima\n");
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
                printf("nome do próximo evento e dia: %s, %d\n", dadosCons.evento, dadosCons.dia);
            else
                printf("Erro ao consultar!\n");
        break;
        case 4:
            printf("Quantidade de eventos: %d\n", tamanho(fi));
        break;
        case 5:
            if(FilaCheia(fi))
                printf("limite máximo de eventos atingido!\n");
            else
                if(FilaVazia(fi))
                    printf("nenhum evento encontrado!\n");
                else
                    printf("erro ao executar operação!\n");
    }

    do{
        printf("Realizar outra operação?\n");
        printf("1-Sim\n");
        printf("2-Não\n");
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
    /*- depois que ele chega no final, quando a fila não tá cheia
     e há posições vagas no início, ele insere na parte vaga, fazendo,assim
     a fila simular uma fila circular
     -não há risco de inserir em posição já alocada, porque quando a lista já tá completa
     por causa da verificação anterior ele não deixa chegar nessa etapa*/
    fi->fim= (fi->fim+1)%MAX;
    fi->qtdd++;
    return 1;
}
int remover(Fila* fi){
    if(fi==NULL || fi->qtdd==0)
        return 0;
    //passando o novo valor do inicio
    fi->inicio= (fi->inicio+1)%MAX;
    /* em uma fila não precisa dizer qual é o dado,
    em qual posição será tirado, pois não importa, já como a remoção é
    sempre a mesma(remoção inicial)*/
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
