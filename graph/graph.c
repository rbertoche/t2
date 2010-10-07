/*

Diagrama UML do modelo fisico da implementacao de grafo

   =========  1    owns     1  =================       
   | Graph | --------------->  | List of Nodes |       
   =========                   =================       
                                      | 1              
                                      | owns           
                                     \/ 0..*           
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
	/* typecast para acessar ponteiro pra funcao */
	(*( ((Node *)n)->DelData)) (n->data);
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


