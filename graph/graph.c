#include <stdlib.h>
/*

Diagrama UML do modelo fisico da implementacao de grafo
'owns' significa atrelamento de tempo de vida, 
responsabilidade pelo desalocamento

          =========  1 owns 1  =================          |
          | Graph | -------->  | List of Nodes |          |
          =========            =================          |
                  1\    owns          | 1                 |
                    \-------\         |                   |
                             \        | lists             |
                         0..* \       |                   |
                              \/      \/ 0..*             |
    ========                   =================          |
    | Data |  1    owns    1   |  Node         |          |
    | -??? |  <--------------- =================          |
    ========                    | 1          /\           |
                                | owns        | 0..*      |
                                | 1           | links to  |
                               \/             | 0..*      |
                               =================          |
                               | List of Links |          |
                               =================          |
*/

#include "graph.h"
#include "../lista/lista.h"


typedef struct graph Graph;
typedef struct node Node;
/* Graph definition */
struct graph {
	LIS_tppLista nodes;
	Node * currentNode;
	FDelData delData;
	int nOfNodes;
	int nOfLinks;
};

/* Node definition */
struct node {
	LIS_tppLista links;
	void * data;
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
/* Houve um problema aqui: Como deletar Node?
 *
 * A lista 'nodes' poderia deletar 'node' com uma funcao que ela recebe por
 * ponteiro, de assinatura void foo (void *). Mas pra deletar 'node' voce
 * precisa deletar 'data', e pra isso voce precisa do ponteiro de funcao
 * que esta em cada instancia de graph. Como a funcao passada para a lista
 * 'nodes' vai chamar essa funcao?
 *
 * 1 - O modulo pode ter armazenado internamente todos os grafos
 * e ter uma funcao que procura um determinado no em todos os grafos
 * e o apaga. Essa funcao pode ser passada pra lista 'nodes'.
 *
 * 2 - Cada no' pode possuir um ponteiro para o destrutor de data.
 * Assim, delNode pode executar:  (*n->delData) (n->data);
 *
 * 3 - Nao delegar a responsabilidade de apagar os nos a lista 'nodes':
 * Passar NULL na sua construcao e adicionar codigo para apagar 'data' em
 * todas as funcoes que podem apagar nos.
 *
 * Eu escolho o numero 3.
 */

void delNode (Graph *g, void *n_)
{
	Node * n=n_;
	LIS_DestruirLista( n->links );
	( *g->delData )( n->data );		
}	
	

enum graphRet GraphAddLink (Graph *g, void *n)
{
return graphOk;
}
enum graphRet GraphRemLink (Graph *g, void *n)
{
return graphOk;
}
void *GraphGetData (Graph *g)
{
return NULL;
}
void *GraphGetSuccessor (Graph *g)
{
return NULL;
}


