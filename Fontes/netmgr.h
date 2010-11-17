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
/***********************************************************************
*
*	$FC Funcao: NetIsAuthenticated
*
*	$ED Descrição da função
*		Retorna se existe um usuario corrente no sistema.
*
*	$FV Valor retornado
*		Retorna 0 caso nao hava usuario corrente.
*
***********************************************************************/
int NetIsAuthenticated();

/***********************************************************************
*
*	$FC Funcao: NetNewUser
*
*	$EP Parametros
*		$P id - Id do usuario a ser adicionado
*
*	$ED Descrição da função
*		Cria usuario 'id' caso nao exista usuario com 'id'.
*
*	$FV Valor retornado
*		Caso usuario ja existir: "ID escolhido ja' em uso.\n"
*		Caso 'id' contiver ":":
*			"ID contem caracteres invalidos.\n"
*		Caso sucesso: "Novo usuario criado.\n"
*
***********************************************************************/
const char* NetNewUser (const char *id);

/***********************************************************************
*
*	$FC Funcao: NetDelMe
*
*	$ED Descrição da função
*		Deleta o usuario corrente e suas relacoes com outros usuarios.
*
*	$FV Valor retornado
*		"Usuario excluido com sucesso.\n"
*
***********************************************************************/
const char* NetDelMe();

/***********************************************************************
*
*	$FC Funcao: NetEditMe
*
*	$ED Descrição da função
*		Recebe de forma interativa os parametros de cadastro do usuario
*	corrente. 1. Nome, 2. interesse, 3. Idade
*
*	$FV Valor retornado
*		"Perfil salvo.\n"
*
***********************************************************************/
const char* NetEditMe();

/***********************************************************************
*
*	$FC Funcao: NetUsrChange
*
*	$EP Parametros
*		$P id - Id do usuario que vai logar no sistema
*
*	$ED Descrição da função
*		Troca o usuario corrente no sistema.
*
***********************************************************************/
void NetUsrChange (const char *id);

/***********************************************************************
*
*	$FC Funcao: NetSearch
*
*	$EP Parametros
*		$P isFriend - 1 para procurar dentre os amigos, 0 cc.
*		$p id - id da(s) pessoa(s) procuradas.
*
*
*	$ED Descrição da função
*		Realiza uma busca dentre os usuarios.
*
*	$FV Valor retornado
*		Lista de usuarios.
*
***********************************************************************/
const char* NetSearch (int isFriend, const char *id, const char *in,
		int minAge, int maxAge);
/* posivelmente adicionar uma string com regexp sobre o nome mais tarde */

const char* NetAddFriend (char *id);

const char* NetUnfriend (char *id);

const char* NetWrite (int destC, const char ** destV);
/* Contem codigo de input para editar a mensagem*/

const char* NetRead (int msgNumber);

const char* NetDelMsg (int msgNumber);

const char* NetWhoAmI ();

const char* NetMail ();

#endif /* NETMGR_ */

