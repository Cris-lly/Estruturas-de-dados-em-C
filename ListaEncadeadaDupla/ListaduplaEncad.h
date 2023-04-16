#ifndef LISTADUPLAENCAD_H_INCLUDED
#define LISTADUPLAENCAD_H_INCLUDED
typedef struct aluno{
    char nome[30];
    int matricula;
    float nota[4], media;
}DadosAlunos;
typedef struct lista{
    struct lista *ant;
    struct aluno dados;
    struct lista *prox
}lista;
typedef struct lista* Lista;
Lista* criaLista();
void liberaLista(Lista* li);

int tamanho(Lista* li);
int listaCheia(Lista* li);
int listaVazia(Lista* li);

int insereInicio(Lista* li, DadosAlunos dados);
int insereMeio(Lista* li, DadosAlunos dados);
int insereFim(Lista* li, DadosAlunos dados);

int buscaElemento(Lista* li, int mat, DadosAlunos *dados);
int buscaPosicao(Lista* li, int posicao, DadosAlunos *dados);

int removeInicio(Lista* li);
int removeMeio(Lista* li, int conta);
int removeFim(Lista* li);
#endif // LISTADUPLAENCAD_H_INCLUDED
