#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "cli.h"
#include "tst_espc.h"

#include "generico.h"
#include "lerparm.h"

static const char REGISTER_TABLE [] = "=RegistraTabela";
static const char CHAMA_FUNCAO [] = "=ChamaFuncao";

static char cli_buffer[256];
static const char *cmd_soma (int argc, const char *argv[]);
static const char *cmd_concatena (int argc, const char *argv[]);
static const char *cmd_echo (int argc, const char *argv[]);
static const char *cmd_erro (int argc, const char *argv[]);

const struct cli_cmd_tuple teste1[] = {
	{ "soma", &cmd_soma },
	{ "concat", &cmd_concatena },
	{ NULL, &cmd_erro },
};

const struct cli_cmd_tuple teste2[] = {
	{ "echo_first_arg", &cmd_echo },
	{ NULL, NULL },
};

TST_tpCondRet TST_EfetuarComando( char * CmdTeste )
{
	if (! strcmp (CmdTeste , REGISTER_TABLE)){
		int argc = 0, i = 0;
		const struct cli_cmd_tuple *pcli = NULL;

		argc = LER_LerParametros ("i", &i);
		if (argc != 1)
			return TST_CondRetParm;

		if (i == 0){
			pcli = teste1;
		}else if (i == 1){
			pcli = teste2;
		}else return TST_CondRetErro;

		cli_register_tuple (pcli);
		return TST_CondRetOK;

	} else if (! strcmp (CmdTeste, CHAMA_FUNCAO)) {
		int argc;
		char s[256];
		char ret[256];
		const char *cliret = NULL;

		argc = LER_LerParametros ("ss", s, ret);
		if (argc != 2) return TST_CondRetParm;

		cliret = cli_call (s);
		return TST_CompararString (ret, (char*)cliret,
				"string missmatch,");
	}
        return TST_CondRetNaoConhec;
}

const char *cmd_soma (int argc, const char *argv[])
{
	int i = 0, j = 0;

	if (argc == 1){
		cli_buffer[0] = '\0';
		return cli_buffer;
	}
	
	for (i=1; i < argc; i++){
		int k = 0;
		sscanf (argv[i], " %d", &k);
		j += k;
	}
	sprintf (cli_buffer, "%d", j);
	return cli_buffer;
}

const char *cmd_concatena (int argc, const char *argv[])
{
	int i;
	char *ps = cli_buffer;
	for (i=1; i < argc; i++){
		int j = strlen (argv[i]);
		strcpy (ps, argv[i]);
		ps += j;
	}
	return cli_buffer;
}

const char *cmd_echo (int argc, const char *argv[])
{
	strcpy (cli_buffer, argv[1]);
	return cli_buffer;
}

const char *cmd_erro (int argc, const char *argv[])
{
	strcpy (cli_buffer, "invalid function");
	return cli_buffer;
}
