#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "netmgr.h"
#include "usr.h"

const char *cmd_exit (int argc, const char *argv[]);
const char *cmd_login (int argc, const char *argv[]);

int uhandle_commands (void);
const char *ucmd_newUser (int argc, const char *argv[]);
const char *invalid_command (int argc, const char *argv[]);
const char *ucmd_error (int argc, const char *argv[]);
const char *ucmd_help (int argc, const char *argv[]);

int lhandle_commands (void);
const char *lcmd_error (int argc, const char *argv[]);
const char *lcmd_help (int argc, const char *argv[]);

struct cli_cmd_tuple unlogged_cmds[] = {
	{ "login", &cmd_login },
	{ "exit", &cmd_exit },
	{ "help", &ucmd_help },
	{ NULL, &ucmd_error },
};

struct cli_cmd_tuple logged_cmds[] = {
	{ "logoff", NULL },
	{ "exit", &cmd_exit },
	{ NULL, &lcmd_error },
};

char cmd_buff[1024];
char ans_buff[1024];
const char *ans_ptr = NULL;

int (*handle_commands) (void) = &uhandle_commands;

int main (int argc, char *argv[])
{
	cli_register_tuple (unlogged_cmds);
	while (handle_commands ())
		;
	printf ("\n");
	return 0;
}

const char *cmd_login (int argc, const char *argv[])
{
	/* TODO: checa se usuario existe, se sim, registra logged_cmds e
	 * troca handle_commands para lhandle_commands.
	 */
	return NULL;
}

const char *cmd_exit (int argc, const char *argv[])
{
	exit (0);
}

/* ------------------------------------------------------------------------- */
/* Unlogged Commands */
/* ------------------------------------------------------------------------- */

int uhandle_commands (void)
{
	while (1){
		printf ("please enter login: ");
		if (fgets (cmd_buff, sizeof (cmd_buff), stdin) == NULL)
			return 0;
		ans_ptr = cli_call (cmd_buff);
		if (ans_ptr != NULL)
			printf ("%s", ans_ptr);
	}
}

const char *ucmd_error (int argc, const char *argv[])
{
	sprintf (ans_buff, "invalid command '%s'\n",
			argv[0]);
	return ans_buff;
}

const char *ucmd_help (int argc, const char *argv[])
{
	printf ("lista de possiveis comandos:\n"
			"+ login <user_name>\n"
			"+ create_user <user_name>\n"
			"+ del_user <user_name>\n");
	return NULL;
}
/* ------------------------------------------------------------------------- */
/* Logged Commands */
/* ------------------------------------------------------------------------- */

int lhandle_commands (void)
{
	while (1){
		/* TODO: Imprime o nome do usuario com a funcao WhoAmI */
		printf ("<user_name> $ ");
		if (fgets (cmd_buff, sizeof (cmd_buff), stdin) == NULL)
			return 0;
		ans_ptr = cli_call (cmd_buff);
		if (ans_ptr != NULL)
			printf ("%s", ans_ptr);
	}
}

const char *lcmd_error (int argc, const char *argv[])
{
	sprintf (ans_buff, "invalid command '%s'\n", argv[0]);
	return ans_buff;
}

const char *lcmd_help (int argc, const char *argv[])
{
	printf ("lista de possiveis comandos:\n");
	return NULL;
}
