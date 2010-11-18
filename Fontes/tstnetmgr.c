#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*#include <stdlib.h>*/

#include "netmgr.h"
#include "usr.h"

#include "tst_espc.h"
#include "generico.h"
#include "lerparm.h"

enum {BUFFSIZE = 1000};

static const char NETISAUTHENTICATED[] = "=NetIsAuthenticated";
static const char NETNEWUSER        [] = "=NetNewUser";
static const char NETDELME          [] = "=NetDelMe";
static const char NETEDITME         [] = "=NetEditMe";
static const char NETUSRCHANGE      [] = "=NetUsrChange";
static const char NETSEARCH         [] = "=NetSearch";
static const char NETADDFRIEND      [] = "=NetAddFriend";
static const char NETUNFRIEND       [] = "=NetUnfriend";
static const char NETWRITE          [] = "=NetWrite";
static const char NETREAD           [] = "=NetRead";
static const char NETDELMSG         [] = "=NetDelMsg";
static const char NETMAIL           [] = "=NetMail";


TST_tpCondRet TST_EfetuarComando( char * CmdTeste )
{
	int argc;
	if (! strcmp (CmdTeste ,  NETISAUTHENTICATED) ){

		int logado, argc = LER_LerParametros ("i", &logado);
		if (argc != 1) return TST_CondRetParm;
		return TST_CompararInt (logado, NetIsAuthenticated(),
				"Erro de Autenticacao.");

	} else if (! strcmp (CmdTeste,NETNEWUSER  )) {

		char id[15];

		argc = LER_LerParametros ("s",
			&id);
		if (argc != 1) return TST_CondRetParm;
		return TST_CompararString ( "Novo usuario criado.\n",
			(char*) NetNewUser(id),
			"NetNewUser falhou.");

	} else if (! strcmp (CmdTeste,NETDELME    )) {

		argc = LER_LerParametros ("");
		if (argc != 0) return TST_CondRetParm;
		return TST_CompararString (
			"Usuario excluido com sucesso.\n",
			(char*)NetDelMe(),
			"NetDelMe falhou.");

	} else if (! strcmp (CmdTeste,NETEDITME   )) {

		char name[50]; char in[15]; int age;

		argc = LER_LerParametros ("ssi",
			name, in, &age);
		if (argc != 3) return TST_CondRetParm;
		return TST_CompararString (
			"Perfil salvo.\n",
			(char*)NetEditMe( name, in, age ),
			"NetEditMe nao salvou.");

	} else if (! strcmp (CmdTeste,NETUSRCHANGE)) {

		char id[15];

		argc = LER_LerParametros ("s",
			&id);
		if (argc != 1) return TST_CondRetParm;
		NetUsrChange(id);
		return TST_CondRetOK;



	} else if (! strcmp (CmdTeste,NETSEARCH   )) {

		char buffer[BUFFSIZE]; int isFriend;
		char id[15], in[15]; int minAge, maxAge;
		char expected[BUFFSIZE];

		argc = LER_LerParametros ("issiis",
			&isFriend, id, in, &minAge, &maxAge, expected);
		if (argc != 6) return TST_CondRetParm;
		return TST_CompararString (expected,(char*) NetSearch(
			buffer, BUFFSIZE, isFriend, (id[0])?id:NULL,
			(in[0])?in:NULL, minAge, maxAge),
			"NetSearch retornou uma string incorreta.");

	} else if (! strcmp (CmdTeste,NETADDFRIEND)) {

		char id[15];

		argc = LER_LerParametros ("s",
			&id);
		if (argc != 1) return TST_CondRetParm;
		return TST_CompararString ( "Amigo adicionado com sucesso.\n",
			(char*) NetAddFriend(id),
			"NetAddFriend falhou.");

	} else if (! strcmp (CmdTeste,NETUNFRIEND )) {

		char id[15];

		argc = LER_LerParametros ("s",
			&id);
		if (argc != 1) return TST_CondRetParm;
		return TST_CompararString ( "Amigo removido com sucesso.\n",
			(char*) NetUnfriend(id),
			"NetUnfriend falhou.");

	} else if (! strcmp (CmdTeste,NETWRITE    )) {

		char msg[BUFFSIZE];
		char id[15];
		const char *p=id;

		argc = LER_LerParametros ("ss",
			id, msg);
		if (argc != 2) return TST_CondRetParm;

		return TST_CompararString ("Mensagem enviada.\n",
			(char*)NetWrite(msg, 1, &p),
			"NetWrite nao enviou mensagem.");

	} else if (! strcmp (CmdTeste,NETREAD     )) {

		char expected[BUFFSIZE];
		int msg;

		argc = LER_LerParametros ("is",
			&msg, expected);
		if (argc != 2) return TST_CondRetParm;
		return TST_CompararString (expected,(char*) NetRead(
			msg),
			"NetRead retornou uma string incorreta.");

	} else if (! strcmp (CmdTeste,NETDELMSG   )) {

		int msg;

		argc = LER_LerParametros ("i",
			&msg);
		if (argc != 1) return TST_CondRetParm;
		return TST_CompararString ( "Mensagem deletada.\n",
			(char*) NetDelMsg(msg),
			"NetDelMsg falhou.");

	} else if (! strcmp (CmdTeste,NETMAIL  )) {

		char buffer[BUFFSIZE];
		char expected[BUFFSIZE];

		argc = LER_LerParametros ("s",
			expected);
		if (argc != 1) return TST_CondRetParm;
		return TST_CompararString (expected,(char*) NetMail(
			buffer, BUFFSIZE),
			"NetMail retornou uma string incorreta.");

	}
        return TST_CondRetNaoConhec;
}


