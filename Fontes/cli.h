#ifndef __CLI_H_
#define __CLI_H_

/* Tipo dos ponteiros das funcoes a serem registradas com comandos
 * Os argumentos na linha de comando lida sao tokenizados:
 * argc vale o numero de argumentos e argv um vetor contendo os
 * argumentos em strings */
typedef int (*fncallback) (int argc, const char *argv[]);

/* struct utilizada para criar um registro de comando
 * s deve conter a string do comando
 * cb a funcao a ser executada. */
struct cli_cmd_tuple {
	char *s;
	fncallback cb;
};

/* Le e interpreta uma linha de comando.
 * Tokeniza a string e executa a funcao registrada correspondente ao comando.
 * Retorna -1 caso o comando nao exista ou o retorno do comando caso
 * contrario. */
int cli_call (char *s);

/* Registra um vetor de registros de comandos. Esse vetor contem o mapeamento
 * dos comandos para as funcoes que respondem por eles.
 *
 * Assertiva estrutural:
 * - Esse vetor deve ser terminado por { NULL, NULL }. */
void cli_register_tuple (const struct cli_cmd_tuple *cmds);


#endif
