#ifndef BIBLIOLISTA_H_INCLUDED
#define BIBLIOLISTA_H_INCLUDED
#define MAX 100

//----programa de cadastro de alunos-----
//TIPO DE DADO ARMAZENADO NA LISTA
/*esse � aquele dado que � utilizado
na lista encadeada, no qual armazena duas coisas,
o dado e o ponteiro para o pr�ximo elemento da lista.
*/
typedef struct aluno{
    char nome[30];
    int matricula;
    float nota[4], media;
}DadosAlunos;
typedef struct lista{
    int qtdd;
    struct aluno dados[MAX];
}Lista;

//prot�tipo das fun��es:
Lista* criaLista();
//inser��o
int inserirDadosInicio(Lista* li, DadosAlunos Alunos);
int inserirDadosMeio(Lista* li, DadosAlunos Alunos);
int inserirDadosFim(Lista* li, DadosAlunos Alunos);
//consultas
int tamanho(Lista* li);
int listaCheia(Lista* li);
int listaVazia(Lista* li);
int BuscaElemAluno(Lista* li, int alunoMat, DadosAlunos *ponteiro);
//remo��o
int RemoveInicio(Lista* li);
int RemoveMeio(Lista* li, int alunoMat);
int Removefim(Lista* li);
#endif // BIBLIOLISTA_H_INCLUDED
