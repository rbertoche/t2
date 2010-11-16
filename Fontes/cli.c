#include <string.h>
#include <ctype.h>

#include "cli.h"

#define MAXARGC 50
const static struct cli_cmd_tuple *userCmds;

/* Tokenize the blank chars from the string.
 * Works like the argc, argv generator. */
static int clitok (char *s,const char **argv)
{
	int argc = 0;
	int i, n = strlen (s);
	int last_isspace;
	int instring = 0;

	argv[0] = NULL;
	for (i=0, last_isspace=1; i<n+1; i++){
		if (s[i] == '"' && instring){
			instring = 0;
		}else if (s[i] == '"' && !instring){
			instring = 1;
			continue;
		}
		if (!instring && (isspace (s[i]) || s[i] == '\0' || s[i] == '"')){
			if (!last_isspace){
				if (argc >= MAXARGC) return -1;
				last_isspace = 1;
				argc++;
			}
			s[i] = '\0';
		}else if (last_isspace){
			argv[argc] = s + i;
			last_isspace = 0;
		}
	}
	return argc;
}

/* transform a string in a argc, *argv[]. and call the function from the
 *  argv[0]. If function not found, try to run the "error" errorfn function at
 *  the last  entry of the table, { NULL, errorfn }, If errorfn doesn't exist
 *  return NULL. */
const char *cli_call (char *s)
{
	int i;
	const char *argv[MAXARGC];
	int argc = clitok(s,argv);

	if (argc == 0) return NULL;
	if (argv[0][0] == '#') return NULL;
	for (	i=0;
			userCmds[i].s
			&& argv[0]
			&& (strcmp (userCmds[i].s, argv[0]) != 0);
		i++ ){}

	if (userCmds[i].cb == NULL)
		return NULL;
	return userCmds[i].cb (argc, argv);
}

void cli_register_tuple (const struct cli_cmd_tuple *cmds)
{
	userCmds = cmds;
}
