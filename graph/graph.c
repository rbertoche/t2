/*

Diagrama UML do modelo fisico da implementacao de grafo
'owns' significa atrelamento de tempo de vida.

   =========  1    owns     1  =================       
   | Graph | --------------->  | List of Nodes |       
   =========                   =================       
          \ 1       owns              | 1              
           \--------------------\     |		       
                            0..*|     | lists          
                                \/    \/ 0..*          
    ========  1    owns    1   =================       
    | Data | <---------------  |  Node         |       
    | -??? |                   =================       
    ========                    | 1          /\        
                                | owns        | 1      
                                | 1           | links to  
                               \/             | 0..*      
                =================  1   0..*  =========    
                | List of Links |----------->| Link  |    
                =================    owns    =========    
*/

#include "graph.h"

typedef struct node Node;
typedef struct link Link;
// Graph definition
struct graph {
	LIS_tppLista nodes;
	Node * currentNode;
	FDelData delData;
	int nOfNodes;
	int nOfLinks;
};

// Link definition
struct link {
	Node * head;  // node com o qual ha’ relacao
};

// Node definition
struct node {
	LIS_tppLista links;
	void * data;
	FDelData delData;
};


Graph *GraphNew (FDelData fdd)
{
	Graph *g;
	g = (Graph *) malloc(sizeof(Graph));
	if (g!)
		return NULL;
	g->nodes = LIS_CriarLista(delNode);
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
	/* Deleta o unico recurso diretamente possuido por Graph */
	LIS_DestruirLista( g->nodes );
	free(g);
	return;
}

enum graphRet GraphCCurrent (Graph *g, Node *newCurrent)
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
	n->links = LIS_CriarLista(delLink);
	n->data = data;
	n->delNode = g->delNode;
	IrFinalLista( g->nodes );
	if (!LIS_InserirElementoApos( g->nodes , n)){
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
		return graphInvalidCurrentNode
	delNode(g->currentNode);
	g->currentNode=0;
	
}
void delNode (void *n)
{
/* Essa funcao sera' passada na construcao da lista 'nodes'
 * pois a lista precisa apagar os nos.
 * Problema: Para apagar os nos e' necessario chamar (*g->delData).
 * Como trazer esse ponteiro ate aqui sem mudar a assinatura da
 * funcao?
 * 
 * 1 - O modulo pode ter armazenado internamente todos os grafos
 * e ter uma funcao que procura um determinado no em todos os grafos
 * e o apaga. Essa funcao pode ser passada pra lista 'nodes'.
 * 
 * 2 - Cada no' pode possuir um ponteiro para o destrutor de data.
 * Assim, delNode pode executar:  (*n->DelData) (n->data);
 *
 * 3 - Nao delegar a responsabilidade de apagar os nos a lista 'nodes':
 * Passar NULL na sua construcao e adicionar codigo para apagar 'data' em
 * todas as funcoes que podem apagar nos. 
 * 
 * Eu escolho o numero 3.
 */

	LIS_DestruirLista (n->links);
}
enum graphRet GraphAddLink (Graph *g, Node *n)
{
}
enum graphRet GraphRemLink (Graph *g, Node *n)
{
}
void *GraphGetData (Graph *g)
{
}
void *GraphGetSuccessor (Graph *g)
{
}


