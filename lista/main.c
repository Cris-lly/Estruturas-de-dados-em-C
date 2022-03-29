#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioLista.h"
int main(){
    setlocale(LC_ALL,"portuguese");
    //tipo de dado lista e criação
    int i,matricula, escolha;
    float count=0.0;
    Lista *li= criaLista();
    DadosAlunos alunoCad, ponteiro;

    //Tela do usuário
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
            scanf(" %[^\n]s", alunoCad.nome);
            printf("MATRÍCULA:");
            scanf("%d", &alunoCad.matricula);
            for(i=0; i<4;i++){
                printf("DIGITE A %dª NOTA:\n", i+1);
                scanf("%f", &alunoCad.nota[i]);
                count+= alunoCad.nota[i];
            }
            alunoCad.media= count/4.0;
            if(escolha==1)
                inserirDadosInicio(li, alunoCad);
            else
                if(escolha==2)
                    inserirDadosMeio(li, alunoCad);
                else
                    inserirDadosFim(li, alunoCad);
            printf("Inserido com sucesso!\n");
            count= 0;
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
                    RemoveInicio(li);
            else
                if(escolha==2){
                    printf("Digite o número de matrícula para fazer a remoção:");
                    scanf("%d", &matricula);
                    RemoveMeio(li, matricula);
                }
                else
                    Removefim(li);
            printf("Removido com sucesso!\n");
            break;
        case 3:
            do{
                printf("Escolha a operação:\n");
                printf("1- Consultar tamanho da lista\n");
                printf("2- Consultar status da lista(cheia ou vazia)\n");
                printf("3- Buscar elemento da lista\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);
            if(escolha==1)
                printf("Tamanho da lista: %d\n",tamanho(li));
            else
                if(escolha==2){
                   if(listaCheia(li)==-1)
                        printf("Lista não inicializada");
                    else
                        if(listaCheia(li)==1)
                            printf("lista cheia!");
                        else
                            printf("lista vazia ou incompleta\n");
                            do{
                                printf("verificar tamanho?\n");
                                printf("1-SIM\n");
                                printf("2-NÃO\n");
                                scanf("%d", &escolha);
                            }while(escolha<1&&escolha>2);
                            if(escolha==1)
                                printf("Tamanho da lista: %d\n",tamanho(li));
                }
                else{
                    printf("Digite o número da matrícula:");
                    scanf("%d", &matricula);

                    if(BuscaElemAluno(li, matricula, &ponteiro)){
                        printf("NOME= %s\n", ponteiro.nome);
                        printf("MATRÍCULA= %d\n", ponteiro.matricula);
                        printf("MÉDIA= %.2f\n", ponteiro.media);
                    }
                    else
                        printf("Aluno não encontrado!\n");
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
    free(li);
    return 0;
}
//criei o espaço para começar a inserir algo
Lista* criaLista(){
    Lista* li=(Lista*) malloc(sizeof(Lista));
    if(li!=NULL)
        li->qtdd=0;
    return li;
}
//liberar a alocação feita ao decorrer da execução do programa
void libera(Lista* li){
    free(li);
}
//----inserção de dados na lista----
int inserirDadosInicio(Lista* li, DadosAlunos Alunos){
    /*verificação se a lista já foi inicializada, ou se está cheia*/
    if(li==NULL||li->qtdd==MAX )
        return 0;
    int i;
    //quando for o melhor caso(qtdd=0) ele não entra no for
    for(i=li->qtdd-1; i>=0; i--){
        li->dados[i+1]=li->dados[i];
    }
    li->dados[0]= Alunos;
    li->qtdd++;
    return 1;
}
int inserirDadosMeio(Lista* li, DadosAlunos Alunos){
    if(li==NULL||li->qtdd==MAX )
        return 0;
    int posicao=0,i;
    //percorrendo o array e comparando se é menor ou maior
    while(posicao<li->qtdd && li->dados[posicao].matricula<Alunos.matricula)
        //Ele serve como contador para saber a posição que o número irá ficar
        posicao++;
    for(i= li->qtdd-1; i>=posicao; i--)
        li->dados[i+1]= li->dados[i];
    li->dados[posicao]= Alunos;
    li->qtdd++;
    return 1;
}
int inserirDadosFim(Lista* li, DadosAlunos Alunos){
    /*verificação se a lista já foi inicializada, ou se está cheia*/
    if(li==NULL||li->qtdd==MAX )
        return 0;
    li->dados[li->qtdd]= Alunos;
    li->qtdd++;
    return 1;
}

//----Realizar consultas sobre a lista-----
int tamanho(Lista* li){
    if(li==NULL)
        // o -1 será retornado quando n tiver nenhuma lista inicializada
        return -1;
    return li->qtdd;
}
int listaCheia(Lista* li){
    if(li==NULL)
        return -1;
    //se a expressão dentro do parêntese satisfazer a igualdade retorna 1, senão retorna 0;
    return (li->qtdd==MAX);
}
int listaVazia(Lista* li){
    if(li==NULL)
        return -1;
    return (li->qtdd==0);
}
//----Realizar consultas sobre os dados da lista-----
int BuscaElemAluno(Lista* li, int alunoMat, DadosAlunos *ponteiro){
    if(li==NULL||li->qtdd==0 )
        return 0;
    int posicao=0;
    while(posicao<li->qtdd && li->dados[posicao].matricula!=alunoMat)
        posicao++;
    if(posicao==li->qtdd)
        return 0;
    *ponteiro= (li->dados[posicao]);

    return 1;
}

//Realizar Remoção dos elementos
int RemoveInicio(Lista* li){
    if(li==NULL||li->qtdd==0 )
        return 0;
    int i;
    for(i=0; i<li->qtdd-1; i++)
        li->dados[i]= li->dados[i+1];
    li->qtdd--;
    return 1;
}
int RemoveMeio(Lista* li, int alunoMat){
    if(li==NULL||li->qtdd==0 )
        return 0;
    int posicao=0;
    while(posicao<li->qtdd && li->dados[posicao].matricula!=alunoMat)
        posicao++;
    if(posicao==li->qtdd)
        return 0;
    int i;
    for(i=posicao; i<li->qtdd-1; i++)
        li->dados[i]= li->dados[i+1];
    li->qtdd--;
    return 1;
}
int Removefim(Lista* li){
    if(li==NULL||li->qtdd==0 )
        return 0;
    li->qtdd--;
    return 1;
}
