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
#include "lista.h"


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
	void *nodesOld;
	void *linksOld;
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
	Link * brother;
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

enum graphRet searchData(LIS_tppLista l, void *data)
{
	Node* n;
	IrInicioLista(l);
	do{	
		n = LIS_ObterValor(LIS_ObterValor(l));
		if(data == n->data){
			return graphOk;
		}
	} while(LIS_CondRetOK == LIS_AvancarElementoCorrente (l, 1));
	return graphInvalidArgNode;
}
enum graphRet GraphCCurrent (Graph *g, void *newCurrent)
{
	if (!g)
		return graphInvalidGraph;
	if (!newCurrent)
		return graphInvalidArgNode;
	if (graphOk != searchData(g->nodes,newCurrent))
		return graphInvalidArgNode;
	g->currentNode = LIS_ObterValor(g->nodes);
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

	if (LIS_CondRetOK != LIS_InserirElementoApos( ln, n )){
		free (n);
		LIS_DestruirLista( ln );
		return graphMemoryError;
	}

	n->links = LIS_CriarLista( NULL );
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
	n->delData = g->delData;
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
	g->currentNode = LIS_ObterValor(g->nodes);
}

void delNode (Graph *g, void *n_)
{
	Node * n=n_;
	LIS_DestruirLista( n->links );
	( *g->delData )( n->data );
	free (n);
}

void delLink (Link *l)
{
	LIS_ProcurarValor(l->n2->links,l->brother);
	LIS_ExcluirElemento(l->n2->links);
	LIS_ProcurarValor(l->n1->links,l);
	LIS_ExcluirElemento(l->n1->links);
}

enum graphRet linkTwoNodes(Node *n1, Node *n2)
{
	Link *l1,*l2,*l;
	IrInicioLista(n1->links);
	do{ /* Assertiva: Nao repetir links */
		l = LIS_ObterValor(n1->links);
		if( l && l->n2 == n2 ){
			return graphInvalidLink;
		}
	}while (LIS_CondRetOK == LIS_AvancarElementoCorrente (n1->links,1));

	l1 = (Link*) malloc (sizeof(Link));
	l2 = (Link*) malloc (sizeof(Link));
	l1->n1=n1;
	l1->n2=n2;
	l1->brother=l2;
	l2->n1=n2;
	l2->n2=n1;
	l2->brother=l1;

	IrFinalLista(n1->links);
	IrFinalLista(n2->links);
	if( LIS_CondRetOK != LIS_InserirElementoApos( n1->links,l1 ) )
		return graphMemoryError;
	if( LIS_CondRetOK != LIS_InserirElementoApos( n2->links,l2 ) ){
		LIS_ExcluirElemento(n1->links);
		return graphMemoryError;
	}
	return graphOk;
}

enum graphRet GraphAddLink (Graph *g, void *n)
{
	Node *n1, *n2;
	if (!g)
		return graphInvalidGraph;
	if (!n)
		return graphNullData;
	if (!g->currentNode)
		return graphInvalidCurrentNode;
	n1 = LIS_ObterValor(g->currentNode);
	if (!n1)
		return graphInvalidCurrentNode;

	if (searchData (g->nodes, n) != graphOk)
		return graphInvalidArgNode;
	n2 = LIS_ObterValor(LIS_ObterValor(g->nodes));

	return linkTwoNodes(n1,n2);
}

enum graphRet GraphRemLink (Graph *g, void *d)
{
	Node *curr;
	Link *l;
	if (!g)
		return graphInvalidGraph;
	if (!d)
		return graphNullData;
	if (!g->currentNode)
		return graphInvalidCurrentNode;
	curr = LIS_ObterValor (g->currentNode);


	IrInicioLista (curr->links);
	do{
		l = (Link*)LIS_ObterValor (curr->links);
		if (l->n2->data == d){
			/* deleta de curr -> n2 */
			delLink(l);
			return graphOk;
		}
	}while (LIS_AvancarElementoCorrente(curr->links, 1)
			== LIS_CondRetOK);

	return graphInvalidArgNode;
}

void *GraphGetData (Graph *g)
{
	if (g->currentNode)
		return ((Node *)LIS_ObterValor ( g->currentNode ))->data;
	return NULL;
}

void GraphNodesStart (Graph *g)
{
	g->nodesOld = NULL;
	IrInicioLista ( g->nodes );
}

void GraphLinksStart (Graph *g)
{
	g->linksOld = NULL;
	IrInicioLista ( ((Node *)LIS_ObterValor (g->currentNode))->links );
}

void *GraphNodesGetNext (Graph *g)
{
	void *ret;
	LIS_tppLista l;
	if (!g || !g->currentNode)
		return NULL;
	l = g->nodes;
	if (!l)
		return NULL;
	ret = ((Node*)LIS_ObterValor (LIS_ObterValor(l)))->data;
	if (g->nodesOld == ret){ /* Se esse dado ja' repitiu, ja terminou a lista */
		return NULL;
	}
	g->nodesOld = ret;
	LIS_AvancarElementoCorrente (l, 1);
	return ret;
}

void *GraphLinksGetNext (Graph *g)
{
	void *ret;
	LIS_tppLista l;
	if (!g || !g->currentNode)
		return NULL;
	l = ((Node*)LIS_ObterValor (g->currentNode))->links;
	if (!LIS_ObterValor(l))
		return NULL;
	ret = ((Link*)LIS_ObterValor(l))->n2->data;
	if (g->linksOld == ret){ /* Se esse dado ja' repitiu, ja terminou a lista */
		return NULL;
	}
	g->linksOld = ret;
	LIS_AvancarElementoCorrente (l, 1);
	return ret;
}

