#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "netmgr.h"
#include "usr.h"

int handle_commands (void);

const char *cmd_exit (int argc, const char *argv[]);

const char *ucmd_newUser (int argc, const char *argv[]);
const char *ucmd_error (int argc, const char *argv[]);
const char *ucmd_help (int argc, const char *argv[]);
const char *ucmd_register (int argc, const char *argv[]);
const char *ucmd_login (int argc, const char *argv[]);

const char *lcmd_error (int argc, const char *argv[]);
const char *lcmd_help (int argc, const char *argv[]);
const char *lcmd_logoff (int argc, const char *argv[]);
const char *lcmd_addfriend (int argc, const char *argv[]);
const char *lcmd_delme (int argc, const char *argv[]);
const char *lcmd_unfriend (int argc, const char *argv[]);
const char *lcmd_write (int argc, const char *argv[]);
const char *lcmd_read (int argc, const char *argv[]);
const char *lcmd_search (int argc, const char *argv[]);
const char *lcmd_mail (int argc, const char *argv[]);

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
	{ "read", &lcmd_read },
	{ "write", &lcmd_write },
	{ "addfriend", &lcmd_addfriend },
	{ "search", &lcmd_search },
	{ "rmfriend", &lcmd_unfriend },
	{ "mail", &lcmd_mail },
	{ "exit", &cmd_exit },
	{ NULL, &lcmd_error },
};

static char cmd_buff[1024];
static int logged = 0;

int main (int argc, char *argv[])
{
	cli_register_tuple (unlogged_cmds);
	ucmd_help (0, NULL);
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
		cli_call (cmd_buff);
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
	printf ("%s", NetNewUser (argv[1]));
	return NULL;
}

const char *ucmd_error (int argc, const char *argv[])
{
	printf ("invalid command '%s'\n", argv[0]);
	return NULL;
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
			printf ("login as '%s' failed\n", argv[1]);
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------- */
/* Logged Commands */
/* ------------------------------------------------------------------------- */

const char *lcmd_error (int argc, const char *argv[])
{
	printf ("invalid command '%s'\n", argv[0]);
	return NULL;
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
	printf ("bye %s\n", NetWhoAmI());
	return NULL;
}

const char *lcmd_addfriend (int argc, const char *argv[])
{
	if (argc != 2){
		printf ("syntax is %s user_id\n", argv[0]);
	}
	printf ("%s", NetAddFriend ((char*)argv[1]));
	return NULL;
}

const char *lcmd_delme (int argc, const char *argv[])
{
	lcmd_logoff (0, NULL);
	printf ("%s", NetDelMe());
	return NULL;
}

const char *lcmd_unfriend (int argc, const char *argv[])
{
	int i;
	for (i=1; i < argc; i++){
		printf ("%s", NetUnfriend ((char*)argv[i]));
	}
	return NULL;
}

const char *lcmd_read (int argc, const char *argv[])
{
	int i;
	for (i=1; i < argc; i++){
		int k;
		sscanf (argv[i], "%d", &k);
		printf("%s", NetRead (k));
	}
	return NULL;
}

const char *lcmd_write (int argc, const char *argv[])
{
	printf("%s", NetWrite (argc-1, ++argv));
	return NULL;
}

const char *lcmd_search (int argc, const char *argv[])
{
	int isFriend = 0, minAge = 0, maxAge = 0x7FFFFF;
	const char *id = NULL;
	int in;

	if (argc != 5){
		printf ("%s\n"
				"isFriend\n"
				"interest\n"
				"minAge\n"
				"maxAge\n",
				argv[0]
		       );
		return NULL;
	}
	sscanf (argv[1], "%d", &isFriend);
	id = argv[2];
	sscanf (argv[3], "%d", &in);
	sscanf (argv[4], "%d", &minAge);
	sscanf (argv[5], "%d", &maxAge);
	printf ("%s", NetSearch (isFriend, id, in, minAge, maxAge));
	return NULL;
}

const char *lcmd_mail (int argc, const char *argv[])
{
	printf ("%s", NetMail ());
	return NULL;
}
