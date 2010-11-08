#include <stdlib.h>
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
	pUsr u;
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

char* NetDelMe()
{
	LIS_DestruirLista(
		((pUsr) GraphGetData (pGraph g))->msgs );
	GraphDelNode (getGraphInstance());
	IsAutheticated = 0;
	return NETDELMEOK;
}

char* NetEditMe()
{
	return NULL;
}

char* NetAddFriend (char *id)
{
	return NULL;
}

char* NetUnfriend (char *id)
{
	return NULL;
}

char* NetWrite (int destC, char * destV)
{
	return NULL;
}

char* NetRead (char * sender)
{
	return NULL;
}

char* NetDelMsg (int msgNumber)
{
	return NULL;
}

