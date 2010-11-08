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

const char* NetNewUser (char *id);

char* NetDelMe();

char* NetEditMe();
/* Contem codigo de input para editar o perfil*/

char* NetSearch (int isFriend, char *id, enum interest in, int minAge, int maxAge);
/* posivelmente adicionar uma string com regexp sobre o nome mais tarde */

char* NetAddFriend (char *id);

char* NetUnfriend (char *id);

char* NetWrite (int destC, char * destV);
/* Contem codigo de input para editar a mensagem*/

char* NetRead (char * sender);

char* NetDelMsg (int msgNumber);


#endif /* NETMGR_ */

