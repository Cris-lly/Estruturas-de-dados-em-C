#ifndef PILHADINA_H_INCLUDED
#define PILHADINA_H_INCLUDED
typedef struct aluno{
    char nome[30];
    int matricula;
}Aluno;
typedef struct pilha{
    Aluno dados;
    struct pilha *prox;
}Elem;

typedef struct pilha* Pilha;

//prototipo
Pilha* criaPilha();
void liberaPilha(Pilha* pi);
int tamanho (Pilha* pi);
int pilhaCheia(Pilha* pi);
int pilhaVazia(Pilha* pi);
int inserir(Pilha* pi, Aluno dadosCad);
int remover(Pilha* pi);
int consulta(Pilha* pi, Aluno *dadosConsul );

#endif // PILHADINA_H_INCLUDED
