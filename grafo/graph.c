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

// Graph definition
struct graph {
	LIS_tppLista nodes;
	int nOfNodes;
	int nOfLinks;
};
typedef struct graph Graph;

// Node definition
typedef struct {
	LIS_tppLista links;
	void * data;
} Node;

// Link definition
typedef struct {
	Node * head;  // node com o qual ha’ relacao
} Link;

