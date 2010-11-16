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
*	$ED Descricao do tipo
*		Enumeração de possiveis interesses de usuários da rede.
*	$ED Descricao do tipo
*		Enumeracao de possiveis interesses de usuarios da rede.
***********************************************************************/
enum interest {
	INVALID = 0,
	WORK,
	FRIENDS,
	SEX,
	NONE
};

/***********************************************************************
*	$TC Tipo de Dados: usr
*	$ED Descricao do tipo
*		Estrutura de definição de usuário da rede.
*	$ED Descricao do tipo
*		Estrutura de definicao de usuario da rede.
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
*		$C id - identificador do usuario
*
*	$ED Descricao da funcao
*		Cria (aloca) um novo nó da estrutura Usr.
*	$ED Descricao da funcao
*		Cria (aloca) um novo no da estrutura Usr.
*
*	$FV Valor retornado
*		Ponteiro para estrutura us alocada.
*
***********************************************************************/
Usr *UsrNew( const char id[15] );

/***********************************************************************
*
*	$FC Funcao: UsrDel
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usuário a ser deletado
*
*	$ED Descricao da funcao
*		Desaloca a lista de mensagens do usuário bem como a sua estrutura
*       da memória.
*
*	$FV Valor retornado
*		Número de caractreres impressos.
*
***********************************************************************/
void UsrDel( void *u );

/***********************************************************************
*
*	$FC Funcao: UsrPrint
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usuario desejado
*       $P buffer - string onde ficara o resultado da "impressao"
*       $i buffersize - delimitador de tamanho da string buffer
*
*	$ED Descricao da funcao
*		Gera uma string de informacoes sobre o usuario sobre buffer, com menos
*       que buffersize caracteres.
*
*	$FV Valor retornado
*		Nï¿½mero de caractreres impressos.
*
***********************************************************************/
int UsrPrint( Usr *u, char *buffer, int buffersize );

/***********************************************************************
*
*	$FC Funcao: UsrMsgList
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usuario desejado
*       $P buffer - string onde ficara o resultado da "listagem"
*       $i buffersize - delimitador de tamanho da string buffer
*
*	$ED Descricao da funcao
*		Gera uma string de informacoes sobre o usuario sobre buffer, com menos
*       que buffersize caracteres.
*
*	$FV Valor retornado
*		Nï¿½mero de caractreres impressos.
*
***********************************************************************/
int UsrMsgList( Usr *u, char *buffer, int buffersize );

/***********************************************************************
*
*	$FC Funcao: UsrMsgDeliver
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usuario desejado
*       $P m - mensagem a ser entregue ao usuario.
*
*	$ED Descricao da funcao
*		Coloca a mensagem recebida na lista de mensagens do usuário u.
*	$ED Descricao da funcao
*		Coloca a mensagem recebida na lista de mensagens do usuï¿½rio u.
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
*		$P u - ponteiro para estrutura usr, contendo o usuario desejado
*       $i msg - mensagem a ser entregue ao usuï¿½rio.
*       $P buffer - string onde ficara o resultado da "listagem"
*       $i buffersize - delimitador de tamanho da string buffer
*
*	$ED Descricao da funcao
*		Gera uma string contendo a mensagem numero msg da lista de mensagens
*       de u sobre buffer, com menos que buffersize caracteres.
*
*
*	$FV Valor retornado
*       Nï¿½mero de caracteres impressos.
*
***********************************************************************/
int UsrMsgPrint( Usr *u, int msg, char *buffer, int buffersize );

/***********************************************************************
*
*	$FC Funcao: UsrMsgDel
*
*	$EP Parametros
*		$P u - ponteiro para estrutura usr, contendo o usuario desejado
*       $i msg - mensagem a ser deletada do usuario.
*
*	$ED Descricao da funcao
*       Exclui mensagem numero msg da lista de mensagens de u.
*
*	$FV Valor retornado
*       Retorna 0 caso nao tenha recebido nenhum erro do módulo de
*       listas.
*
***********************************************************************/
int UsrMsgDel ( Usr *u, int msg);

#endif /* USR_ */


