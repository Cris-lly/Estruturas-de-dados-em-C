#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED
typedef struct agenda{
    char evento[30];
    int dia;
}Agenda;
typedef struct lista* Lista;

Lista* criaLista();
void liberaLista(Lista* li);
int tamanho(Lista* li);
int listaCheia(Lista* li);
int listaVazia(Lista* li);
int insereInicio(Lista* li, Agenda dados);
int insereMeio(Lista* li, Agenda dados);
int insereFim(Lista* li, Agenda dados);
int removeInicio(Lista* li);
int removeMeio(Lista* li, int day);
int removeFim(Lista* li);
int buscaPosicao(Lista* li, int posicao, Agenda *dados);
int buscaElem(Lista* li, int day, Agenda *dados);

#endif // LISTACIRCULAR_H_INCLUDED
