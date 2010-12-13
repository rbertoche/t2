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


#ifndef GRA_
#define GRA_


/***********************************************************************
*	$TC Tipo de Dados: pGraph
*	$ED Descrição do tipo
*		Identificador do grafo dentro e fora do modulo.
***********************************************************************/
typedef struct graph *pGraph;


/***********************************************************************
*	$TC Tipo de Dados: GRA_Ret
*	$ED Descrição do tipo
*		Condicoes de retorno das funcoes Graph
***********************************************************************/
enum GRA_Ret {
	GRA_Ok,
	GRA_InvalidGraph,
	GRA_InvalidCurrentNode,
	GRA_InvalidArgNode,
	GRA_InvalidLink,
	GRA_NullData,
	GRA_MemoryError
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
pGraph GRA_New (FDelData fdd);

/***********************************************************************
*
*	$FC Metodo: Graph Delete
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$ED Descricao da funcao
*		Se foi passada uma funcao em GRA_New(), esta e' chamada
*		para excluir 'data'.
*		g deve ser um ponteiro pra um Graph valido
*
***********************************************************************/
void GRA_Del (pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Change Current
*	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P newCurrentNode - Ponteiro para o 'data' contido no
*		'Node' que sera' current
*
*	$FV Valor retornado
*		GRA_Ok
*		GRA_InvalidGraph
*		GRA_InvalidArgNode - Caso newCurrentData for nulo ou
*			nenhum 'Node' contendo newCurretData exista.
*
***********************************************************************/
enum GRA_Ret GraphCCurrent (pGraph g, void *newCurrentData);

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
*		GRA_Ok
*		GRA_InvalidGraph
*		GRA_NullData
*
***********************************************************************/
enum GRA_Ret GRA_NewNode (pGraph g, void *data);

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
*		Se foi passada uma funcao em GRA_New(), esta e' chamada
*		para excluir 'currentNode->data'.
*
*	$FV Valor retornado
*		GRA_Ok
*		GRA_InvalidGraph
*		GRA_InvalidCurrentNode
*
***********************************************************************/
void GRA_DelNode (pGraph g);

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
*		GRA_Ok
*		GRA_InvalidGraph
*		GRA_InvalidCurrentNode
*		GRA_InvalidArgNode
*
***********************************************************************/
enum GRA_Ret GraphAddLink (pGraph g, void *d);

/***********************************************************************
*
*	$FC Metodo: Graph Remove Link
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*		$P d - Ponteiro para o 'Node' head do link a ser apagado
*
*	$ED Descricao da funcao
*		Apaga um link entre 'currentNode' e o 'Node' contendo 'd'
*
*	$FV Valor retornado
*		GRA_Ok
*		GRA_InvalidGraph
*		GRA_InvalidCurrentNode
*		GRA_InvalidArgNode
*		GRA_InvalidLink
*
***********************************************************************/
enum GRA_Ret GraphRemLink (pGraph g, void *d);

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
void *GRA_GetData (pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Nodes Start
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$ED Descricao da Funcao
*		Garante que o proximo elemento lido por GRA_NodesGetNext
*		e' o primeiro da lista de nodes do grafo.
*
***********************************************************************/
void GRA_NodesStart(pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Links Start
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$ED Descricao da Funcao
*		Garante que o proximo elemento lido por GRA_LinksGetNext
*		e' o primeiro da lista de links do 'currentNode' do grafo.
*
***********************************************************************/
void GRA_LinksStart (pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Nodes Get Next
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$ED Descricao da Funcao
*		Pega o 'data' do elemento atual e avanca um elemento na
*		lista de nodes do 'Graph'.
*
*	$FV Valor retornado
*		Ponteiro 'data' do proximo no da lista de nodes ou NULL
*		Caso a lista tenha terminado.
*
***********************************************************************/
void *GRA_NodesGetNext (pGraph g);

/***********************************************************************
*
*	$FC Metodo: Graph Links Get Next
*
* 	$EP Parametros
*		$P g - Ponteiro para o 'Graph' a ser manipulado
*
*	$ED Descricao da Funcao
*		Pega o 'data' do elemento atual e avanca um elemento na
*		lista de links do 'currentNode'.
*
*	$FV Valor retornado
*		Ponteiro 'data' do proximo no da lista de links ou NULL
*		Caso a lista tenha terminado.
*
***********************************************************************/
void *GRA_LinksGetNext (pGraph g);


#endif /* GRA_ */

