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
	int nOfNodes;
	int nOfLinks;
};

// Link definition
typedef struct {
	Node * head;  // node com o qual ha’ relacao
} Link;


Graph *graphNew (FDelData fdd)
{
}
void graphDel (Graph *g)
{
}
enum graphRet graphCCurrent (Graph *g, Node *newCurrent)
{
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


