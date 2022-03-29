#ifndef BIBLIOLISTAENCAD_H_INCLUDED
#define BIBLIOLISTAENCAD_H_INCLUDED
typedef struct aluno{
    char nome[30];
    int matricula;
    float nota[4];
    float media;
}DadosAlunos;
//essa é a primeira diferença, agora lista é um ponteiro para ponteiro
typedef struct lista* Lista;

//protótipo de funções:
Lista* criaLista();
void liberaLista(Lista* li);
//inserção
int inserirDadosInicio(Lista* li, DadosAlunos Dados);
int inserirDadosMeio(Lista* li, DadosAlunos Dados);
int inserirDadosFim(Lista* li, DadosAlunos Dados);
//consultas
int tamanho(Lista* li);
int listaCheia(Lista* li);
int listaVazia(Lista* li);
int BuscaElemAluno(Lista* li, DadosAlunos *Dados, int matricula);
int consultaPosicao(int posicao, Lista* li, DadosAlunos *Dados);
int consultaPosicaoElemento(int posicao, Lista* li, DadosAlunos Dados);
//remoção
int removerInicio(Lista* li);
int removerMeio(Lista* li, DadosAlunos Dados);
int removerFim(Lista* li);

#endif // BIBLIOLISTAENCAD_H_INCLUDED
