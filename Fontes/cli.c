#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int MAXARGC=50;
const int LINEBUFFSIZE=50;

typedef int (*fncallback) (int argc, const char *argv[]);

struct cli_cmd_tuple {
	char *s;
	fncallback cb;
};

int debug (int argc, const char *argv[])
{
	int i;
	for (i=0; i<argc; i++)
		printf ("%d-%s\n", i, argv[i]);
	return 0;
}

struct cli_tuple cli[] = {
	{ "print", &debug },
	{ NULL, NULL },
};

/* Tokenize the blank chars from the string.
 * Works like the argc, argv generator. */
int clitok (char *s,const char **argv)
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
int clicall (char *s)
{
	int i;
	const char *argv[MAXARGC];
	int argc = clitok(s,argv);

	for (i=0; cmds[i].s; i++){
		int ret;
		if (strcmp (cmds[i].s, argv[0]) == 0){
			ret = cmds[i].cb (argc, argv);
			return ret;
		}
	}
	printf ("invalid command %s\n", argv[0]);
	return -1;
}

int main (int argc, char *argv[])
{
	char buff[LINEBUFFSIZE];
	fgets (buff, LINEBUFFSIZE, stdin);
	clicall (buff);
	return 0;
}
