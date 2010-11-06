/***************************************************************************
*
*	$MCD Modulo de definicao: Net Manager
*
*	Arquivo gerado:		netmgr.h
*
*	Autores: gac mpl rlb 
*
*	$ED Descricao do modulo
*
***************************************************************************/


#ifndef GRAORE_

enum interest {
	WORK,
	FRIENDS,
	SEX,
	NONE
}

/* Caso esse modulo va' gerar muitas strings, me parece fazer sentido que
ele nao retorne condicoes de retorno em enum, mas em strings com mensagens de erro
ou com NULL ou com a informacao pedida.

Dessa forma concentramos codigo que manipula essas strings nesse modulo ao inves
de empurrar pra outro.
*/

char* NetNewUser (char *id);

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



#define GRAORE_









#endif /* GRAORE_ */

