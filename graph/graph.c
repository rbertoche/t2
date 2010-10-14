#include <stdlib.h>
/*

Diagrama UML do modelo fisico da implementacao de grafo
'owns' significa atrelamento de tempo de vida,
responsabilidade pelo desalocamento

================  1 owns 1  ======================     |
| struct Graph |  ------->  | list of list Nodes |     |
================            ======================     |
                                   | 1                 |
                                   | owns              |
                                   \/ 0..*             |
                            =================          |
                            |  list Node    |          |
                            =================          |
                                   |  1                |
                                   |  owns             |
                                   \/ 1                |
        ========            =================          |
        | Data |  1 owns 1  |  struct Node  |          |
        | -??? |  <-------  =================          |
        ========             | 1          /\           |
                             | owns        | 0..*      |
                             | 1           | links to  |
                            \/             | 0..*      |
                            =================          |
                            | list of Links |          |
                            =================          |
                                                       |
*/

#include "graph.h"
#include "../lista/lista.h"


typedef struct graph Graph;
typedef struct node Node;
/* Graph definition */
struct graph {
	LIS_tppLista nodes;
	LIS_tppLista currentNode;
	FDelData delData;
	int nOfNodes;
	int nOfLinks;
};

/* Node definition */
struct node {
	void * data;
	LIS_tppLista links;
	FDelData delData;
};

void delNode (Graph *g, void *n);

Graph *GraphNew (FDelData fdd)
{
	Graph *g;
	g = (Graph *) malloc(sizeof(Graph));
	if (!g)
		return NULL;
	/* Atencao, NULL abaixo esta correto. O Dono dos nodes e' o graph */
	g->nodes = LIS_CriarLista(NULL);
	if (!g->nodes){
		return NULL;
	}
	g->delData = fdd;
	g->currentNode = NULL;
	g->nOfNodes = 0;
	g->nOfLinks = 0;
	return g;
}

void GraphDel (Graph *g)
{
	/* Esse codigo tende a ser replicado:
         * Varre toda uma lista aplicando uma funcao */
	IrInicioLista ( g->nodes );
	do {
		delNode( g, (Node*) LIS_ObterValor ( g->nodes ) );
	} while ( LIS_AvancarElementoCorrente ( g->nodes , 1)
		== 0 );
/*	== LIS_CondRetOk ) FIXME: isso nao tava compilando, nao entendi.*/

	LIS_DestruirLista( g->nodes );

	free(g);
	return;
}

enum graphRet GraphCCurrent (Graph *g, void *newCurrent)
{
	if (!g)
		return graphInvalidGraph;
	if (!newCurrent)
		return graphInvalidArgNode;
	g->currentNode = newCurrent;
	return graphOk;
}
enum graphRet GraphNewNode (Graph *g, void *data)
{
	Node *n;
	if (!g)
		return graphInvalidGraph;
	if (!data)
		return graphNullData;
	n = (Node *) malloc(sizeof(Node));
	if (!n)
		return graphMemoryError;
	n->links = LIS_CriarLista(NULL);
	n->data = data;
	IrFinalLista( g->nodes );
	if ( LIS_CondRetOK != LIS_InserirElementoApos( g->nodes , n) ){
		free( n );
		return graphMemoryError;
	}
	g->nOfNodes++;
	g->currentNode = n;
	return graphOk;
}
enum graphRet GraphDelNode (Graph *g)
{
	if (!g)
		return graphInvalidGraph;
	if (!g->currentNode)
		return graphInvalidCurrentNode;
	delNode(g,g->currentNode);
	g->currentNode = NULL;
	return graphOk;
}

void delNode (Graph *g, void *n_)
{
	Node * n=n_;
	LIS_DestruirLista( n->links );
	( *g->delData )( n->data );
}	
	
enum graphRet GraphAddLink (Graph *g, void *n)
{
	if (!g)
		return graphInvalidGraph;
	if (!n)
		return graphNullData;
	if (LIS_ProcurarValor (g->nodes, n) == LIS_CondRetOK)
		return graphInvalidLink;

	LIS_InserirElementoApos (g->nodes);
	return graphOk;
}

enum graphRet GraphRemLink (Graph *g, void *n)
{
	if (!g)
		return graphInvalidGraph;
	if (!n)
		return graphNullData;
	if (LIS_ProcurarValor (g->currentNode->links, n)
			== LIS_CondRetNaoAchou)
		return graphInvalidLink;

	if (LIS_ProcurarValor (g->nodes, g->currentNode))
	LIS_ObterValor (g->nodes, g->currentNode);

	LIS_ExcluirElemento (g->currentNode->links);
	return graphOk;
}

void *GraphGetData (Graph *g)
{
	return NULL;
}
void GraphListStart(pGraphList l)
{
}
void *GraphListGetNext(pGraphList l)
{
	return NULL;
}
pGraphList GraphGetLinks(pGraph g)
{
}
pGraphList GraphGetNodes(pGraph g)
{
	if (!g || !g->currentNode)
		return NULL;
	return g->currentNode->data;
}

<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
