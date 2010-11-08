#include <stdlib.h>
#include "netmgr.h"
#include "graph.h"


static const char NEWUSROK[  ] = "Novo usuario criado.\n";

/* use essa funcao para acessar o ponteiro de grafo */
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
	u = UsrNew(id);
	GraphNewNode( getGraphInstance(), u);
	return NEWUSROK;
}

char* NetDelMe()
{
	return NULL;
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

