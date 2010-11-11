#define _ISOC99_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usr.h"
#include "lista.h"


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
int UsrDeliver ( Usr *u, msg m)
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

