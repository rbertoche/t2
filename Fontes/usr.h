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
#include "lista.h"
enum interest {
	INVALID,
	WORK,
	FRIENDS,
	SEX,
	NONE
};

struct usr{
	char id[15];
	char name[50];
	int age;
	enum interest interest;
	LIS_tppLista msgs;
};
typedef struct usr Usr;

typedef char *msg;
	
Usr *UsrNew( char id[15] );

void UsrDel( void *u );

int UsrPrint( Usr *u, char *buffer, int buffersize );
/* Gera uma string de informacoes sobre o usuario sobre buffer, com menos
 * que buffersize caracteres.
 * O retorno e' o numero de caracteres impressos.
 */

int UsrMsgPrint( Usr *u, char *buffer, int buffersize );
/* Gera uma string de informacoes sobre o usuario sobre buffer, com menos
 * que buffersize caracteres.
 * O retorno e' o numero de caracteres impressos.
 */

int UsrDeliver ( Usr *u, msg m);
/* Appenda mensagem `a lista desse usua rio */

int UsrDelMsg ( Usr *u, int id);
/* Exclui idesima msg do usuario. Retorna 0 caso nao tenha recebido
 * nenhum erro do modulo de listas.
 */

#endif /* USR_ */


