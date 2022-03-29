#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioLista.h"
int main(){
    setlocale(LC_ALL,"portuguese");
    //tipo de dado lista e cria��o
    int i,matricula, escolha;
    float count=0.0;
    Lista *li= criaLista();
    DadosAlunos alunoCad, ponteiro;

    //Tela do usu�rio
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
            scanf(" %[^\n]s", alunoCad.nome);
            printf("MATR�CULA:");
            scanf("%d", &alunoCad.matricula);
            for(i=0; i<4;i++){
                printf("DIGITE A %d� NOTA:\n", i+1);
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
                printf("Escolha a opera��o:\n");
                printf("1- Remover no in�cio\n");
                printf("2- Remover no meio\n");
                printf("3- Remover no fim\n");
                scanf("%d", &escolha);
            }while(escolha<1 && escolha>3);
            if(escolha==1)
                    RemoveInicio(li);
            else
                if(escolha==2){
                    printf("Digite o n�mero de matr�cula para fazer a remo��o:");
                    scanf("%d", &matricula);
                    RemoveMeio(li, matricula);
                }
                else
                    Removefim(li);
            printf("Removido com sucesso!\n");
            break;
        case 3:
            do{
                printf("Escolha a opera��o:\n");
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
                        printf("Lista n�o inicializada");
                    else
                        if(listaCheia(li)==1)
                            printf("lista cheia!");
                        else
                            printf("lista vazia ou incompleta\n");
                            do{
                                printf("verificar tamanho?\n");
                                printf("1-SIM\n");
                                printf("2-N�O\n");
                                scanf("%d", &escolha);
                            }while(escolha<1&&escolha>2);
                            if(escolha==1)
                                printf("Tamanho da lista: %d\n",tamanho(li));
                }
                else{
                    printf("Digite o n�mero da matr�cula:");
                    scanf("%d", &matricula);

                    if(BuscaElemAluno(li, matricula, &ponteiro)){
                        printf("NOME= %s\n", ponteiro.nome);
                        printf("MATR�CULA= %d\n", ponteiro.matricula);
                        printf("M�DIA= %.2f\n", ponteiro.media);
                    }
                    else
                        printf("Aluno n�o encontrado!\n");
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
    free(li);
    return 0;
}
//criei o espa�o para come�ar a inserir algo
Lista* criaLista(){
    Lista* li=(Lista*) malloc(sizeof(Lista));
    if(li!=NULL)
        li->qtdd=0;
    return li;
}
//liberar a aloca��o feita ao decorrer da execu��o do programa
void libera(Lista* li){
    free(li);
}
//----inser��o de dados na lista----
int inserirDadosInicio(Lista* li, DadosAlunos Alunos){
    /*verifica��o se a lista j� foi inicializada, ou se est� cheia*/
    if(li==NULL||li->qtdd==MAX )
        return 0;
    int i;
    //quando for o melhor caso(qtdd=0) ele n�o entra no for
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
    //percorrendo o array e comparando se � menor ou maior
    while(posicao<li->qtdd && li->dados[posicao].matricula<Alunos.matricula)
        //Ele serve como contador para saber a posi��o que o n�mero ir� ficar
        posicao++;
    for(i= li->qtdd-1; i>=posicao; i--)
        li->dados[i+1]= li->dados[i];
    li->dados[posicao]= Alunos;
    li->qtdd++;
    return 1;
}
int inserirDadosFim(Lista* li, DadosAlunos Alunos){
    /*verifica��o se a lista j� foi inicializada, ou se est� cheia*/
    if(li==NULL||li->qtdd==MAX )
        return 0;
    li->dados[li->qtdd]= Alunos;
    li->qtdd++;
    return 1;
}

//----Realizar consultas sobre a lista-----
int tamanho(Lista* li){
    if(li==NULL)
        // o -1 ser� retornado quando n tiver nenhuma lista inicializada
        return -1;
    return li->qtdd;
}
int listaCheia(Lista* li){
    if(li==NULL)
        return -1;
    //se a express�o dentro do par�ntese satisfazer a igualdade retorna 1, sen�o retorna 0;
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

//Realizar Remo��o dos elementos
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
