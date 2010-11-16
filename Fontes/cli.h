#ifndef __CLI_H_
#define __CLI_H_

/***************************************************************************
*
*	$MCD M�dulo de defini��o: Cli
*
*	Arquivo gerado:		cli
*
*	Autores: rlb gac mpc
*
*	$HA Hist�rico de evolu��o:
*		Vide repositorio Git
*
*	$ED Descri��o do m�dulo
*           M�dulo de implementa��o da linha de comando respons�vel
*           por todas altera��es na rede de relacionamentos
***************************************************************************/
typedef const char * (*fncallback) (int argc, const char *argv[]);

/***********************************************************************
*	$TC Tipo de Dados: cli_cmd_tuple
*	$ED Descri��o do tipo
*		struct utilizada para criar um registro de comando
***********************************************************************/
struct cli_cmd_tuple {
	char *s;
	fncallback cb;
};
/***********************************************************************
*
*	$FC Funcao: cli_call
*
*	$EP Parametros
*		$P s - ponteiro para string de comandos.
*
*	$ED Descri��o da fun��o
*		        Le e interpreta uma linha de comando.
*               Tokeniza a string e executa a funcao registrada
*               correspondente ao comando. Retorna -1 caso o comando nao
*               exista ou o retorno do comando caso contrario.
*
*	$FV Valor retornado
*		        -1 caso o comando nao exista ou o retorno do comando caso
*               contr�rio.
*
***********************************************************************/

const char *cli_call (char *s);

 /***********************************************************************
*
*	$FC Funcao: cli_register_tuple
*
*	$EP Parametros
*		$P cmds - ponteiro para estrutura de registro de comando.
*
*	$ED Descricao da funcao
*               Registra um vetor de registros de comandos. Esse vetor
*               contem o mapeamento dos comandos para as funcoes que
*               respondem por eles.

*
***********************************************************************/
void cli_register_tuple (const struct cli_cmd_tuple *cmds);


#endif
