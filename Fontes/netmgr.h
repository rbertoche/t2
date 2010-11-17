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
*	$ED Descricao da funcao
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
*	$ED Descricao da funcao
*		Cria usuario 'id' caso nao exista usuario com 'id'.
*
*	$FV Valor retornado
*		"ID escolhido ja' em uso.\n"
*		"ID contem caracteres invalidos.\n" caso id contenha ":"
*		"Novo usuario criado.\n"
*
***********************************************************************/
const char* NetNewUser (const char *id);

/***********************************************************************
*
*	$FC Funcao: NetDelMe
*
*	$ED Descricao da funcao
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
*	$ED Descricao da funcao
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
*	$ED Descricao da funcao
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
*	$ED Descricao da funcao
*		Realiza uma busca dentre os usuarios.
*
*	$FV Valor retornado
*		Lista de usuarios.
*
***********************************************************************/
const char* NetSearch (int isFriend, const char *id, const char *in,
		int minAge, int maxAge);

/***********************************************************************
*
*	$FC Funcao: NetAddFriend
*
*	$EP Parametros
*		$p id - id da pessoa a ser adicionada.
*
*
*	$ED Descricao da funcao
*		Caso o usuario 'id' eixsta, adiciona-o a lista de amigos do
*	usuario corrente.
*
*	$FV Valor retornado
*		"Amigo adicionado com sucesso.\n"
*		"Usuario nao encontrado.\n"
*
***********************************************************************/
const char* NetAddFriend (char *id);

/***********************************************************************
*
*	$FC Funcao: NetUnFriend
*
*	$EP Parametros
*		$p id - id da pessoa a ser removida.
*
*
*	$ED Descricao da funcao
*		Remove amigo da lista de amigos.
*
*	$FV Valor retornado
*		"Amigo removido com sucesso.\n"
*		"Amigo nao encontrado.\n"
*
***********************************************************************/
const char* NetUnfriend (char *id);


const char* NetWrite (int destC, const char ** destV);

/***********************************************************************
*
*	$FC Funcao: NetRead
*
*	$EP Parametros
*		$p id - id da mensagem a ser lida.
*
*
*	$ED Descricao da funcao
*		Exibe a mensagem na tela ou indica falha.
*
*	$FV Valor retornado
*		"Numero de mensagem invalido.\n"
*		ou string contendo a mensagem.
*
***********************************************************************/
const char* NetRead (int msgNumber);

/***********************************************************************
*
*	$FC Funcao: NetDelMsg
*
*	$EP Parametros
*		$p msgNumber - Numero da mensagem a ser deletada.
*
*
*	$ED Descricao da funcao
*		Remove uma mensagem da lista de mensagens do usuario.
*
*	$FV Valor retornado
*		"Numero de mensagem invalido.\n"
*		"Mensagem deletada.\n"
*
***********************************************************************/
const char* NetDelMsg (int msgNumber);

/***********************************************************************
*
*	$FC Funcao: NetWhoAmI
*
*	$ED Descricao da funcao
*		Imprime 'id' do usuario corrente
*
*	$FV Valor retornado
*		String terminada em '\0' com o id do usuario.
*
***********************************************************************/
const char* NetWhoAmI ();

/***********************************************************************
*
*	$FC Funcao: NetMail
*
*	$ED Descricao da funcao
*		Retorna as mensagens recebidas com uma formatacao mais amigavel.
*		Com: "From:", "To:", id da mensagem e a mensagem.
*
*	$FV Valor retornado
*		String terminada em '\0'.
*
***********************************************************************/
const char* NetMail ();

#endif /* NETMGR_ */

