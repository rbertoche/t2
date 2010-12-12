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
#include "conta.h"
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
	CNT_CONTA("GraphNew - Inicializa??o");
	g = (Graph *) malloc(sizeof(Graph));
	if (!g){
	CNT_CONTA("GraphNew - N?o alocou g");
		return NULL;
    }
	g->nodes = LIS_CriarLista((FDelData) LIS_DestruirLista );
	CNT_CONTA("GraphNew - Alocando nodes");
	if (!g->nodes){
        CNT_CONTA("GraphNew - N?o alocou nodes");
		return NULL;
	}
	g->delData = fdd;
	g->currentNode = NULL;
	CNT_CONTA("GraphNew - Atribui??es, finaliza??o");
#ifdef _DEBUG
	g->nOfNodes = 0;
	g->nOfLinks = 0;
	CNT_CONTA("GraphNew - Chamando AssertGraph, finalizando")
	AssertGraph(g);
#endif /* _DEBUG */
	return g;
}

void GraphDel (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
    CNT_CONTA("GraphDel - Inicializa??o");
	IrInicioLista ( g->nodes );
	do {
        CNT_CONTA("GraphDel - Deletando nos");
		g->currentNode = LIS_ObterValor( g->nodes );
		GraphDelNode( g );
	} while ( LIS_AvancarElementoCorrente ( g->nodes , 1)
	== LIS_CondRetOK );
/*		== 0 ); */

    CNT_CONTA("GraphDel - Destruindo, finaliza??o");
	LIS_DestruirLista( g->nodes );

	free(g);
	return;
}

enum graphRet searchData(LIS_tppLista l, void *data)
{
	Node* n;

	CNT_CONTA("searchData - Inicializa??o");
	IrInicioLista(l);
	do{
        CNT_CONTA("searchData - Procurando dado");
		n = LIS_ObterValor(LIS_ObterValor(l));
		if(data == n->data){
            CNT_CONTA("searchData - Achou o dado");
			return graphOk;
		}
	} while(LIS_CondRetOK == LIS_AvancarElementoCorrente (l, 1));
	CNT_CONTA("searchData - Finaliza??o");
	return graphInvalidArgNode;
}
enum graphRet GraphCCurrent (Graph *g, void *newCurrent)
{
    CNT_CONTA("GraphCCurrent - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	if (!g){
        CNT_CONTA("GraphCCurrent - N?o existe g");
		return graphInvalidGraph;
    }
	if (!newCurrent){
        CNT_CONTA("GraphCCurrent - N?o existe novo corrente");
		return graphInvalidArgNode;
    }
	if (graphOk != searchData(g->nodes,newCurrent)){
        CNT_CONTA("GraphCCurrent - N?o encontrou no grafo novo corrente");
		return graphInvalidArgNode;
    }

    CNT_CONTA("GraphCCurrent - Seta novo corrente, finaliza??o");
	g->currentNode = LIS_ObterValor(g->nodes);
	return graphOk;
#ifdef _DEBUG
    CNT_CONTA("GraphCCurrent - Chamando AssertGraph, Fim");
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
    CNT_CONTA("GraphNewNode - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */

       CNT_CONTA("GraphNewMode - Inicializa??o");
/* Inicio do bloco de codigo com tratamento de excecao */
	if (!g){
	    CNT_CONTA("GraphNewMode - N?o existe g");
		return graphInvalidGraph;
    }
	if (!data){
	    CNT_CONTA("GraphNewMode - N?o existe data a ser inserida");
		return graphNullData;
    }
    CNT_CONTA("GraphNewMode - Aloca??o de no");
	n = (Node *) malloc(sizeof(Node));
	if (!n){
        CNT_CONTA("GraphNewMode - N?o alocou no");
		return graphMemoryError;
    }

    CNT_CONTA("GraphNewMode - Criando Lista");
	ln = LIS_CriarLista(NULL);
	/* Para que ln possa se tornar heterogeneo, uso NULL */
	if (!ln){
        CNT_CONTA("GraphNewMode - N?o criou a Lista");
		free (n);
		return graphMemoryError;
	}

    CNT_CONTA("GraphNewMode - Inserindo elemento apos");
	if (LIS_CondRetOK != LIS_InserirElementoApos( ln, n )){
        CNT_CONTA("GraphNewMode - N?o inseriu elemento apos");
		free (n);
		LIS_DestruirLista( ln );
		return graphMemoryError;
	}

    CNT_CONTA("GraphNewMode - Criando lista de Links");
	n->links = LIS_CriarLista((FDelData) delLink );
	if (!n->links){
        CNT_CONTA("GraphNewMode - N?o criou lista de Links");
		free (n);
		LIS_DestruirLista( ln );
		return graphMemoryError;
	}

    CNT_CONTA("GraphNewMode - Inserindo no final da lista");
	IrFinalLista( g->nodes );
	if ( LIS_CondRetOK != LIS_InserirElementoApos( g->nodes , ln) ){
        CNT_CONTA("GraphNewMode - N?o inseriu no final da lista");
		LIS_DestruirLista( n->links );
		free (n);
		LIS_DestruirLista( ln );
		return graphMemoryError;
	}
/* Fim do bloco de codigo com tratamento de excecao */

    CNT_CONTA("GraphNewMode - Atribui??o, finaliza??o");
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
	CNT_CONTA("267 GraphNewNode - N?O SEI O QUE ESCREVER FIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIM");
#endif /* _DEBUG */
	return graphOk;
}


void GraphDelNode (Graph *g)
{
#ifdef _DEBUG
	int nOfNodesAntigo = g->nOfNodes;
	AssertGraph(g);
#endif /* _DEBUG */

    CNT_CONTA("GraphdelNode - Inicializa??o");
	Node *n;
	assert( g!=NULL );
	n = (Node *) LIS_ObterValor(g->currentNode);
	assert( n!=NULL );
#ifdef _DEBUG
	AssertNode(n,g);
#endif /* _DEBUG */

    CNT_CONTA("GraphdelNode - Deletando no");
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

	CNT_CONTA("delNode - Destruindo lista de links");
	LIS_DestruirLista( n->links );
	if ( g->delData ){
         CNT_CONTA("delNode - Existe g->delData");
		( *g->delData )( n->data );
    }
#ifdef _DEBUG
	IrFinalLista( g->currentNode );
	free(LIS_ObterValor( g->currentNode ));
	IrInicioLista( g->currentNode );
#endif /* _DEBUG */
    CNT_CONTA("delNode - Finalizando");
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

	CNT_CONTA("delLink - Inicio");
	if ( RecursionCnt <= 1 &&
			LIS_CondRetOK == LIS_ProcurarValor(l->n2->links,l->brother) ){
			CNT_CONTA("delLink - Achou: Deletando Lista de Links");
		LIS_ExcluirElemento(l->n2->links);
	}
	CNT_CONTA("delLink - Finalizando");
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
	CNT_CONTA("linkTwoNodes - Inicializa??o");
	do{ /* Assertiva: Nao repetir links */
	    CNT_CONTA("linkTwoNodes - Procurando link igual");
		link = LIS_ObterValor(node1->links);
		if( link && link->n2 == node2 ){
            CNT_CONTA("linkTwoNodes - Links iguais");
			return graphInvalidLink;
		}
	}while (LIS_CondRetOK == LIS_AvancarElementoCorrente (node1->links,1));

    CNT_CONTA("linkTwoNodes - Compondo Links");
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

	CNT_CONTA("linkTwoNodes - Inserindo link 1 na lista");
	if( LIS_CondRetOK != LIS_InserirElementoApos(node1->links, link1) ){
        CNT_CONTA("linkTwoNodes - N?o inseriu link 1 na lista");
		return graphMemoryError;
    }

    CNT_CONTA("linkTwoNodes - Inserindo link 2 na lista");
	if( LIS_CondRetOK != LIS_InserirElementoApos(node2->links, link2) ){
        CNT_CONTA("linkTwoNodes - N?o inseriu link 2 na lista");
		LIS_ExcluirElemento(node1->links);
		return graphMemoryError;
	}
#ifdef _DEBUG
	AssertLink(link1);
	AssertLink(link2);
#endif /* _DEBUG */
    CNT_CONTA("linkTwoNodes - Finalizando");
	return graphOk;
}

enum graphRet GraphAddLink (Graph *g, void *n)
{
    CNT_CONTA("GraphAddLink - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	Node *n1, *n2;
	enum graphRet ret;
	if (!g){
	    CNT_CONTA("GraphAddLink - N?o existe g");
		return graphInvalidGraph;
    }
	if (!n){
	    CNT_CONTA("GraphAddLink - N?o existe n");
		return graphNullData;
    }
	if (!g->currentNode){
        CNT_CONTA("GraphAddLink - N?o existe g->currentNode");
		return graphInvalidCurrentNode;
    }
	n1 = LIS_ObterValor(g->currentNode);
	assert(n1);

    CNT_CONTA("GraphAddLink - Procurando no");
	if (searchData (g->nodes, n) != graphOk){
        CNT_CONTA("GraphAddLink - N?o encontrou no");
		return graphInvalidArgNode;
    }
	n2 = LIS_ObterValor(LIS_ObterValor(g->nodes));

#ifdef _DEBUG
	AssertNode(n1,g);
	AssertNode(n2,g);
#endif /* _DEBUG */
    CNT_CONTA("GraphAddLink - Ligando 2 nos");
	ret = linkTwoNodes(n1, n2);
#ifdef _DEBUG
	if (ret == graphOk){
        CNT_CONTA("GraphAddLink - Ligou os nos");
		g->nOfLinks += 2;
    }
		AssertNode(n1,g);
		AssertNode(n2,g);
		AssertGraph(g);
#endif /* _DEBUG */
	return ret;
}

enum graphRet GraphRemLink (Graph *g, void *d)
{
    CNT_CONTA("GraphRemLink - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	Node *curr;
	Link *l;
	if (!g){
        CNT_CONTA("GraphRemLink - N?o existe g");
		return graphInvalidGraph;
    }
	if (!d){
        CNT_CONTA("GraphRemLink - N?o existe d");
		return graphNullData;
    }
	if (!g->currentNode){
        CNT_CONTA("GraphRemLink - N?o existe g->currentNode");
		return graphInvalidCurrentNode;
    }
	curr = LIS_ObterValor (g->currentNode);
#ifdef _DEBUG
	AssertNode(curr,g);
#endif /* _DEBUG */

    CNT_CONTA("GraphRemLink - Procurando elemento");
	IrInicioLista (curr->links);
	do{
        CNT_CONTA("GraphRemLink - Avan?ando na lista");
		l = (Link*)LIS_ObterValor (curr->links);
		#ifdef _DEBUG
		AssertLink(l);
		#endif /* _DEBUG */
		if (l->n2->data == d){
             CNT_CONTA("GraphRemLink - Deletando elemento");
			/* deleta de curr -> n2 */
			LIS_ExcluirElemento(curr->links);
				/* isso deleta link e link->brother */
			#ifdef _DEBUG
			g->nOfLinks -= 2 ;
			AssertGraph(g);
			#endif /* _DEBUG */
			return graphOk;
		}
	}while (LIS_AvancarElementoCorrente(curr->links, 1)
			== LIS_CondRetOK);

    CNT_CONTA("GraphRemLink - Finalizando");
	return graphInvalidArgNode;
}

void *GraphGetData (Graph *g)
{
    CNT_CONTA("GraphGetData - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */

	if (g->currentNode){
        CNT_CONTA("GraphGetData - Obtendo valor");
		return ((Node *)LIS_ObterValor ( g->currentNode ))->data;
    }

    CNT_CONTA("GraphGetData - currentNode nao existe, finalizando");
	return NULL;
}

void GraphNodesStart (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */

    CNT_CONTA("GraphNodesStart - Finalizando");
	g->nodesOld = NULL;
	IrInicioLista ( g->nodes );
}

void GraphLinksStart (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */

    CNT_CONTA("GraphNodesStart - Finalizando");
	g->linksOld = NULL;
	IrInicioLista ( ((Node *)LIS_ObterValor (g->currentNode))->links );
}

void *GraphNodesGetNext (Graph *g)
{
    CNT_CONTA("GraphNodesGetNext - inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	void *ret;
	LIS_tppLista l;
	if (!g || !g->currentNode)
		return NULL;
    }
    CNT_CONTA("GraphNodesGetNext - guardando g->nodes");
	l = g->nodes;
	if (!l){
        CNT_CONTA("GraphNodesGetNext - N?o existe g->nodes");
		return NULL;
    }
    CNT_CONTA("GraphNodesGetNext - Obtendo dado");
	ret = ((Node*)LIS_ObterValor (LIS_ObterValor(l)))->data;
	if (g->nodesOld == ret){ /* Se esse dado ja' repitiu, ja terminou a lista */
	    CNT_CONTA("GraphNodesGetNext - Dado repetido, fim da lista");
		return NULL;
	}
	CNT_CONTA("GraphNodesGetNext - Avan?ando elemento corrente");
	g->nodesOld = ret;
	LIS_AvancarElementoCorrente (l, 1);
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
    CNT_CONTA("GraphNodesGetNext - Finalizando");
	return ret;
}

void *GraphLinksGetNext (Graph *g)
{
    CNT_CONTA("GraphLinksGetNext - inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	void *ret;
	LIS_tppLista l;
	CNT_CONTA("GraphLinksGetNext - Inicializa??o");

	if (!g || !g->currentNode){
	    CNT_CONTA("GraphLinksGetNext - N?o existe g ou currentNode");
		return NULL;
    }
	CNT_CONTA("GraphLinksGetNext - Salvando lista de links");
	l = ((Node*)LIS_ObterValor (g->currentNode))->links;
	if (!LIS_ObterValor(l)){
        CNT_CONTA("GraphLinksGetNext - N?o acessou lista de links");
		return NULL;
    }

    CNT_CONTA("GraphLinksGetNext - Salvando dados");
	ret = ((Link*)LIS_ObterValor(l))->n2->data;
	if (g->linksOld == ret){ /* Se esse dado ja' repitiu, ja terminou a lista */
		CNT_CONTA("GraphLinksGetNext - Dado repetido, fim da lista");
        return NULL;
	}

	CNT_CONTA("GraphLinksGetNext - Avan?ando elemento corrente");
	g->linksOld = ret;
	LIS_AvancarElementoCorrente (l, 1);
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
    CNT_CONTA("GraphNodesGetNext - Finalizando");
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
    CNT_CONTA("AssertLink - Verificando assertivas");
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
    CNT_CONTA("AssertNode - Verificando assertivas");
	IrInicioLista(g->nodes);
	do{
        CNT_CONTA("AssertLink - Procurando valor");
		if (n == LIS_ObterValor(LIS_ObterValor( g->nodes ))){
            CNT_CONTA("AssertLink - Valor encontrado");
			assert( n->delData == g->delData );
			return;
        }
	} while(LIS_CondRetOK == LIS_AvancarElementoCorrente ( g->nodes , 1));
	/* Nao deveria cruzar esse ponto: Significa que nao foi encontrado
	 * n na lista g->nodes
	 */
	CNT_CONTA("AssertLink - Valor n?o encontrado");
	assert( 0 );
}

void AssertGraph(Graph *g)
{
	int i;

	CNT_CONTA("AssertGraph - Verificando assertivas");
	assert( g->nOfNodes == 0 || g->currentNode !=NULL );
	assert( g->nOfLinks % 2 == 0 );

	IrInicioLista(g->nodes);
	for (	i=1;
			LIS_CondRetOK == LIS_AvancarElementoCorrente ( g->nodes , 1);
			i++ ){
            CNT_CONTA("AssertGraph - Avan?ando elemento corrente");
        }

    CNT_CONTA("AssertGraph - Verificando assertivas, finalizando");
	assert( i == g->nOfNodes || g->nOfNodes == 0 );
}
#endif /* _DEBUG */
