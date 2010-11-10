#include <stdlib.h>
#include <string.h>
#include "netmgr.h"
#include "graph.h"


static const char NEWUSEROK[  ] = "Novo usuario criado.\n";
static const char NEWUSERUSEDID[  ] = "ID escolhido ja' em uso.\n";
static const char NETDELMEOK[  ] = "Usuario excluido com sucesso.\n";

int IsAuthenticated = 0;

/* use essa funcao para acessar o ponteiro de grafo */
int NetIsAuthenticated()
{
	return IsAuthenticated;
}

pGraph getGraphInstance()
{
	static pGraph Net;
	if (Net) return Net;
	Net = GraphNew (UsrDel);
	return Net;
}

const char* NetNewUser (char *id)
{
	Usr* u;
	GraphNodesStart(getGraphInstance());
	u = GraphNodesGetNext (getGraphInstance());
	while (u){
		if(0 == strcmp(u->id,id))
			return NEWUSERUSEDID;
		u = GraphNodesGetNext (getGraphInstance());
	}
	u = UsrNew(id);
	GraphNewNode( getGraphInstance(), u);
	IsAutheticated = 1;
	return NEWUSEROK;
}

const char* NetDelMe()
{
	GraphDelNode (getGraphInstance());
	IsAutheticated = 0;
	return NETDELMEOK;
}

const char* NetEditMe()
{
	return NULL;
}

const char* NetAddFriend (char *id)
{
	return NULL;
}

const char* NetUnfriend (char *id)
{
	return NULL;
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

