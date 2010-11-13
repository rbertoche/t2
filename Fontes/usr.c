#define _ISOC99_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "usr.h"


/* Isso permite snprintf de C99 no gcc */
#define _ISOC99_SOURCE
#include <stdio.h>
#undef _ISOC99_SOURCE

/* Isso permite snprintf de C99 no MSVS */
#if _MSC_VER
#define snprintf _snprintf
#endif
/* Estamos usando uma funcao de C99. Sem essa funcao, o buffer
 * que utilizamos em UsrPrint e UsrMsgPrint em estaria sujeito
 * a buffer overflow, ou entao teriamos que fazer strcpy desnecessario.
 */


const char *sInterest[] = {
	"Invalid",
	"Work",
	"Friends",
	"Sex",
	"None"
};

Usr* UsrNew( char id[15] )
{
	Usr *ret;
	ret = malloc (sizeof(Usr));
	strcpy(ret->id, id);
	ret->msgs = LIS_CriarLista(free);
	return ret;	
}
void UsrDel( void *u)
{
	LIS_DestruirLista( ((Usr*)u)->msgs );
	free (u);
	return;
}


int UsrPrint( Usr *u, char *buffer, int size)
{
	return snprintf( buffer, size,
				"%s\n"
				"%s\n"
				"Idade:%d\n"
				"Interesse: %s\n"
				"\n"
			,u->id,u->name,u->age,sInterest[u->interest]);
}

int printmsgheader ( char * msg, char *_buffer, int size)
{
/* formato da string msg:
remetente:destinatario1:destinatario2: ... :destinatarioN::Assunto:conteudodamensagem\0
*/
	char *buffer = _buffer;
	int bToWrite=0;

	if ( strstr(strstr(msg,"::"),":") - msg > size )
		return buffer - _buffer;

	/* Coloca o remetente */
	buffer += sprintf( buffer, "From: " );
	bToWrite = strchr( msg, ':' ) - msg;
	memcpy ( buffer, msg, bToWrite );
	buffer += bToWrite;
	msg += bToWrite + 1; /* +1 pula o : */
	buffer += sprintf( buffer, "\nTo: " );

	/* Coloca a lista de destinatarios ate encontrar "::" */
	while ( *msg != ':' ){
		bToWrite = strchr( msg, ':' ) - msg;
		memcpy ( buffer, msg, bToWrite );
		buffer += bToWrite;
		msg += bToWrite + 1; /* pula o : */
		buffer += sprintf( buffer, "; " );
	}
	buffer -= 2; /* Tira o "; " final sobrando */
	msg++; /* pula o : */
	(*buffer++) = '\n';

	/* printa assunto */
	bToWrite = strchr( msg, ':' ) - msg;
	memcpy ( buffer, msg, bToWrite );
	buffer += bToWrite;
	*buffer = '\0'; /* Poe um \0 que pode ser sobrescrito */
	/* msg += 1 + bToWrite; So e' necessario caso o header aumente */
	return buffer - _buffer;
}

int printmsgcontent ( char * msg, char *buffer, int size)
{
	int msgLen;
	msg = 2 + strstr(msg,"::");
	*strstr(msg,":") = '\n'; /* Troca o separador : por \n */
	msgLen = strlen(msg);
	if ( size < msgLen )
		return 0;
	strcpy(buffer,msg);
	return msgLen;
}

int UsrMsgDeliver ( Usr *u, msg m)
{
	LIS_tpCondRet condRet;
	condRet = LIS_InserirElementoApos( u->msgs, m);
	if (LIS_CondRetOK == condRet)
		return 0;
	return condRet;
}

int UsrDelMsg ( Usr *u, int id)
{
	LIS_tpCondRet condRet;
	condRet = LIS_AvancarElementoCorrente(
		u->msgs ,id );
	if (LIS_CondRetOK == condRet){
		LIS_ExcluirElemento( u->msgs ) ;
		IrInicioLista( u->msgs ) ;
		return 0;
	}
	IrInicioLista( u->msgs ) ;
	return condRet;
}

int UsrMsgList( Usr *u, char *_buffer, int size )
{
	int i=0, bWritten;
	char *buffer = _buffer;
	IrInicioLista( u->msgs );
	while (LIS_CondRetOK ==  LIS_AvancarElementoCorrente( u->msgs,1 )){
		bWritten = sprintf(buffer, "%d - ",i++);
		buffer += bWritten;
		size -= bWritten;
		bWritten = printmsgheader( LIS_ObterValor ( u->msgs ) ,
				buffer,size );
		buffer += bWritten;
		size -= bWritten;
	}
	return buffer - _buffer;
}

int UsrMsgPrint( Usr *u, int msgNumber, char *buffer, int size )
{
	LIS_tpCondRet condRet;
	char * msg;
	condRet = LIS_AvancarElementoCorrente(
		u->msgs ,msgNumber );
	if (LIS_CondRetOK == condRet){
		msg = LIS_ObterValor ( u->msgs ) ;
		IrInicioLista( u->msgs ) ;
		return printmsgcontent( msg, buffer, size);
	}
	IrInicioLista( u->msgs ) ;
	return 0;
}
