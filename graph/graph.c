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

// Node definition
typedef struct {
	LIS_tppLista links;
	void * data;
} Node;

// Graph definition
struct graph {
	LIS_tppLista nodes;
	Node * currentNode;
	FDelData delData;
	int nOfNodes;
	int nOfLinks;
};

// Link definition
typedef struct {
	Node * head;  // node com o qual ha’ relacao
} Link;




Graph *graphNew (FDelData fdd)
{
	Graph *g;
	g = (Graph *) malloc(sizeof(Graph));
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

void graphDel (Graph *g)
{
	/* Deleta o unico recurso diretamente possuido por Graph */
	LIS_DestruirLista( g->nodes );
	free(g);
	return;
}

enum graphRet graphCCurrent (Graph *g, Node *newCurrent)
{
	if (!g){
		return graphInvalidGraph;
	}if (!newCurrent){
		return graphInvalidArgNode;
	}
	g->currentNode = newCurrent;
}
enum graphRet graphNewNode (Graph *g, void *data)
{
}
enum graphRet graphDelNode (Graph *g)
{
}
enum graphRet graphAddLink (Graph *g, Node *n)
{
}
enum graphRet graphRemLink (Graph *g, Node *n)
{
}
void *graphGetData (Graph *g)
{
}
void *graphGetSuccessor (Graph *g)
{
}


