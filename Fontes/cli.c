#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int (*fncallback) (int argc, const char *argv[]);

struct cli_tuple {
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

/* Tolkenize the blank chars from the string.
 * Works like the argc, argv generator. */
int clitok (char *s)
{
	int argc = 0;
	int i, n = strlen (s);
	int state; /* 0 for blank, 1 for else. */

	for (i=0, state=0; i<n; i++){
		if (isspace (s[i])){
			if (state != 0){
				state = 0;
				argc++;
			}
			s[i] = '\0';
		} else
			state = 1;
	}
	return argc;
}

/* transform a string in a argc, *argv[]. and call the function from the
 *  argv[0]. */
int clicall (char *s)
{
	int i, j;
	int state; /*0 for '\0', 1 for else. */
	int argc = clitok(s);
	const char **argv = malloc (argc*sizeof(char*));

	for (j=0, i=0, state=0; j<argc; i++){
		if (s[i] != '\0'){
			if (!state){
				argv[j] = &s[i];
				j++;
				state = 1;
			}
		} else
			state = 0;
	}

	for (i=0; cli[i].s; i++){
		int ret;
		if (strcmp (cli[i].s, argv[0]) == 0){
			ret = cli[i].cb (argc, argv);
			free (argv);
			return ret;
		}
	}
	printf ("invalid command %s\n", argv[0]);
	free (argv);
	return -1;
}

int main (int argc, char *argv[])
{
	char buff[255];
	fgets (buff, 255, stdin);
	clicall (buff);
	return 0;
}
