#ifndef BIBLIOPILHA_H_INCLUDED
#define BIBLIOPILHA_H_INCLUDED
#define MAX 100
typedef struct aluno{
    char nome[30];
    int matricula;
}AlunoCad;
struct pilha{
    int qtdd;
    struct aluno dados[MAX];
};
typedef struct pilha Pilha;

//prototipo das funcoes
Pilha* criaPilha();
void liberaPilha(Pilha* pi);
int tamanho(Pilha* pi);
int pilhaCheia(Pilha* pi);
int pilhaVazia(Pilha* pi);
int inserir(Pilha* pi, AlunoCad dadosCad);
int remover(Pilha* pi);
int consulta(Pilha* pi, AlunoCad *dadosCad);

#endif // BIBLIOPILHA_H_INCLUDED
