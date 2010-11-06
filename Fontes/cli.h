#ifndef __CLI_H_
#define __CLI_H_

typedef int (*fncallback) (int argc, const char *argv[]);

struct cli_cmd_tuple {
	char *s;
	fncallback cb;
};

/* Transforma a string tokenizando-a em comando e lista de argumentos e
 * executa a funcao registrada correspondente ao comando. Retorna -1 caso
 * o comando nao exista ou o retorno do comando caso contrario. */
int cli_call (char *s);

/* Registra um vetor de struct cli_cmd_tuple. Esse vetor contem o mapeamento
 * dos comandos para as funcoes que respondem por eles.
 *
 * Assertiva:
 * - Esse vetor deve ser terminado por { NULL, NULL }. */
void cli_register_tuple (const struct cli_cmd_tuple *cmds);


#endif
