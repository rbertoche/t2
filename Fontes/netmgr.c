#include <stdlib.h>
#include <string.h>
#include "netmgr.h"
#include "graph.h"


static const char NEWUSER_OK[  ] = "Novo usuario criado.\n";
static const char NEWUSER_USEDID[  ] = "ID escolhido ja' em uso.\n";
static const char NETDELME_OK[  ] = "Usuario excluido com sucesso.\n";
static const char NETADDFRIEND_OK[  ] = "Amigo adicionado com sucesso.\n";
static const char NETADDFRIEND_NOTFOUND[  ] = "Usuario nao encontrado.\n";
static const char NETUNFRIEND_OK[  ] = "Amigo removido com sucesso.\n";
static const char NETUNFRIEND_NOTFOUND[  ] = "Amigo nao encontrado.\n";

/* Atencao, cuidado ao deletar esse usr porque normalmente o grafo o deleta */
Usr *usr = NULL;

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

Usr *searchUsr(char *id)
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

Usr *searchLink(char *id)
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

const char* NetNewUser (char *id)
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

const char* NetSearch (int isFriend, char *id, enum interest in, int minAge, int maxAge)
{
	return NULL;
}

const char* NetRead (char * sender)
{
	return NULL;
}

const char* NetDelMsg (int msgNumber)
{
	return NULL;
}

