#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cli.h"
#include "netmgr.h"
#include "usr.h"

/* Buffer para armazenar as strings geradas dinamicamente ou coisas
 * grandes lidas de stdin */
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
const char *lcmd_editme (int argc, const char *argv[]);
const char *lcmd_delmsg (int argc, const char *argv[]);

struct cli_cmd_tuple unlogged_cmds[] = {
	{ "login", &ucmd_login },
	{ "exit", &cmd_exit },
	{ "register", &ucmd_register },
	{ "help", &ucmd_help },
	{ NULL, &ucmd_error },
};

struct cli_cmd_tuple logged_cmds[] = {
	{ "help", &lcmd_help },
	{ "delme", &lcmd_delme },
	{ "editme", &lcmd_editme },
	{ "read", &lcmd_read },
	{ "delmsg", &lcmd_delmsg },
	{ "write", &lcmd_write },
	{ "addfriend", &lcmd_addfriend },
	{ "search", &lcmd_search },
	{ "rmfriend", &lcmd_unfriend },
	{ "mail", &lcmd_mail },
	{ "logout", &lcmd_logoff },
	{ "exit", &cmd_exit },
	{ NULL, &lcmd_error },
};

static char cmd_buff[1024];
static int logged = 0;
static int ScriptMode = 0;
enum { BUFFSIZE = 10000 };
char buffer[BUFFSIZE];


int main (int argc, char *argv[])
{
	if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == 's')
		ScriptMode = 1;
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
	const char *ret;
	while (!feof(stdin)){
		if (!ScriptMode){
			if (logged){
				printf ("%s $ ", NetWhoAmI() );
			} else {
				printf ("admin $ ");
			}
		}
		cmd_buff[0] = '\0';
		fgets (cmd_buff, sizeof (cmd_buff), stdin);
		ret = cli_call (cmd_buff);
		if (ret)
			fprintf(stdout,"%s",ret);
	}
	return 0;
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
			"\t+ help\n"
			"\t+ exit\n"
			);
	return NULL;
}

const char *ucmd_login (int argc, const char *argv[])
{
	if (argc != 2){
		return ucmd_help (0, NULL);
	} else {
		NetUsrChange (argv[1]);
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
	printf ("lista de possiveis comandos:\n"
			"\t+ logout\n"
			"\t+ delme\n"
			"\t+ editme\n"
			"\t+ read <msg_id>\n"
			"\t+ write\n"
			"\t+ addfriend <user_id> [user_id ...]\n"
			"\t+ rmfriend <user_id> [user_id ...]\n"
			"\t+ search [-f] [-u id] [-i interest] "
				"[-a maxAge-minAge]\n"
			"\t+ mail\n"
			"\t+ exit\n"
			);
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

	int i;
	for (i=1; i < argc; i++){
		printf ("%s", NetAddFriend ((char*)argv[i]));
	}
	return NULL;
}

const char *lcmd_delme (int argc, const char *argv[])
{
	lcmd_logoff (0, NULL);
	return NetDelMe();
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
	int offset = 0;
	/* recebe o conteudo da mensagem de stdin */
	while (offset < BUFFSIZE-4)
	{
		buffer[offset++] = getchar();
		if ( buffer[offset-3] == '#' && (buffer[offset-2] == '#')
				&& buffer[offset-1] == '#')
					break;
	}
	buffer[offset-3] = '\0';
	clearerr(stdin);
	return NetWrite (buffer,argc-1, ++argv);
}

const char *lcmd_search (int argc, const char *argv[])
{
	int i, isFriend = 0, minAge = -1, maxAge = -1;
	const char *in = NULL, *id = NULL;

	for (i=1; i < argc; i++){
		if (argv[i][0] != '-'){
			printf("Erro: Argumento %d, %s"
				" nao e uma opcao valida\n",i,argv[i]);
			return NULL;
		}
		switch (argv[i][1]){
			case 'f':
				isFriend = 1;
				break;
			case 'u':
				id = argv[++i];
				break;
			case 'i':
				in = argv[++i];
				break;
			case 'a':
				sscanf(argv[++i],"%d:%d",&minAge,&maxAge);
				break;
			default:
				printf("Erro: Argumento %d, %s"
					" nao e uma opcao valida\n",i,argv[i]);
				return NULL;

		}
	}
	return NetSearch (buffer, BUFFSIZE, isFriend, id, in, minAge, maxAge);
}

const char *lcmd_mail (int argc, const char *argv[])
{
	return NetMail(buffer, BUFFSIZE);
}

const char *lcmd_editme (int argc, const char *argv[])
{
	char in[15], name[50], str[10];
	int age;
	*in = 0; *name = 0; age = -1;
	printf("Entre um novo nome ate 50 caracteres ou pressione enter\n");
	if (fgets(name,50,stdin) && ! isspace( *name )){
		str[strlen(name)-1]='\0';
	}
	printf("Entre um novo interesse ou pressione enter\n");
	if (fgets(in,50,stdin) && ! isspace( *in )){
		in[strlen(in)-1]='\0';
	}
	printf("Entre uma nova idade ou pressione enter\n");
	if (fgets(str,10,stdin) && ! isspace( *str )){
		sscanf(str,"%d\n",&age);
	}
	return NetEditMe(name,in,age);
}

const char *lcmd_delmsg (int argc, const char *argv[])
{
	int i=0, j=0;

	for (i=1; i<argc; i++){
		sscanf (argv[1], "%d", &j);
		printf ("%s", NetDelMsg (j));
	}
	return NULL;
}
