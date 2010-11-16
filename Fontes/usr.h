/***************************************************************************
*
*	$MCD Modulo de definicao: User
*
*	Arquivo gerado:		usr.h
*
*	Autores: rlb 
*
*	$ED Descricao do modulo
*
***************************************************************************/
#ifndef USR_
#define USR_
#ifndef LIS_tpp_typedef
   #define LIS_tpp_typedef
typedef struct LIS_tagLista * LIS_tppLista ;
#endif
/***********************************************************************
*	$TC Tipo de Dados: interest
*	$ED Descri√ß√£o do tipo
*		EnumeraÁ„o de possiveis interesses de usu·rios da rede.
***********************************************************************/
enum interest {
	INVALID,
	WORK,
	FRIENDS,
	SEX,
	NONE
};

/***********************************************************************
*	$TC Tipo de Dados: usr
*	$ED Descri√ß√£o do tipo
*		Estrutura de definiÁ„o de usu·rio da rede.
***********************************************************************/
struct usr{
	char id[15];
	char name[50];
	int age;
	enum interest interest;
	LIS_tppLista msgs;
};
typedef struct usr Usr;

typedef char *msg;

/***********************************************************************
*
*	$FC Funcao: UsrNew
*
*	$EP Parametros
*		$C id - identificador do usu·rio
*
*	$ED Descri√ß√£o da fun√ß√£o
*		Cria (aloca) um novo nÛ da estrutura Usr.
*
*	$FV Valor retornado
*		Ponteiro para estrutura us alocada.
*
***********************************************************************/	
Usr *UsrNew( const char id[15] );

void UsrDel( void *u );

/***********************************************************************
*
*	$FC Funcao: UsrPrint
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usu·rio desejado
*       $P buffer - string onde ficar· o resultado da "impress„o"
*       $i buffersize - delimitador de tamanho da string buffer
*
*	$ED Descri√ß√£o da fun√ß√£o
*		Gera uma string de informacoes sobre o usuario sobre buffer, com menos
*       que buffersize caracteres.
*
*	$FV Valor retornado
*		N˙mero de caractreres impressos.
*
***********************************************************************/
int UsrPrint( Usr *u, char *buffer, int buffersize );

/***********************************************************************
*
*	$FC Funcao: UsrMsgList
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usu·rio desejado
*       $P buffer - string onde ficar· o resultado da "listagem"
*       $i buffersize - delimitador de tamanho da string buffer
*
*	$ED Descri√ß√£o da fun√ß√£o
*		Gera uma string de informacoes sobre o usuario sobre buffer, com menos
*       que buffersize caracteres.
*
*	$FV Valor retornado
*		N˙mero de caractreres impressos.
*
***********************************************************************/
int UsrMsgList( Usr *u, char *buffer, int buffersize );

/***********************************************************************
*
*	$FC Funcao: UsrMsgDeliver
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usu·rio desejado
*       $P m - mensagem a ser entregue ao usu·rio. 
*
*	$ED Descri√ß√£o da fun√ß√£o
*		Coloca a mensagem recebida na lista de mensagens do usu·rio u.
*      
*
*	$FV Valor retornado
*		Retorna o retorno da chamada LIS_InserirElementoApos
*       (0 em caso de sucesso)
*
***********************************************************************/
int UsrMsgDeliver ( Usr *u, msg m);

/***********************************************************************
*
*	$FC Funcao: UsrMsgPrint
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usu·rio desejado
*       $i msg - mensagem a ser entregue ao usu·rio. 
*       $P buffer - string onde ficar· o resultado da "listagem"
*       $i buffersize - delimitador de tamanho da string buffer
*
*	$ED Descri√ß√£o da fun√ß√£o
*		Gera uma string contendo a mensagem numero msg da lista de mensagens 
*       de u sobre buffer, com menos que buffersize caracteres.
*      
*
*	$FV Valor retornado
*       N˙mero de caracteres impressos.
*
***********************************************************************/
int UsrMsgPrint( Usr *u, int msg, char *buffer, int buffersize );

/***********************************************************************
*
*	$FC Funcao: UsrDelMsg
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usu·rio desejado
*       $i msg - mensagem a ser deletada do usu·rio. 
*
*	$ED Descri√ß√£o da fun√ß√£o
*       Exclui mensagem numero msg da lista de mensagens de u.
*
*	$FV Valor retornado
*       Retorna 0 caso nao tenha recebido nenhum erro do mÛdulo de 
*       listas.
*
***********************************************************************/
int UsrDelMsg ( Usr *u, int msg);

#endif /* USR_ */


