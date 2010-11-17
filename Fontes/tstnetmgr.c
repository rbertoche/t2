#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	} else if (! strcmp (CmdTeste,NETNEWUSER  )) {
	} else if (! strcmp (CmdTeste,NETDELME    )) {
	} else if (! strcmp (CmdTeste,NETEDITME   )) {
	} else if (! strcmp (CmdTeste,NETUSRCHANGE)) {
	} else if (! strcmp (CmdTeste,NETSEARCH   )) {
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


