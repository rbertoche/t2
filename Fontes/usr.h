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

enum interest {
	WORK,
	FRIENDS,
	SEX,
	NONE
};
typedef struct usr *pUsr;
typedef char *msg;
	
pUsr UsrNew( char id[15] );

void UsrDel( void *u );

char* UsrGetPId( pUsr u );
/* Retorna ponteiro cujo conteudo pode ser alterado */

char* UsrGetPName( pUsr u );
/* Retorna ponteiro cujo conteudo pode ser alterado */

enum interest* UsrGetPInterest( pUsr u );
/* Retorna ponteiro cujo conteudo pode ser alterado */

int UsrDeliver ( pUsr u, msg m);
/* Appenda mensagem `a lista desse usua rio */

int UsrDelMsg ( pUsr u, int id);
/* Exclui idesima msg do usuario. Retorna 0 caso nao tenha recebido
 * nenhum erro do modulo de listas.
 */

#endif /* USR_ */


