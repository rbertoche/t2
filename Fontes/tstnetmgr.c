//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

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
static const char NETWHOAMI         [] = "=NetWhoAmI";
static const char NETNETMAIL        [] = "=NetNetMail";


TST_tpCondRet TST_EfetuarComando( char * CmdTeste )
{
	if (! strcmp (CmdTeste ,  NETISAUTHENTICATED) ){
		int logado, argc = LER_LerParametros ("i", &logado);
		if (argc != 1) return TST_CondRetParm;
		return TST_CompararInt (logado, NetIsAuthenticated(),
				"Erro de Autenticacao.");

	} else if (! strcmp (CmdTeste,NETNEWUSER  )) {
	} else if (! strcmp (CmdTeste,NETDELME    )) {
	} else if (! strcmp (CmdTeste,NETEDITME   )) {

		char name[50]; char in[15]; int age;

		argc = LER_LerParametros ("ssi",
			name, in, &age);
		if (argc != 3) return TST_CondRetParm;
		return TST_CompararString (
			"Perfil salvo.\n",
			NetSearch( name, id, age )
			"NetSearch nao salvou.");

	} else if (! strcmp (CmdTeste,NETUSRCHANGE)) {
	} else if (! strcmp (CmdTeste,NETSEARCH   )) {

		char buffer[BUFFSIZE]; int buffsize; int isFriend;
		char id[15], in[15]; int minAge, maxAge;
		char expected[BUFFSIZE]

		argc = LER_LerParametros ("issiis",
			&isFriend, id, in, &minAge, &maxAge, expected);
		if (argc != 6) return TST_CondRetParm;
		return TST_CompararString (expected, NetSearch(
			buffer, buffsize, isFriend, id, in, minAge, maxAge)
			"NetSearch retornou uma string incorreta.");

	} else if (! strcmp (CmdTeste,NETADDFRIEND)) {
	} else if (! strcmp (CmdTeste,NETUNFRIEND )) {
	} else if (! strcmp (CmdTeste,NETWRITE    )) {
	} else if (! strcmp (CmdTeste,NETREAD     )) {
	} else if (! strcmp (CmdTeste,NETDELMSG   )) {
	} else if (! strcmp (CmdTeste,NETWHOAMI   )) {
	} else if (! strcmp (CmdTeste,NETNETMAIL  )) {
	}
        return TST_CondRetNaoConhec;
}


