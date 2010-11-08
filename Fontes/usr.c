#include <string.h>
#include <stdlib.h>
#include "usr.h"
#include "lista.h"

struct usr{
	char id[15];
	char name[50];
	enum interest interest;
	LIS_tppLista msgs;
};
typedef struct usr Usr;


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
char* UsrGetPId( Usr *u )
{
	return u->id;
}
char* UsrGetPName( pUsr u )
{
	return u->name;
}
enum interest* UsrGetPInterest( pUsr u )
{
	return &u->interest;
}
int UsrDeliver ( pUsr u, msg m)
{
	LIS_tpCondRet condRet;
	condRet = LIS_InserirElementoApos( u->msgs, m);
	if (LIS_CondRetOK == condRet)
		return 0;
	return condRet;
}
int UsrDelMsg ( pUsr u, int id)
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

