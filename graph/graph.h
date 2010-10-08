#ifndef( GRAORE_ )
#define GRAORE_

#include "../lista/lista.h"

/***************************************************************************
*
*	$MCD Módulo de definição: Graph	
*
*	Arquivo gerado:		graph.h
*
*	Autores: rlb
*
*	$HA Histórico de evolução:
*		Vide repositorio Git
*
*	$ED Descrição do módulo
*
*	Implementa um grafo simples permitindo:
*		* Vertices paralelos ou repetidos;
*		* Lacos ou loops;
*		* Grafos disconexos
*	A implementacao e' feita atraves de um digrafo simetrico
*		(para cada seta ha' igual no sentido oposto).
*
*	Cada vertice contem um ponteiro generico nao nulo.
*
***************************************************************************/
 

/***********************************************************************
*	$TC Tipo de Dados: pGraph
*	$ED Descrição do tipo
*		Identificador do grafo dentro e fora do modulo.
***********************************************************************/
typedef Graph * pGraph;

/***********************************************************************
*	$TC Tipo de Dados: graphRet
*	$ED Descrição do tipo
*		Condicoes de retorno das funcoes Graph
***********************************************************************/
enum graphRet {
	graphOk,
	graphInvalidGraph,
	graphInvalidCurrentNode,
	graphInvalidArgNode,
	graphInvalidLink,
	graphNullData,
	graphMemoryError
};

/***********************************************************************
*
*	$FC Funcao: Graph New
*
*	$EP Parametros
*		$P fdd - ponteiro para funcao usado para deletar 'data'.
*			A funcao deve retornar 'void' e receber 'void *'.
*			Caso queira que o grafo nao delete 'data', passe 'NULL'.
* 
*	$ED Descrição da função
*		Cria um novo grafo vazio e retorna um ponteiro para tal.
*
*	$FV Valor retornado
*		Ponteiro para novo grafo ou para NULL caso algum problema
*			tenha ocorrido
*
***********************************************************************/
typedef void (*FDelData)(void *data);
Graph *graphNew (FDelData fdd);


/***********************************************************************
*
*	$FC Metodo: Graph Delete
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$ED Descricao da funcao
*		Se foi passada uma funcao em GraphNew(), esta e' chamada
*			para excluir 'data'.
*
*	Ha uma assertiva de entrada: g e um ponteiro pra um Graph valido
*
***********************************************************************/
void GraphDel (Graph *g);


/***********************************************************************
*
*	$FC Metodo: Graph Change Current
*	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P newCurrent - Ponteiro para o 'Node' que sera' current
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphInvalidArgNode
*
***********************************************************************/
enum graphRet GraphCCurrent (Graph *g, Node *newCurrent);


/***********************************************************************
*
*	$FC Metodo: Graph New Node
*	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P data - Ponteiro generico para 'data' que o novo 'Node' 
*			possuira'
*	$ED Descricao da funcao
*		Aloca novo 'Node'; 'currentNode' vira esse novo 'Node'.
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphNullData
*
***********************************************************************/
enum graphRet GraphNewNode (Graph *g, void *data);


/***********************************************************************
*		As proximas funcoes manipulam sempre o 'currentNode'
*
***********************************************************************/

/***********************************************************************
*
*	$FC Metodo: Graph Delete Node
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$ED Descricao da funcao
*		Deleta 'currentNode'. 'currentNode' se torna'Null'.
*		Se foi passada uma funcao em GraphNew(), esta e' chamada
*			para excluir 'currentNode->data'.
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphInvalidCurrentNode
*
***********************************************************************/
enum graphRet GraphDelNode (Graph *g);

/***********************************************************************
*
*	$FC Metodo: Graph Add Link
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P n - Ponteiro para o 'Node' a ser head do novo link
*
*	$ED Descricao da funcao
*		Cria um link entre 'currentNode' e 'n'
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphInvalidCurrentNode
*		graphInvalidArgNode
*
***********************************************************************/
enum graphRet GraphAddLink (Graph *g, Node *n);

/***********************************************************************
*
*	$FC Metodo: Graph Add Link
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P n - Ponteiro para o 'Node' head do link a ser apagado
*
*	$ED Descricao da funcao
*		Apaga um link entre 'currentNode' e 'n'
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphInvalidCurrentNode
*		graphInvalidArgNode
*		graphInvalidLink
*
***********************************************************************/
enum graphRet GraphRemLink (Graph *g, Node *n);
//melhor GraphRMLink?


/***********************************************************************
*
*	$FC Metodo: Graph Get Data
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$FV Valor retornado
*		Ponteiro 'currentNode->data'
*
***********************************************************************/
void *GraphGetData (Graph *g);


/***********************************************************************
*
*	$FC Metodo: Graph Get Data
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*	$ED Descricao da funcao
*		Retorna data do proximo 'head' entre os links de 'currentNode'
*		FIXME:lembrar de tirar isso: 
*			Pra usar dentro de for ou do foreach
*	$FV Valor retornado
*		Ponteiro para 'data' do sucessor ou para 'NULL'
*
***********************************************************************/
void *GraphGetSuccessor (Graph *g);


#endif /* GRAORE_ */

