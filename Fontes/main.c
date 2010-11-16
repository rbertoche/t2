#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "netmgr.h"
#include "usr.h"

int handle_commands (void);
const char *cmd_exit (int argc, const char *argv[]);

const char *ucmd_newUser (int argc, const char *argv[]);
const char *invalid_command (int argc, const char *argv[]);
const char *ucmd_error (int argc, const char *argv[]);
const char *ucmd_help (int argc, const char *argv[]);
const char *ucmd_register (int argc, const char *argv[]);
const char *ucmd_login (int argc, const char *argv[]);
const char *ucmd_didyou_mean (int argc, const char *argv[]);

const char *lcmd_error (int argc, const char *argv[]);
const char *lcmd_help (int argc, const char *argv[]);
const char *lcmd_logoff (int argc, const char *argv[]);
const char *lcmd_addfriend (int argc, const char *argv[]);
const char *lcmd_search (int argc, const char *argv[]);
const char *lcmd_delme (int argc, const char *argv[]);
const char *lcmd_rmfriend (int argc, const char *argv[]);

struct cli_cmd_tuple unlogged_cmds[] = {
	{ "login", &ucmd_login },
	{ "exit", &cmd_exit },
	{ "register", &ucmd_register },
	{ "help", &ucmd_help },
	{ NULL, &ucmd_error },
};

struct cli_cmd_tuple logged_cmds[] = {
	{ "logout", &lcmd_logoff },
	{ "delme", &lcmd_delme },
	{ "addfriend", &lcmd_addfriend },
	{ "rmfriend", &lcmd_rmfriend },
	{ "search", &lcmd_search },
	{ "exit", &cmd_exit },
	{ NULL, &lcmd_error },
};

char cmd_buff[1024];
char ans_buff[1024];
const char *ans_ptr = NULL;
int logged = 0;

int main (int argc, char *argv[])
{
	cli_register_tuple (unlogged_cmds);
	while (handle_commands ())
		;
	printf ("\n");
	return 0;
}

const char *cmd_exit (int argc, const char *argv[])
{
	exit (0);
}

int handle_commands (void)
{
	while (1){
		if (logged){
			printf ("%s $ ", NetWhoAmI() );
		} else {
			printf ("admin $ ");
		}
		cmd_buff[0] = '\0';
		fgets (cmd_buff, sizeof (cmd_buff), stdin);
		switch (cmd_buff[0]){
		case '\0':
			printf ("\n");
		case '\n':
			continue;
		default: break;
		}
		ans_ptr = cli_call (cmd_buff);
		if (ans_ptr != NULL)
			printf ("%s", ans_ptr);
		ans_ptr = NULL;
	}
}

/* ------------------------------------------------------------------------- */
/* Unloged Commands */
/* ------------------------------------------------------------------------- */

const char *ucmd_register (int argc, const char *argv[])
{
	if (argc != 2){
		return ucmd_help (0, NULL);
	}
	return NetNewUser (argv[1]);
}

const char *ucmd_error (int argc, const char *argv[])
{
	sprintf (ans_buff, "invalid command '%s'\n",
			argv[0]);
	return ans_buff;
}

const char *ucmd_help (int argc, const char *argv[])
{
	printf ("lista de comandos:\n"
			"\t+ login <user_name>\n"
			"\t+ register <user_name>\n"
			);
	return NULL;
}

const char *ucmd_login (int argc, const char *argv[])
{
	if (argc != 2){
		return ucmd_help (0, NULL);
	} else {
		switchUsr (argv[1]);
		if (NetIsAuthenticated()){
			logged = 1;
			cli_register_tuple (logged_cmds);
		} else {
			sprintf (ans_buff, "login as '%s' failed\n", argv[1]);
		}
	}
	return ans_buff;
}

/* ------------------------------------------------------------------------- */
/* Logged Commands */
/* ------------------------------------------------------------------------- */

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

const char *lcmd_logoff (int argc, const char *argv[])
{
	logged = 0;
	cli_register_tuple (unlogged_cmds);
	sprintf (ans_buff, "bye %s\n", NetWhoAmI());
	return ans_buff;
}

const char *lcmd_addfriend (int argc, const char *argv[])
{
	if (argc != 2){
		sprintf (ans_buff, "syntax is %s user_id\n", argv[0]);
	}
	return NetAddFriend ((char*)argv[1]);
}

const char *lcmd_search (int argc, const char *argv[])
{
	return NULL;
}

const char *lcmd_delme (int argc, const char *argv[])
{
	lcmd_logoff (0, NULL);
	return NetDelMe();
}

const char *lcmd_unfriend (int argc, const char *argv[])
{
	if (argc != 2){
		sprintf (ans_buff, "syntax is %s user_id\n", argv[0]);
	}
	return NetUnfriend ((char*)argv[1]);
}
