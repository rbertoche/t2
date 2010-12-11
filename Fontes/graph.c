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
                    \              v  0..*             |
                     \      =================          |
                 owns \     |  list Node    |          |
                       \    =================          |
                        \          |  1                |
                    0..* \         |  lists            |
                          \|       v  1                |
        ========            =================          |
        | Data |  1 owns 1  |  struct Node  |          |
        | -??? |  <-------  =================          |
        ========             | 1         ^ ^           |
                             | owns    1 | | 1         |
                             | 1    links| | links to  |
                             |       from| |           |
                             v         1 | | 1         |
              =================  owns   ========       |
              | list of Links |-------->| Link |       |
              =================  1   1  ========       |
                                         |    ^        |
                                       1 |    | 1      |
                                         \----/        |
                                       is brother      |
                                                       |
*/

#include "graph.h"
#include "lista.h"

#ifdef _DEBUG
#include "cespdin.h"
#include <string.h>
#undef NDEBUG /* Habilita assert */
#endif /* _DEBUG */
#include <assert.h>

typedef struct graph Graph;
typedef struct node Node;
typedef struct link Link;

#ifdef _DEBUG
/* Declara funcoes de assertivas estruturais*/
void AssertLink(Link *l);
void AssertGraph(Graph *g);
void AssertNode(Node *n, Graph *g);
#endif /* _DEBUG */


/* Graph definition */
struct graph {
	LIS_tppLista nodes;
	LIS_tppLista currentNode;
	FDelData delData;
	void *nodesOld;
	void *linksOld;
#ifdef _DEBUG
	int nOfNodes;
	int nOfLinks;
#endif /* _DEBUG */
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
#ifdef _DEBUG
	g->nOfNodes = 0;
	g->nOfLinks = 0;
	AssertGraph(g);
#endif /* _DEBUG */
	return g;
}

void GraphDel (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
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
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	if (!g)
		return graphInvalidGraph;
	if (!newCurrent)
		return graphInvalidArgNode;
	if (graphOk != searchData(g->nodes,newCurrent))
		return graphInvalidArgNode;
	g->currentNode = LIS_ObterValor(g->nodes);
	return graphOk;
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
} 

enum graphRet GraphNewNode (Graph *g, void *data)
{
	Node *n;
#ifdef _DEBUG
	Node *mirror;
	void *offset;
#endif /* _DEBUG */
	LIS_tppLista ln;
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
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

	n->links = LIS_CriarLista((FDelData) delLink );
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
	g->currentNode = ln;
#ifdef _DEBUG
	offset = malloc( 0x200 );
		/* Apenas para que o proximo malloc esteja longe do dado replicado*/
	mirror = (Node *) malloc(sizeof(Node));
	free(offset);
	memcpy(mirror,n, sizeof(Node));
	LIS_InserirElementoApos( ln, mirror );
	IrInicioLista( ln );
	g->nOfNodes++;
	AssertGraph(g);
	AssertNode(n,g);
#endif /* _DEBUG */
	return graphOk;
}


void GraphDelNode (Graph *g)
{
#ifdef _DEBUG
	int nOfNodesAntigo = g->nOfNodes;
	AssertGraph(g);
#endif /* _DEBUG */
	Node *n;
	assert( g!=NULL );
	n = (Node *) LIS_ObterValor(g->currentNode);
	assert( n!=NULL );
#ifdef _DEBUG
	AssertNode(n,g);
#endif /* _DEBUG */
	delNode(g,n);
	LIS_ExcluirElemento(g->nodes);
	g->currentNode = LIS_ObterValor(g->nodes);
#ifdef _DEBUG
	g->nOfNodes--;
	assert ( g->nOfNodes == (nOfNodesAntigo - 1) );
	AssertGraph(g);
#endif /* _DEBUG */
}

void delNode (Graph *g, void *n_)
{
	Node * n=n_;
	LIS_DestruirLista( n->links );
	if ( g->delData )
		( *g->delData )( n->data );
#ifdef _DEBUG
	IrFinalLista( g->currentNode );
	free(LIS_ObterValor( g->currentNode ));
	IrInicioLista( g->currentNode );
#endif /* _DEBUG */
	free (n);
}


/* Deleta automagicamente um link e seu link-complemento/brother, removendo
 * ambos das listas.
 * !! Essa funcao NUNCA deve ser chamada diretamente. Apenas a lista link
 * a deve chamar, do contrario essa lista tera um elemento com um ponteiro
 * invalido. !!
 * delLink(link) e' chamada durante a execucao de algum LIS_ExcluirElemento.
 * quando isso acontece, link ja nao pertence a essa lista. delLink
 * invoca um outro LIS_ExcluirElemento para remover o link irmao.
 * Achei bom incluir um certo chines:
 *  - sendo LIS1 a lista a que link pertence,
 *  - LIS2 a lista a que link->brother pertence:
 *
 *  LIS_ExcluirElemento ( LIS1 ) e' chamada{
 *  	link e' removido da lista LIS1;
 *  	delLink (link) e' chamada{
 * 			LIS_ProcurarValor ( LIS2, link->brother ) {} retorna OK;
 *  		LIS_ExcluirElemento ( LIS2 ) e' chamada{
 *  			link->brother e' removido da lista LIS2;
 *    			delLink (link->brother) e' chamada{
 *		 			LIS_ProcurarValor ( LIS1, link->brother->brother ){
 * 						} retorna nao OK;
 *				link->brother e' liberado
 *    			}
 *   		}
 *   		link e' liberado
 *  	}
 *  }
 */

void delLink (Link *l)
{
	static int RecursionCnt = 0;
	RecursionCnt++;
	IrInicioLista( l->n2->links );
	if ( RecursionCnt <= 1 &&
			LIS_CondRetOK == LIS_ProcurarValor(l->n2->links,l->brother) )
		LIS_ExcluirElemento(l->n2->links);
	free (l);
	RecursionCnt--;
}


/* Essa funcao e' responsavel por criar e compor 2 links ligando
 * 2 nos.
 */
enum graphRet linkTwoNodes(Node *node1, Node *node2)
{
	Link *link1, *link2, *link;
	IrInicioLista(node1->links);
	do{ /* Assertiva: Nao repetir links */
		link = LIS_ObterValor(node1->links);
		if( link && link->n2 == node2 ){
			return graphInvalidLink;
		}
	}while (LIS_CondRetOK == LIS_AvancarElementoCorrente (node1->links,1));

	link1 = (Link*) malloc (sizeof(Link));
	link2 = (Link*) malloc (sizeof(Link));

	/* Compoe os dois links */
	link1->n1 = node1;
	link1->n2 = node2;
	link1->brother = link2;
	link2->n1 = node2;
	link2->n2 = node1;
	link2->brother = link1;

	IrFinalLista(node1->links);
	IrFinalLista(node2->links);

	/* Tenta inserir cada link em uma lista, limpa se nao der certo */
	if( LIS_CondRetOK != LIS_InserirElementoApos(node1->links, link1) )
		return graphMemoryError;
	if( LIS_CondRetOK != LIS_InserirElementoApos(node2->links, link2) ){
		LIS_ExcluirElemento(node1->links);
		return graphMemoryError;
	}
#ifdef _DEBUG
	AssertLink(link1);
	AssertLink(link2);
#endif /* _DEBUG */
	return graphOk;
}

enum graphRet GraphAddLink (Graph *g, void *n)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	Node *n1, *n2;
	enum graphRet ret;
	if (!g)
		return graphInvalidGraph;
	if (!n)
		return graphNullData;
	if (!g->currentNode)
		return graphInvalidCurrentNode;
	n1 = LIS_ObterValor(g->currentNode);
	assert(n1);

	if (searchData (g->nodes, n) != graphOk)
		return graphInvalidArgNode;
	n2 = LIS_ObterValor(LIS_ObterValor(g->nodes));

#ifdef _DEBUG
	AssertNode(n1,g);
	AssertNode(n2,g);
#endif /* _DEBUG */
	ret = linkTwoNodes(n1, n2);
#ifdef _DEBUG
	if (ret == graphOk)
		g->nOfLinks += 2;
		AssertNode(n1,g);
		AssertNode(n2,g);
		AssertGraph(g);
#endif /* _DEBUG */
	return ret;
}

enum graphRet GraphRemLink (Graph *g, void *d)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	Node *curr;
	Link *l;
	if (!g)
		return graphInvalidGraph;
	if (!d)
		return graphNullData;
	if (!g->currentNode)
		return graphInvalidCurrentNode;
	curr = LIS_ObterValor (g->currentNode);
#ifdef _DEBUG
	AssertNode(curr,g);
#endif /* _DEBUG */


	IrInicioLista (curr->links);
	do{
		l = (Link*)LIS_ObterValor (curr->links);
		#ifdef _DEBUG
		AssertLink(l);
		#endif /* _DEBUG */
		if (l->n2->data == d){
			/* deleta de curr -> n2 */
			LIS_ExcluirElemento(curr->links);
				/* isso deleta deleta link e link->brother */
			#ifdef _DEBUG
			g->nOfLinks -= 2 ;
			AssertGraph(g);
			#endif /* _DEBUG */
			return graphOk;
		}
	}while (LIS_AvancarElementoCorrente(curr->links, 1)
			== LIS_CondRetOK);

	return graphInvalidArgNode;
}

void *GraphGetData (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	if (g->currentNode)
		return ((Node *)LIS_ObterValor ( g->currentNode ))->data;
	return NULL;
}

void GraphNodesStart (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	g->nodesOld = NULL;
	IrInicioLista ( g->nodes );
}

void GraphLinksStart (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	g->linksOld = NULL;
	IrInicioLista ( ((Node *)LIS_ObterValor (g->currentNode))->links );
}

void *GraphNodesGetNext (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
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
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	return ret;
}

void *GraphLinksGetNext (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
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
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	return ret;
}

#ifdef _DEBUG
/* Assertivas estruturais de cara uma das structs
 * Para descobrir em que funcao uma assertiva dessas foi quebrada, rode o
 * programa com algum debugger e veja as pilha de chamadas (stacktrace)
 */

void AssertLink(Link *l)
{
	Link *b = l->brother;
	assert(	b->brother == l );
	assert( l != b );
	assert( l->n1 == b->n2 );
	assert( l->n2 == b->n1 );
	assert( l->n1->links == b->n2->links );
	assert( l->n2->links == b->n1->links );

	IrInicioLista( l->n1->links );
	IrInicioLista( b->n1->links );
	assert( LIS_CondRetOK == LIS_ProcurarValor( l->n1->links , l) );
	assert( LIS_CondRetOK == LIS_ProcurarValor( b->n1->links , b) );
}

void AssertNode(Node *n, Graph *g)
{
	IrInicioLista(g->nodes);
	do{
		if (n == LIS_ObterValor(LIS_ObterValor( g->nodes )))
			assert( n->delData == g->delData );
			return;
	} while(LIS_CondRetOK == LIS_AvancarElementoCorrente ( g->nodes , 1));
	/* Nao deveria cruzar esse ponto: Significa que nao foi encontrado
	 * n na lista g->nodes
	 */
	assert( 0 );
}

void AssertGraph(Graph *g)
{
	int i;
	assert( g->nOfNodes == 0 || g->currentNode !=NULL );
	assert( g->nOfLinks % 2 == 0 );

	IrInicioLista(g->nodes);
	for (	i=1;
			LIS_CondRetOK == LIS_AvancarElementoCorrente ( g->nodes , 1);
			i++ ){}

	assert( i == g->nOfNodes || g->nOfNodes == 0 );
}
#endif /* _DEBUG */
