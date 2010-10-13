
#ifndef GRAORE_
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
*	Nao ha' suporte para armazenar o mesmo ponteiro em mais de um no'.
*	O ponteiro e' o unica forma de identificar um no' para o cliente.
*
***************************************************************************/
 

/***********************************************************************
*	$TC Tipo de Dados: pGraph
*	$ED Descrição do tipo
*		Identificador do grafo dentro e fora do modulo.
***********************************************************************/
typedef struct graph *pGraph;

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
*		tenha ocorrido
*
***********************************************************************/
typedef void (*FDelData)(void *data);
pGraph GraphNew (FDelData fdd);


/***********************************************************************
*
*	$FC Metodo: Graph Delete
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$ED Descricao da funcao
*		Se foi passada uma funcao em GraphNew(), esta e' chamada
*		para excluir 'data'.
*
*	Ha uma assertiva de entrada: g e um ponteiro pra um Graph valido
*
***********************************************************************/
void GraphDel (pGraph g);


/***********************************************************************
*
*	$FC Metodo: Graph Change Current
*	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P newCurrentNode - Ponteiro para o 'data' contido no 
*		'Node' que sera' current
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphInvalidArgNode - Caso newCurrentData for nulo ou
*			nenhum 'Node' contendo newCurretData exista.
*
***********************************************************************/
enum graphRet GraphCCurrent (pGraph g, void *newCurrentData);


/***********************************************************************
*
*	$FC Metodo: Graph New Node
*	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P data - Ponteiro generico para 'data' que o novo 'Node' 
*		possuira'
*	$ED Descricao da funcao
*		Aloca novo 'Node'; 'currentNode' vira esse novo 'Node'.
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphNullData
*
***********************************************************************/
enum graphRet GraphNewNode (pGraph g, void *data);


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
*		para excluir 'currentNode->data'.
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphInvalidCurrentNode
*
***********************************************************************/
enum graphRet GraphDelNode (pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Add Link
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P d - Ponteiro para o 'data' do 'Node' a ser ligado
*			ao 'currentNode'
*
*	$ED Descricao da funcao
*		Cria um link entre 'currentNode' e o 'Node' que contem 'd'
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphInvalidCurrentNode
*		graphInvalidArgNode
*
***********************************************************************/
enum graphRet GraphAddLink (pGraph g, void *d);

/***********************************************************************
*
*	$FC Metodo: Graph Rem Link
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P d - Ponteiro para o 'Node' head do link a ser apagado
*
*	$ED Descricao da funcao
*		Apaga um link entre 'currentNode' e o 'Node' contendo 'd'
*
*	$FV Valor retornado
*		graphOk
*		graphInvalidGraph
*		graphInvalidCurrentNode
*		graphInvalidArgNode
*		graphInvalidLink
*
***********************************************************************/
enum graphRet GraphRemLink (pGraph g, void *n);
/* melhor GraphRMLink? */


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
void *GraphGetData (pGraph g);


/***********************************************************************
*
*	$FC Metodo: Graph Get Data
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*	$ED Descricao da funcao
*		Retorna data do proximo 'head' entre os links de 
*		'currentNode'
*
*	$FV Valor retornado
*		Ponteiro para 'data' do proximo 'linkado' ou, ao fim da 
*		lista, para 'NULL'
*
***********************************************************************/
void *GraphGetSuccessor (pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Iterator Start
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*	$ED Descricao da funcao
*		Garante que a proxima chamada de GraphSearchNext retornara
*		'data' do primeiro Node, e que GraphSearchNext so retornara 
*		NULL depois de ter percorrido todos os Nodes.
*
***********************************************************************/
void GraphIterStart(pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Iterator Next
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*	$ED Descricao da funcao
*		Retorna 'data' do proximo Node a na iteracao. Use junto com
*		GraphIterStart.
*
*	$FV Valor retornado
*		Ponteiro para 'data' do proximo node ou, ao fim da lista, 
*		para 'NULL'
*
***********************************************************************/
void *GraphIterNext (pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Iterator Set Current
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*	$ED Descricao da funcao
*		Modifica 'currentNode' para o ultimo 'Node' consultado
*		com GraphIterNext.
*
***********************************************************************/
void GraphIterSetCurrent (pGraph g);

#endif /* GRAORE_ */

