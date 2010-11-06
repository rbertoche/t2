#include "netmgr.h"
#include "usr.h"
#include "msg.h"


static const char NEWUSROK[  ] = "Novo usuario criado.\n";

/* use essa funcao para acessar o ponteiro de grafo */
pGraph getGraphInstance()
{
	static pGraph Net; 
	if (Net) return Net;
	Net = GraphNew (UsrDel);
	return Net;
}
	
char* NetNewUser (char *id)
{
	pUsr u;
	u = UsrNew();
	GraphNewNode( getGraphInstance(), u)
	/* muda id do usuario com funcao do mod usr */
	return NEWUSROK	
}

char* NetDelMe()
{
}

char* NetEditMe()
{
}

char* NetAddFriend (char *id)
{
}

char* NetUnfriend (char *id)
{
}

char* NetWrite (int destC, char * destV)
{
}

char* NetRead (char * sender)
{
}

char* NetDelMsg (int msgNumber)
{
}

