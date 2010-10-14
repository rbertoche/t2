#include <stdlib.h>
/*

Diagrama UML do modelo fisico da implementacao de grafo
'owns' significa atrelamento de tempo de vida,
responsabilidade pelo desalocamento

================  1 owns 1  ======================     |
| struct Graph |  ------->  | list of list Nodes |     |
================            ======================     |
                1 \                | 1                 |
                   \               | owns              |
                    \              \/ 0..*             |
                     \      =================          |
                 owns \     |  list Node    |          |
                       \    =================          |
                        \          |  1                |
                    0..* \         |  lists            |
                          \|       \/ 1                |
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
typedef struct link Link;
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

/* Link definition */
struct link {
	Node * n1;
	Node * n2;
};

void delNode (Graph *g, void *n);
void delLink (Link *n);

Graph *GraphNew (FDelData fdd)
{
	Graph *g;
	g = (Graph *) malloc(sizeof(Graph));
	if (!g)
		return NULL;
	g->nodes = LIS_CriarLista((FDelData) LIS_DestruirLista );
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
		g->currentNode = LIS_ObterValor( g->nodes );
		GraphDelNode( g );
	} while ( LIS_AvancarElementoCorrente ( g->nodes , 1)
	== LIS_CondRetOK );
/*		== 0 ); */

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
	LIS_tppLista ln;
/* Inicio do bloco de codigo com tratamento de excecao */
	if (!g)
		return graphInvalidGraph;
	if (!data)
		return graphNullData;

	n = (Node *) malloc(sizeof(Node));
	if (!n)
		return graphMemoryError;

	ln = LIS_CriarLista(NULL);
	/* Para que ln possa se tornar heterogeneo, uso NULL */
	if (!ln){
		free (n);
		return graphMemoryError;
	}

	if (!LIS_InserirElementoApos( ln, n )){
		free (n);
		LIS_DestruirLista( ln );
		return graphMemoryError;
	}

	n->links = LIS_CriarLista( (FDelData) delLink );
	if (!n->links){
		free (n);
		LIS_DestruirLista( ln );
		return graphMemoryError;
	}

	IrFinalLista( g->nodes );
	if ( LIS_CondRetOK != LIS_InserirElementoApos( g->nodes , ln) ){
		LIS_DestruirLista( n->links );
		free (n);
		LIS_DestruirLista( ln );
		return graphMemoryError;
	}
/* Fim do bloco de codigo com tratamento de excecao */

	n->data = data;
	g->nOfNodes++;
	g->currentNode = ln;
	return graphOk;
}
void GraphDelNode (Graph *g)
{
	Node *n;
/* assertiva caso nao retornasse void (Change Current ja' testou isso):
	if (!g)
		return graphInvalidGraph;
*/
	n = (Node *) LIS_ObterValor(g->currentNode);
/* assertiva caso nao retornasse void (Change Current ja' testou isso):
	if (!n)
		return graphInvalidCurrentNode;
*/
	delNode(g,n);
	LIS_DestruirLista(g->currentNode);
	g->currentNode = NULL;
}

void delNode (Graph *g, void *n_)
{
	Node * n=n_;
	LIS_DestruirLista( n->links );
	( *g->delData )( n->data );
	free (n);
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

void GraphListStart (pGraphList l)
{
	LIS_IrInicioLista (l);
}

void *GraphListGetNext (pGraphList l)
{
	if (LIS_AvancarElementoCorrente (l) != LIS_CondRetOK)
		return NULL;
	return LIS_ObterValor (l);
}

pGraphList GraphGetLinks (pGraph g)
{
	return ((Node *)LIS_ObterValor (g->currentNode))->links;
}

pGraphList GraphGetNodes (pGraph g)
{
	if (!g || !g->currentNode)
		return NULL;
	return g->currentNode->data;
}

