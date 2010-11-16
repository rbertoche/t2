#include <stdlib.h>
#include <string.h>
#include "netmgr.h"
#include "graph.h"

enum { BUFFERSIZE = 10000 };

static const char NEWUSER_OK[  ] = "Novo usuario criado.\n";
static const char NEWUSER_USEDID[  ] = "ID escolhido ja' em uso.\n";
static const char NETDELME_OK[  ] = "Usuario excluido com sucesso.\n";
static const char NETADDFRIEND_OK[  ] = "Amigo adicionado com sucesso.\n";
static const char NETADDFRIEND_NOTFOUND[  ] = "Usuario nao encontrado.\n";
static const char NETUNFRIEND_OK[  ] = "Amigo removido com sucesso.\n";
static const char NETUNFRIEND_NOTFOUND[  ] = "Amigo nao encontrado.\n";
static const char NETSEARCH_NOTFOUND[  ] = "Nenhum usuario casou com a busca.\n";
static const char NETDELMSG_OK[  ] = "Mensagem deletada.\n";
static const char NETDELMSG_NOTFOUND[  ] = "Numero de mensagem invalido.\n";


/* Atencao, cuidado ao deletar esse usr porque normalmente o grafo o deleta */
Usr *usr = NULL;

/* Buffer para armazenar as strings geradas a serem retornadas */
char buffer[BUFFERSIZE];
/* Indice para atual posicao no buffer */
int offset;

/* use essa funcao para acessar o ponteiro de grafo */
int NetIsAuthenticated()
{
	return usr?1:0;
}

pGraph getGraphInstance()
{
	static pGraph Net;
	if (Net) return Net;
	Net = GraphNew (UsrDel);
	return Net;
}

Usr *searchUsr(const char *id)
{
	Usr* u;
	GraphNodesStart(getGraphInstance());
	u = GraphNodesGetNext (getGraphInstance());
	while (u){
		if(0 == strcmp(u->id,id))
			return u;
		u = GraphNodesGetNext (getGraphInstance());
	}
	return NULL;
}

void switchUsr(const char *id)
{
	usr = searchUsr(id);
}

Usr *searchLink(const char *id)
{
	Usr *u;
	GraphLinksStart(getGraphInstance());
	u = GraphLinksGetNext (getGraphInstance());
	while (u){
		if(0 == strcmp(u->id,id))
			return u;
		u = GraphLinksGetNext (getGraphInstance());
	}
	return NULL;
}

const char* NetNewUser (const char *id)
{
	if(searchUsr(id))
		return NEWUSER_USEDID;
	usr = UsrNew(id);
	GraphNewNode( getGraphInstance(), usr);
	return NEWUSER_OK;
}

const char* NetDelMe()
{
	GraphDelNode (getGraphInstance());
	usr = NULL;
	return NETDELME_OK;
}

const char* NetEditMe()
{
	return NULL;
}

const char* NetAddFriend (char *id)
{
	Usr *u;
	u = searchUsr(id);
	if (!u)
		return NETADDFRIEND_NOTFOUND;
	GraphAddLink(getGraphInstance(),u);
	return NETADDFRIEND_OK;
}

const char* NetUnfriend (char *id)
{
	Usr *u;
	u = searchLink(id);
	if (!u)
		return NETUNFRIEND_NOTFOUND;
	GraphRemLink(getGraphInstance(),u);
	return NETUNFRIEND_OK;
}

const char* NetWrite (int destC, char * destV)
{
	return NULL;
}

const char* NetSearch (		int isFriend,
				char *id,
				enum interest in,
				int minAge,
				int maxAge)
{
	int fid=0, fin=0, fage=0;
	Usr *u;
	void *(*pFuncGetNext)(pGraph);
	/* Ponteiro para funcao que contera' um getnext */

	offset=0;
	if (!id)
		fid=1;
	if (fin == INVALID)
		fin=1;
	if (-1 == minAge && minAge == maxAge);
		fage=1;


	if (isFriend){
		GraphLinksStart(getGraphInstance());
		u = GraphLinksGetNext (getGraphInstance());
		pFuncGetNext = GraphLinksGetNext;
	} else {
		GraphNodesStart(getGraphInstance());
		u = GraphNodesGetNext (getGraphInstance());
		pFuncGetNext = GraphNodesGetNext;
	}

	for(; u ; u = (*pFuncGetNext)(getGraphInstance()) )
	{
		if (		(fid || strcmp(u->id,id) )
				&& (fin || u->interest == in)
				&& (fage || (u->age >= minAge
					&& u->age <= maxAge)) )
		{
			offset += UsrPrint(u,buffer + offset,
					 BUFFERSIZE - offset);
		}
	}
	if (offset==0)
		return NETSEARCH_NOTFOUND;
	else
		return buffer;
}

const char* NetMail ()
{
	offset = 0;
	offset += UsrMsgList(usr,buffer,offset);
	return buffer;
}

const char* NetRead (int msgNumber)
{
	offset = 0;
	offset += UsrMsgPrint(usr,msgNumber,buffer,offset);
	return buffer;
}

const char* NetDelMsg (int msgNumber)
{
	if (!UsrDelMsg(usr, msgNumber))
		return NETDELMSG_OK;
	return NETDELMSG_NOTFOUND;
}

const char* NetWhoAmI (void)
{
	return usr->id;
}
