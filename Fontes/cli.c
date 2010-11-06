#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli.h"

const int MAXARGC=50;
const static struct cli_cmd_tuple *userCmds;

/* Tokenize the blank chars from the string.
 * Works like the argc, argv generator. */
static int clitok (char *s,const char **argv)
{
	int argc = 0;
	int i, n = strlen (s);
	int last_isspace;

	for (i=0, last_isspace=1; i<n; i++){
		if (isspace (s[i])){
			if (!last_isspace){
				last_isspace = 1;
				argc++;
			}
			s[i] = '\0';
		} else if (last_isspace){
			argv[argc] = s + i;
			last_isspace = 0;
		}
	}
	return argc;
}

/* transform a string in a argc, *argv[]. and call the function from the
 *  argv[0]. */
int cli_call (char *s)
{
	int i;
	const char *argv[MAXARGC];
	int argc = clitok(s,argv);

	for (i=0; userCmds[i].s; i++){
		int ret;
		if ( userCmds[i].s && strcmp (userCmds[i].s, argv[0]) == 0){
			ret = userCmds[i].cb (argc, argv);
			return ret;
		}
	}
	printf ("invalid command %s\n", argv[0]);
	return -1;
}

void cli_register_tuple (const struct cli_cmd_tuple *cmds)
{
	userCmds = cmds;
}
