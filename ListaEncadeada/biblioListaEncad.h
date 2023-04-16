#ifndef BIBLIOLISTAENCAD_H_INCLUDED
#define BIBLIOLISTAENCAD_H_INCLUDED
typedef struct Dados{
    char nome_vertice;
    int qtdd_vizinhos;
}Dados_vertice;
//essa � a primeira diferen�a, agora lista � um ponteiro para ponteiro
typedef struct lista_principal* ListaVertice;
typedef struct listaSecundaria* ListaVizinho;

//prot�tipo de fun��es da lista principal:
ListaVertice* criaListaVertice();
void liberaListaVertice(ListaVertice* li);
//inser��o
int inserirDadosFimVertice(ListaVertice* li, ListaVizinho* li_vizinho, Dados_vertice dados );
//consultas
int tamanhoVertice(ListaVertice* li);
int listaVaziaVertice(ListaVertice* li);
int BuscaElemVertice(ListaVertice* li, char *nomeRetorno, char nome);
//remo��o
int removerMeioVertice(ListaVertice* li, char nome);

//prot�tipo de fun��es da lista vizinho:
ListaVizinho* criaListaVizinho();
void liberaListaVizinho(ListaVizinho* li);
//inser��o
int inserirDadosFimVizinho(ListaVizinho* li, char Dados);
//consultas
int tamanhoVizinho(ListaVizinho* li);
int listaVaziaVizinho(ListaVizinho* li);
int BuscaElemVizinho(ListaVizinho* li, char *nomeRetorno, char nome);
//remo��o
int removerMeioVizinho(ListaVizinho* li, char nome);
#endif // BIBLIOLISTAENCAD_H_INCLUDED
