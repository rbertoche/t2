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
*	        Le e interpreta uma linha de comando.
*               Tokeniza a string e executa a funcao registrada
*               correspondente ao comando. Caso o comando entrado nao tenha
*               funcao correspondente, o modulo tentara' chamar uma funcao
*               'ferr' registrada como { NULL, ferr } caso exista ou retornara'
*               NULL caso nao exista.
*
*
*	$FV Valor retornado
*		NULL caso haja falha, const char *retornado pela funcao de
*		callback no caso de sucesso.
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
*	$AE Assertiva Estrutural
*		A ultima entrada do vetor de comandos e' { NULL, NULL } ou
*		{ NULL, ferr }. ferr e' uma funcao que recebe os comandos
*		sem match.
*
***********************************************************************/
void cli_register_tuple (const struct cli_cmd_tuple *cmds);


#endif
