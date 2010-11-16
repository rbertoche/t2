#include <stdio.h>
#include <string.h>

#include "usr.h"

#include "tst_espc.h"
#include "generico.h"
#include "lerparm.h"
enum {USRVSIZE = 10};
enum {BUFFSIZE = 100};


Usr*  vUsr[USRVSIZE];

static const char USRNEW        [] = "=UsrNew";
static const char USRDEL        [] = "=UsrDel";
static const char USRPRINT      [] = "=UsrPrint";
static const char USRMSGLIST    [] = "=UsrMsgList";
static const char USRMSGDELIVER [] = "=UsrMsgDeliver";
static const char USRMSGPRINT   [] = "=UsrMsgPrint";
static const char USRMSGDEL     [] = "=UsrMsgDel";

/*
		char buffer[BUFFSIZE];
		char expected[BUFFSIZE];
		char zero[BUFFSIZE];
		int argc, i, tstret, usrret, usr;

		argc = LER_LerParametros ("iis", usr , limit, expected);
		if (argc != 3 || usr > USRVSIZE || usr < 0 || limit > BUFFSIZE)
			return TST_CondRetParm;

 *  Essa macro impede triplicacao de um codigo complexo que sempre seria usado
 *  da mesma forma. Coloque no mesmo escopo algum codigo semelhante ao acima
 *  para declarar e ler variaveis.
 */
#define		__TestFWithBuffer__( _FuncCall_, _FuncString_) \
		for (i=0; i < BUFFSIZE; i++) \
			zeros[i] = buffer[i]=0; \
		usrret = _FuncCall_; \
\
		tstret |= TST_CompararString ( expected, buffer, \
				_FuncString_ " emitiu uma string incorreta.");\
		tstret |= TST_CompararBool ( 1 , usrret > limit, \
				_FuncString_ " disse que printou mais que " \
				"limit bytes."); \
		tstret |= TST_CompararInt ( strlen(buffer) , usrret, \
				_FuncString_ " disse que printou mais bytes " \
				"do que realmente printou"); \
		tstret |= TST_CompararEspaco ( zeros , \
				buffer + limit, BUFFSIZE-limit, \
				_FuncString_ " permitiu buffer overflow.");


TST_tpCondRet TST_EfetuarComando( char * CmdTeste )
{
	if (! strcmp (CmdTeste , USRDEL) ){
		int argc = 0, usr;

		argc = LER_LerParametros ("i", &usr);
		if (argc != 1 || usr > USRVSIZE || usr < 0)
			return TST_CondRetParm;
		UsrDel(vUsr[usr]);
		return TST_CondRetOK;

	} else if (! strcmp (CmdTeste, USRNEW)) {
		int age,interest, usr, argc = 0;
		char id[15];
		char name[50];
		argc = LER_LerParametros ("issii", &usr, id, name, &age, &interest);
		if (argc != 5 || usr > USRVSIZE || usr < 0)
			return TST_CondRetParm;
		vUsr[usr] = UsrNew( id );
		strcpy (vUsr[usr]->name, name);
		vUsr[usr]->age=age;
		vUsr[usr]->interest=interest;
		return TST_CondRetOK;


	} else if (! strcmp (CmdTeste, USRPRINT)) {
		char buffer[BUFFSIZE];
		char expected[BUFFSIZE];
		char zeros[BUFFSIZE];
		int i, argc, limit, tstret=0, usrret, usr;

		argc = LER_LerParametros ("iis", &usr , &limit, expected);
		if (argc != 3 || usr > USRVSIZE || usr < 0 || limit > BUFFSIZE)
			return TST_CondRetParm;

		__TestFWithBuffer__( UsrPrint(vUsr[usr], buffer, limit),
				"UsrPrint" )

		return (tstret) ? (TST_CondRetErro) : (TST_CondRetOK);


	} else if (! strcmp (CmdTeste, USRMSGLIST)) {

		char buffer[BUFFSIZE];
		char expected[BUFFSIZE];
		char zeros[BUFFSIZE];
		int argc, i,limit, tstret=0, usrret, usr;

		argc = LER_LerParametros ("iis", &usr , &limit, expected);
		if (argc != 3 || usr > USRVSIZE || usr < 0 || limit > BUFFSIZE)
			return TST_CondRetParm;

		__TestFWithBuffer__( UsrMsgList(vUsr[i], buffer, limit),
				"UsrMsgList")

		return (tstret) ? (TST_CondRetErro) : (TST_CondRetOK);

	} else if (! strcmp (CmdTeste, USRMSGPRINT)) {

		char buffer[BUFFSIZE];
		char expected[BUFFSIZE];
		char zeros[BUFFSIZE];
		int argc, i,limit, tstret=0, usrret, usr, msg;

		argc = LER_LerParametros("iiis", &usr , &msg, &limit, expected);
		if (argc != 4 || usr > USRVSIZE || usr < 0 || limit > BUFFSIZE)
			return TST_CondRetParm;

		__TestFWithBuffer__( UsrMsgPrint(vUsr[i], msg, buffer, limit),
				"UsrMsgPrint")

		return (tstret) ? (TST_CondRetErro) : (TST_CondRetOK);

	} else if (! strcmp (CmdTeste, USRMSGDELIVER)) {


		char msg[BUFFSIZE];
		int argc, usr;

		argc = LER_LerParametros ("is", &usr , msg);
		if (argc != 2 || usr > USRVSIZE || usr < 0)
			return TST_CondRetParm;

		TST_CompararInt( 0, UsrMsgDeliver( vUsr[usr], msg),
			"UsrMsgDeliver detectou falha.");
		return TST_CondRetOK;


	} else if (! strcmp (CmdTeste, USRMSGDEL)) {

		int argc, usr, msg;

		argc = LER_LerParametros ("ii", &usr , &msg);
		if (argc != 2 || usr > USRVSIZE || usr < 0 )
			return TST_CondRetParm;

		TST_CompararInt( 0, UsrMsgDel( vUsr[usr], msg ),
			"UsrMsgDel detectou falha.");
		return TST_CondRetOK;

	}
        return TST_CondRetNaoConhec;
}
