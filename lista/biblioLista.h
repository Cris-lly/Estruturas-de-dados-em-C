#ifndef BIBLIOLISTA_H_INCLUDED
#define BIBLIOLISTA_H_INCLUDED
#define MAX 100

//----programa de cadastro de alunos-----
//TIPO DE DADO ARMAZENADO NA LISTA
/*esse é aquele dado que é utilizado
na lista encadeada, no qual armazena duas coisas,
o dado e o ponteiro para o próximo elemento da lista.
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

//protótipo das funções:
Lista* criaLista();
//inserção
int inserirDadosInicio(Lista* li, DadosAlunos Alunos);
int inserirDadosMeio(Lista* li, DadosAlunos Alunos);
int inserirDadosFim(Lista* li, DadosAlunos Alunos);
//consultas
int tamanho(Lista* li);
int listaCheia(Lista* li);
int listaVazia(Lista* li);
int BuscaElemAluno(Lista* li, int alunoMat, DadosAlunos *ponteiro);
//remoção
int RemoveInicio(Lista* li);
int RemoveMeio(Lista* li, int alunoMat);
int Removefim(Lista* li);
#endif // BIBLIOLISTA_H_INCLUDED
