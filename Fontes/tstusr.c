#include <stdio.h>
#include <string.h>

#include "usr.h"

#include "tst_espc.h"
#include "generico.h"
#include "lerparm.h"
enum {USRVSIZE = 10};
enum {BUFFSIZE = 10};


Usr* [USRVSIZE] vUsr;

static const char USRNEW        [] = "=UsrNew";
static const char USRDEL        [] = "=UsrDel";
static const char USRPRINT      [] = "=UsrPrint";
static const char USRMSGLIST    [] = "=UsrMsgList";
static const char USRMSGDELIVER [] = "=UsrMsgDeliver";
static const char USRMSGPRINT   [] = "=UsrMsgPrint";
static const char USRMSGDEL     [] = "=UsrMsgDel";

TST_tpCondRet TST_EfetuarComando( char * CmdTeste )
{
	if (! strcmp (CmdTeste , USRDEL) ){
		int argc = 0, i = 0;

		argc = LER_LerParametros ("i", &i);
		if (argc != 1 || i > USRVSIZE || i < 0)
			return TST_CondRetParm;
		UsrDel(vUsr[i]);
		return TST_CondRetOK;

	} else if (! strcmp (CmdTeste, USRPRINT)) {
		char buffer[BUFFSIZE];
		char expected[BUFFSIZE];
		char zero[BUFFSIZE];
		int i, tstret, usrret, usr, size = 0;

		argc = LER_LerParametros ("iis", usr , limit, expected);
		if (argc != 3 || usr > USRVSIZE || usr < 0 || limit > BUFFSIZE)
			return TST_CondRetParm;

		for (i=0; i < BUFFSIZE; i++)
			zero[i] = buffer[i]=0;
		usrret = UsrPrint(vUsr[i], buffer, limit);

		tstret |= TST_CompararBool ( 1 , ret > limit
				"UsrPrint disse que printou mais que limit"
				"bytes.");
		tstret |= TST_CompararString ( expected, buffer,
				"UsrPrint emitiu uma string incorreta.");
		tstret |= TST_CompararEspaco ( zeros , buffer + limit,
				"UsrPrint permitiu buffer overflow.");
		return (tstret) ? (TST_CondRetErro) : (TST_CondRetOK);
	}
        return TST_CondRetNaoConhec;
}
