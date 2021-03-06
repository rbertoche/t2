#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "netmgr.h"
#include "graph.h"


static const char NEWUSER_OK[  ] = "Novo usuario criado.\n";
static const char NEWUSER_USEDID[  ] = "ID escolhido ja' em uso.\n";
static const char NEWUSER_INVALID[  ] = "ID contem caracteres invalidos.\n";
static const char NETDELME_OK[  ] = "Usuario excluido com sucesso.\n";
static const char NETADDFRIEND_OK[  ] = "Amigo adicionado com sucesso.\n";
static const char NETADDFRIEND_NOTFOUND[  ] = "Usuario nao encontrado.\n";
static const char NETADDFRIEND_INVALID[  ] = "Usuario ja e seu amigo.\n";
static const char NETUNFRIEND_OK[  ] = "Amigo removido com sucesso.\n";
static const char NETUNFRIEND_NOTFOUND[  ] = "Amigo nao encontrado.\n";
static const char NETSEARCH_NOTFOUND[ ] = "Nenhum usuario casou com a busca.\n";
static const char NETDELMSG_OK[  ] = "Mensagem deletada.\n";
static const char NETDELMSG_NOTFOUND[  ] = "Numero de mensagem invalido.\n";
static const char NETWRITE_MEMERROR[  ] = "Erro: Nao pude alocar memoria.\n";
static const char NETWRITE_DELIVERERROR[  ] =
		"Erro: Funcao de entrega do modulo usr falhou.\n";
static const char NETWRITE_OK[  ] = "Mensagem enviada.\n";
static const char NETEDITME_OK[  ] = "Perfil salvo.\n";
static const char NETEDITME_NOCHANGES[  ] = "Sem mudancas..\n";



static const char ARGNUMERROR[  ] =
		"Numero de argumentos menor que o esperado.\n";


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
	Net = GRA_New (UsrDel);
	return Net;
}

Usr *searchUsr(const char *id)
{
	Usr* u;
	GRA_NodesStart(getGraphInstance());
	u = GRA_NodesGetNext (getGraphInstance());
	while (u){
		if(0 == strcmp(u->id,id))
			return u;
		u = GRA_NodesGetNext (getGraphInstance());
	}
	return NULL;
}

void NetUsrChange(const char *id)
{
	usr = searchUsr(id);
}

Usr *searchLink(const char *id)
{
	Usr *u;
	GRA_LinksStart(getGraphInstance());
	u = GRA_LinksGetNext (getGraphInstance());
	while (u){
		if(0 == strcmp(u->id,id))
			return u;
		u = GRA_LinksGetNext (getGraphInstance());
	}
	return NULL;
}

const char* NetNewUser (const char *id)
{
	if(searchUsr(id))
		return NEWUSER_USEDID;
	if(strchr(id,':'))
		return NEWUSER_INVALID;
	usr = UsrNew(id);
	GRA_NewNode( getGraphInstance(), usr);
	return NEWUSER_OK;
}

const char* NetDelMe()
{
	GRA_DelNode (getGraphInstance());
	usr = NULL;
	return NETDELME_OK;
}

const char* NetAddFriend (char *id)
{
	Usr *u;
	u = searchUsr(id);
	if (!u)
		return NETADDFRIEND_NOTFOUND;
	if (GRA_Ok == GRA_AddLink(getGraphInstance(),u))
		return NETADDFRIEND_OK;
	return NETADDFRIEND_INVALID;
}

const char* NetUnfriend (char *id)
{
	Usr *u;
	u = searchLink(id);
	if (!u)
		return NETUNFRIEND_NOTFOUND;
	GRA_RemLink(getGraphInstance(),u);
	return NETUNFRIEND_OK;
}

const char* NetWrite (char * buffer, int destC, const char * destV[])
{
	Msg msg;
	int i,size;
	char *msgptr;
	int offset = 0;

	/* testa se ha algum destinatario */
	if (destC == 0)
		return ARGNUMERROR;
	/* testa se os usuarios sao validos */
	for (i=0; i<destC; i++)
		if (!searchUsr(destV[i]))
			offset += sprintf(&buffer[offset],
				"%s nao e' um username valido\n",destV[i]);
	if (offset)
		return buffer;

	/* calcula o tamanho a alocar para armazenar a mensagem codificada */
	size = 0;
	size += strlen( usr->id );
	size+=2; /* ':' */
	for (i=0; i<destC; i++){
		size += strlen( destV[i] );
		size+=2; /* ':' */
	}
	size+=2; /* ':' */
	size += strlen( buffer );

	/* Aloca uma mensagem */
	msg = malloc( sizeof(char) * size );
	if (!msg)
		return NETWRITE_MEMERROR;
	msgptr = msg;

	/* Escreve a mensagem codificada */
	strcpy( msgptr, usr->id );
	msgptr += strlen( usr->id );
	*(msgptr++) = ':';
	for (i=0; i<destC; i++){
		strcpy( msgptr, destV[i] );
		msgptr += strlen( destV[i] );
		*(msgptr++) = ':';
	}
	*(msgptr++) = ':';
	strcpy(msgptr,buffer);

	/* Entrega copias das mensagens pra todos os destinatarios
	 * Atencao: faco o destV[0] separado porque ja tenho uma
	 * msg alocada */
	if (UsrMsgDeliver( searchUsr( destV[0] ), msg))
		return NETWRITE_DELIVERERROR;
	for (i=1; i < destC; i++){
		Msg msgCopy;
		msgCopy = malloc( sizeof(char) * size );
		memcpy( msgCopy, msg, size );
		if (UsrMsgDeliver( searchUsr( destV[i] ), msgCopy))
			return NETWRITE_DELIVERERROR;
	}
	return NETWRITE_OK;
}

const char* NetSearch (		char *buffer,
				int buffsize,
				int isFriend,
				const char *id,
				const char *in,
				int minAge,
				int maxAge)
{
	int fid=0, fin=0, fage=0;
	Usr *u;
	void *(*pFuncGetNext)(pGraph);
	/* Ponteiro para funcao que contera' um getnext */

	int offset=0;
	*buffer = 0;
	if (!id)
		fid=1;
	if (!in)
		fin=1;
	if ((-1 == minAge) && (-1 == maxAge))
		fage=1;

	if (isFriend){
		GRA_LinksStart(getGraphInstance());
		u = GRA_LinksGetNext (getGraphInstance());
		pFuncGetNext = GRA_LinksGetNext;
	} else {
		GRA_NodesStart(getGraphInstance());
		u = GRA_NodesGetNext (getGraphInstance());
		pFuncGetNext = GRA_NodesGetNext;
	}

	for(; u ; u = (*pFuncGetNext)(getGraphInstance()) )
	{
		if (		(fid || !strcmp(u->id,id) )
				&& (fin || u->interest == UsrStrToIn(in))
				&& (fage || (u->age >= minAge
					&& u->age <= maxAge)) )
		{
			offset += UsrPrint(u,buffer + offset,
					 buffsize - offset);
		}
	}
	if (offset==0)
		return NETSEARCH_NOTFOUND;
	else
		return buffer;
}

const char* NetMail (char *buffer, int buffsize)
{
	if (!UsrMsgList(usr, buffer, buffsize))
		return "Lista de mensagens vazia\n";
	return buffer;
}

const char* NetRead ( int msgNumber)
{
	return UsrMsgPrint(usr,msgNumber);
}

const char* NetDelMsg (int msgNumber)
{
	if (!UsrMsgDel(usr, msgNumber))
		return NETDELMSG_OK;
	return NETDELMSG_NOTFOUND;
}

const char* NetWhoAmI (void)
{
	return usr->id;
}

const char* NetEditMe (const char* name, const char *in, int age)
{
	if (*name){
		strcpy(usr->name,name);
	}
	if (*in){
		usr->interest = UsrStrToIn(in);
	}
	if (age > 0){
		usr->age = age;
	}
	if (*name!='\n' || *in!='\n' || age > 0)
		return NETEDITME_OK;
	return NETEDITME_NOCHANGES;
}
