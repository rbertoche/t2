/***************************************************************************
*
*	$MCD Modulo de definicao: Net Manager
*
*	Arquivo gerado:		netmgr.h
*
*	Autores: gac mpl rlb 
*
*	$ED Descricao do modulo
*	Esse modulo retorna strings que podem ser printadas por um modulo
*	de interface, para reduzir o acoplamento entre o modulo de interface
*	e este modulo. Alem disso o codigo que manipula strings a serem printadas
*	fica concentrado em um so' modulo.
*
***************************************************************************/
#include "usr.h"

#ifndef NETMGR_
#define NETMGR_

/* Sera' 0 quando nao houver usuario autenticado
 * ou 1 quando houver
 */

int NetIsAuthenticated();

const char* NetNewUser (const char *id);

const char* NetDelMe();

const char* NetEditMe();
/* Contem codigo de input para editar o perfil*/

void switchUsr (const char *id);

const char* NetSearch (int isFriend, const char *id, enum interest in, int minAge, int maxAge);
/* posivelmente adicionar uma string com regexp sobre o nome mais tarde */

/* TODO: Mesmo usuario pode ser adicionado multiplas vezes? */
const char* NetAddFriend (char *id);

const char* NetUnfriend (char *id);

const char* NetWrite (int destC, char * destV);
/* Contem codigo de input para editar a mensagem*/

const char* NetRead (int msgNumber);

const char* NetDelMsg (int msgNumber);

const char* NetWhoAmI ();

const char* NetMail ();

#endif /* NETMGR_ */

