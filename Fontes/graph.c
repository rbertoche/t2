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
#include "conta.h"
#include <string.h>
#include "cespdin.h"
#include    "../Tabelas/idtiposespaco.def"
#undef NDEBUG /* Habilita assert */
#endif /* _DEBUG */

#ifndef _DEBUG
#define CNT_CONTAR( a ) /* Desativa contadores */
#endif /* !_DEBUG */

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

Graph *GRA_New (FDelData fdd)
{
	Graph *g;
	CNT_CONTAR("GRA_New - Inicializao");
	g = (Graph *) malloc(sizeof(Graph));
	if (!g){
		CNT_CONTAR("GRA_New - Nao alocou g");
		return NULL;
	}
	g->nodes = LIS_CriarLista((FDelData) LIS_DestruirLista );
	CNT_CONTAR("GRA_New - Alocando nodes");
	if (!g->nodes){
		CNT_CONTAR("GRA_New - Nao alocou nodes");
		free (g);
		return NULL;
	}
	g->delData = fdd;
	g->currentNode = NULL;
	CNT_CONTAR("GRA_New - Atribuies, finalizao");
#ifdef _DEBUG
	g->nOfNodes = 0;
	g->nOfLinks = 0;
	CNT_CONTAR("GRA_New - Chamando AssertGraph, finalizando");
	AssertGraph(g);
#endif /* _DEBUG */
	return g;
}

void GRA_Del (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
    CNT_CONTAR("GRA_Del - Inicializao");
	IrInicioLista ( g->nodes );
	if ( !g->currentNode || !LIS_AvancarElementoCorrente ( g->nodes , 1)){
	CNT_CONTAR("GRA_Del - Grafo vazio");
		return;
	}
	IrInicioLista ( g->nodes );
	do {
        CNT_CONTAR("GRA_Del - Deletando nos");
		g->currentNode = LIS_ObterValor( g->nodes );
		GRA_DelNode( g );
	} while ( LIS_AvancarElementoCorrente ( g->nodes , 1)
	== LIS_CondRetOK );
/*		== 0 ); */

    CNT_CONTAR("GRA_Del - Destruindo, finalizao");
	LIS_DestruirLista( g->nodes );

	free(g);
	return;
}

enum GRA_Ret searchData(LIS_tppLista l, void *data)
{
	Node* n;

	CNT_CONTAR("searchData - Inicializao");
	IrInicioLista(l);
	do{
        CNT_CONTAR("searchData - Procurando dado");
		n = LIS_ObterValor(LIS_ObterValor(l));
		if(data == n->data){
            CNT_CONTAR("searchData - Achou o dado");
			return GRA_Ok;
		}
	} while(LIS_CondRetOK == LIS_AvancarElementoCorrente (l, 1));
	CNT_CONTAR("searchData - Finalizacao");
	return GRA_InvalidArgNode;
}
enum GRA_Ret GRA_CCurrent (Graph *g, void *newCurrent)
{
    CNT_CONTAR("GRA_CCurrent - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	if (!newCurrent){
        CNT_CONTAR("GRA_CCurrent - Nao existe novo corrente");
		return GRA_InvalidArgNode;
    }
	if (GRA_Ok != searchData(g->nodes,newCurrent)){
        CNT_CONTAR("GRA_CCurrent - Nao encontrou no grafo novo corrente");
		return GRA_InvalidArgNode;
    }

    CNT_CONTAR("GRA_CCurrent - Seta novo corrente, finalizcaao");
	g->currentNode = LIS_ObterValor(g->nodes);
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	return GRA_Ok;
}

enum GRA_Ret GRA_NewNode (Graph *g, void *data)
{
	Node *n;
#ifdef _DEBUG
	Node *mirror;
	void *offset;
#endif /* _DEBUG */
	LIS_tppLista ln;
    CNT_CONTAR("GRA_NewNode - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
/* Inicio do bloco de codigo com tratamento de excecao */
	if (!data){
	    CNT_CONTAR("GRA_NewMode - Nao existe data a ser inserida");
		return GRA_NullData;
    }
    CNT_CONTAR("GRA_NewMode - Alocao de no");
	n = (Node *) malloc(sizeof(Node));
	if (!n){
        CNT_CONTAR("GRA_NewMode - Nao alocou no");
		return GRA_MemoryError;
    }

    CNT_CONTAR("GRA_NewMode - Criando Lista");
	ln = LIS_CriarLista(NULL);
	/* Para que ln possa se tornar heterogeneo, uso NULL */
	if (!ln){
        CNT_CONTAR("GRA_NewMode - Nao criou a Lista");
		free (n);
		return GRA_MemoryError;
	}

    CNT_CONTAR("GRA_NewMode - Inserindo elemento apos");
	if (LIS_CondRetOK != LIS_InserirElementoApos( ln, n )){
        CNT_CONTAR("GRA_NewMode - Nao inseriu elemento apos");
		free (n);
		LIS_DestruirLista( ln );
		return GRA_MemoryError;
	}

    CNT_CONTAR("GRA_NewMode - Criando lista de Links");
	n->links = LIS_CriarLista((FDelData) delLink );
	if (!n->links){
        CNT_CONTAR("GRA_NewMode - Nao criou lista de Links");
		free (n);
		LIS_DestruirLista( ln );
		return GRA_MemoryError;
	}

    CNT_CONTAR("GRA_NewMode - Inserindo no final da lista");
	IrFinalLista( g->nodes );
	if ( LIS_CondRetOK != LIS_InserirElementoApos( g->nodes , ln) ){
        CNT_CONTAR("GRA_NewMode - Nao inseriu no final da lista");
		LIS_DestruirLista( n->links );
		free (n);
		LIS_DestruirLista( ln );
		return GRA_MemoryError;
	}
/* Fim do bloco de codigo com tratamento de excecao */

    CNT_CONTAR("GRA_NewMode - Atribuicao, finalizacao");
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
	CNT_CONTAR("267 GRA_NewNode - Finalizacao");
#endif /* _DEBUG */
	return GRA_Ok;
}


void GRA_DelNode (Graph *g)
{
	Node *n;
#ifdef _DEBUG
	int nOfNodesAntigo = g->nOfNodes;
	AssertGraph(g);
#endif /* _DEBUG */

    CNT_CONTAR("GRA_delNode - Inicializao");
	assert(g->currentNode);
	n = (Node *) LIS_ObterValor(g->currentNode);
	assert( n!=NULL );
#ifdef _DEBUG
	AssertNode(n,g);
#endif /* _DEBUG */

    CNT_CONTAR("GRA_delNode - Deletando no");
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

	CNT_CONTAR("delNode - Destruindo lista de links");
	LIS_DestruirLista( n->links );
	if ( g->delData ){
         CNT_CONTAR("delNode - Existe g->delData");
		( *g->delData )( n->data );
    }
#ifdef _DEBUG
	IrFinalLista( g->currentNode );
	free(LIS_ObterValor( g->currentNode ));
	IrInicioLista( g->currentNode );
#endif /* _DEBUG */
    CNT_CONTAR("delNode - Finalizando");
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

	CNT_CONTAR("delLink - Inicio");
	if ( RecursionCnt <= 1 &&
			LIS_CondRetOK == LIS_ProcurarValor(l->n2->links,l->brother) ){
			CNT_CONTAR("delLink - Achou: Deletando Lista de Links");
		LIS_ExcluirElemento(l->n2->links);
	}
	CNT_CONTAR("delLink - Finalizando");
	free (l);
	RecursionCnt--;
}


/* Essa funcao e' responsavel por criar e compor 2 links ligando
 * 2 nos.
 */
enum GRA_Ret linkTwoNodes(Node *node1, Node *node2)
{
	Link *link1, *link2, *link;
	IrInicioLista(node1->links);
	CNT_CONTAR("linkTwoNodes - Inicializacao");
	do{ /* Assertiva: Nao repetir links */
	    CNT_CONTAR("linkTwoNodes - Procurando link igual");
		link = LIS_ObterValor(node1->links);
		if( link && link->n2 == node2 ){
            CNT_CONTAR("linkTwoNodes - Links iguais");
			return GRA_InvalidLink;
		}
	}while (LIS_CondRetOK == LIS_AvancarElementoCorrente (node1->links,1));

    CNT_CONTAR("linkTwoNodes - Compondo Links");
	link1 = (Link*) malloc (sizeof(Link));
	if (!link1){
	CNT_CONTAR("linkTwoNodes - Alocacao de link1 falhou");
		return GRA_MemoryError;
	}
	link2 = (Link*) malloc (sizeof(Link));
	if (!link2){
		/* Muito improvavel de cair aqui num teste
	CNT_CNTAR("linkTwoNodes - Alocacao de link2 falhou"); */
		free (link1);
		return GRA_MemoryError;
	}

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

	CNT_CONTAR("linkTwoNodes - Inserindo link 1 na lista");
	if( LIS_CondRetOK != LIS_InserirElementoApos(node1->links, link1) ){
        CNT_CONTAR("linkTwoNodes - Nao inseriu link 1 na lista");
		return GRA_MemoryError;
    }

    CNT_CONTAR("linkTwoNodes - Inserindo link 2 na lista");
	if( LIS_CondRetOK != LIS_InserirElementoApos(node2->links, link2) ){
        CNT_CONTAR("linkTwoNodes - Nao inseriu link 2 na lista");
		LIS_ExcluirElemento(node1->links);
		return GRA_MemoryError;
	}
#ifdef _DEBUG
	AssertLink(link1);
	AssertLink(link2);
#endif /* _DEBUG */
    CNT_CONTAR("linkTwoNodes - Finalizando");
	return GRA_Ok;
}

enum GRA_Ret GRA_AddLink (Graph *g, void *n)
{
	Node *n1, *n2;
	enum GRA_Ret ret;
    CNT_CONTAR("GRA_AddLink - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	if (!n){
	    CNT_CONTAR("GRA_AddLink - Nao existe n");
		return GRA_NullData;
    }
	if (!g->currentNode){
        CNT_CONTAR("GRA_AddLink - Nao existe g->currentNode");
		return GRA_InvalidCurrentNode;
    }
	n1 = LIS_ObterValor(g->currentNode);
	assert(n1);

    CNT_CONTAR("GRA_AddLink - Procurando no");
	if (searchData (g->nodes, n) != GRA_Ok){
        CNT_CONTAR("GRA_AddLink - Nao encontrou no");
		return GRA_InvalidArgNode;
    }
	n2 = LIS_ObterValor(LIS_ObterValor(g->nodes));
	if (n2 == n1){
        CNT_CONTAR("GRA_AddLink - Tentando criar link de n1 pra n1");
		return GRA_InvalidArgNode;
	}
#ifdef _DEBUG
	AssertNode(n1,g);
	AssertNode(n2,g);
#endif /* _DEBUG */
    CNT_CONTAR("GRA_AddLink - Ligando 2 nos");
	ret = linkTwoNodes(n1, n2);
#ifdef _DEBUG
	if (ret == GRA_Ok){
        CNT_CONTAR("GRA_AddLink - Ligou os nos");
		g->nOfLinks += 2;
    }
		AssertNode(n1,g);
		AssertNode(n2,g);
		AssertGraph(g);
#endif /* _DEBUG */
	return ret;
}

enum GRA_Ret GRA_RemLink (Graph *g, void *d)
{
	Node *curr;
	Link *l;
    CNT_CONTAR("GRA_RemLink - Inicio");
	if (!d){
        CNT_CONTAR("GRA_RemLink - Nao existe d");
		return GRA_NullData;
    }
	if (!g->currentNode){
        CNT_CONTAR("GRA_RemLink - Nao existe g->currentNode");
		return GRA_InvalidCurrentNode;
    }
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	curr = LIS_ObterValor (g->currentNode);
#ifdef _DEBUG
	AssertNode(curr,g);
#endif /* _DEBUG */

    CNT_CONTAR("GRA_RemLink - Procurando elemento");
	IrInicioLista (curr->links);
	do{
        CNT_CONTAR("GRA_RemLink - Avanando na lista");
		l = (Link*)LIS_ObterValor (curr->links);
		#ifdef _DEBUG
		AssertLink(l);
		#endif /* _DEBUG */
		if (l->n2->data == d){
             CNT_CONTAR("GRA_RemLink - Deletando elemento");
			/* deleta de curr -> n2 */
			LIS_ExcluirElemento(curr->links);
				/* isso deleta link e link->brother */
			#ifdef _DEBUG
			g->nOfLinks -= 2 ;
			AssertGraph(g);
			#endif /* _DEBUG */
			return GRA_Ok;
		}
	}while (LIS_AvancarElementoCorrente(curr->links, 1)
			== LIS_CondRetOK);

    CNT_CONTAR("GRA_RemLink - Finalizando");
	return GRA_InvalidArgNode;
}

void *GRA_GetData (Graph *g)
{
    CNT_CONTAR("GRA_GetData - Inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */

	if (g->currentNode){
        CNT_CONTAR("GRA_GetData - Obtendo valor");
		return ((Node *)LIS_ObterValor ( g->currentNode ))->data;
    }

    CNT_CONTAR("GRA_GetData - currentNode nao existe, finalizando");
	return NULL;
}

void GRA_NodesStart (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	if (!g->currentNode){
	    CNT_CONTAR("GRA_NodesStart - Nao existe currentNode");
		return;
    }

    CNT_CONTAR("GRA_NodesStart - Finalizando");
	g->nodesOld = NULL;
	IrInicioLista ( g->nodes );
}

void GRA_LinksStart (Graph *g)
{
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	if (!g->currentNode){
	    CNT_CONTAR("GRA_LinksStart - Nao existe currentNode");
		return;
    }

    CNT_CONTAR("GRA_LinksStart - Finalizando");
	g->linksOld = NULL;
	IrInicioLista ( ((Node *)LIS_ObterValor (g->currentNode))->links );
}

void *GRA_NodesGetNext (Graph *g)
{
	void *ret;
	LIS_tppLista l;
    CNT_CONTAR("GRA_NodesGetNext - inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	if (!g->currentNode){
		return NULL;
    }
    CNT_CONTAR("GRA_NodesGetNext - guardando g->nodes");
	l = g->nodes;
	if (!l){
        CNT_CONTAR("GRA_NodesGetNext - Nao existe g->nodes");
		return NULL;
    }
    CNT_CONTAR("GRA_NodesGetNext - Obtendo dado");
	ret = ((Node*)LIS_ObterValor (LIS_ObterValor(l)))->data;
	if (g->nodesOld == ret){ /* Se esse dado ja' repitiu, ja terminou a lista */
	    CNT_CONTAR("GRA_NodesGetNext - Dado repetido, fim da lista");
		return NULL;
	}
	CNT_CONTAR("GRA_NodesGetNext - Avanando elemento corrente");
	g->nodesOld = ret;
	LIS_AvancarElementoCorrente (l, 1);
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
    CNT_CONTAR("GRA_NodesGetNext - Finalizando");
	return ret;
}

void *GRA_LinksGetNext (Graph *g)
{
	void *ret;
	LIS_tppLista l;
    CNT_CONTAR("GRA_LinksGetNext - inicio");
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
	CNT_CONTAR("GRA_LinksGetNext - Inicializao");

	if (!g->currentNode){
	    CNT_CONTAR("GRA_LinksGetNext - Nao existe currentNode");
		return NULL;
    }
	CNT_CONTAR("GRA_LinksGetNext - Salvando lista de links");
	l = ((Node*)LIS_ObterValor (g->currentNode))->links;
	if (!LIS_ObterValor(l)){
        CNT_CONTAR("GRA_LinksGetNext - Nao acessou lista de links");
		return NULL;
    }

    CNT_CONTAR("GRA_LinksGetNext - Salvando dados");
	ret = ((Link*)LIS_ObterValor(l))->n2->data;
	if (g->linksOld == ret){ /* Se esse dado ja' repitiu, ja terminou a lista */
		CNT_CONTAR("GRA_LinksGetNext - Dado repetido, fim da lista");
        return NULL;
	}

	CNT_CONTAR("GRA_LinksGetNext - Avanando elemento corrente");
	g->linksOld = ret;
	LIS_AvancarElementoCorrente (l, 1);
#ifdef _DEBUG
	AssertGraph(g);
#endif /* _DEBUG */
    CNT_CONTAR("GRA_LinksGetNext - Finalizando");
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
    CNT_CONTAR("AssertLink - Verificando assertivas");
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
    CNT_CONTAR("AssertNode - Verificando assertivas");
	IrInicioLista(g->nodes);
	do{
        CNT_CONTAR("AssertNode - Procurando valor");
		if (n == LIS_ObterValor(LIS_ObterValor( g->nodes ))){
            CNT_CONTAR("AssertNode - Valor encontrado");
			assert( n->delData == g->delData );
			return;
		}
	} while(LIS_CondRetOK == LIS_AvancarElementoCorrente ( g->nodes , 1));
	/* Nao deveria cruzar esse ponto: Significa que nao foi encontrado
	 * n na lista g->nodes
	 */
	assert( 0 );
}

void AssertGraph(Graph *g)
{
	int i;

	CNT_CONTAR("AssertGraph - Verificando assertivas");
	assert( g->nOfNodes == 0 || g->currentNode !=NULL );
	assert( g->nOfLinks % 2 == 0 );

	IrInicioLista(g->nodes);
	for (	i=1;
			LIS_CondRetOK == LIS_AvancarElementoCorrente ( g->nodes , 1);
			i++ ){
            CNT_CONTAR("AssertGraph - Avanando elemento corrente");
        }

    CNT_CONTAR("AssertGraph - Verificando assertivas, finalizando");
	assert( i == g->nOfNodes || g->nOfNodes == 0 );
}
#endif /* _DEBUG */
