#ifndef FILABIBLIO_H_INCLUDED
#define FILABIBLIO_H_INCLUDED
#define MAX 100
typedef struct agenda{
    char evento[30];
    int dia;
} Agenda;

//prototipo de funcoes
typedef struct fila Fila;
Fila* criaFila();
void liberaFila(Fila* li);
int tamanho(li);
int FilaCheia(Fila* li);
int FilaVazia(Fila* li);
int inserir(Fila* fi, Agenda dadosCad);
int remover(Fila* fi);
int consulta(Fila* fi, Agenda *dadosCons);
#endif // FILABIBLIO_H_INCLUDED
