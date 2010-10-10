#include    <stdio.h>
#include    <malloc.h>

#include    <string.h>
/*

#include    "../lista/lista.h"
*/
#include    "graph.h"
#include    "../arcab/tst_espc.h"
#include    "../arcab/generico.h"
#include    "../arcab/lerparm.h"

enum { MAXGRAPHS = 10 };
enum { MAXDATAS = 10 };

static pGraph vGraph[ MAXGRAPHS ];
static char * vData[ MAXDATAS ];

static int DataAlocCount = 0;

static const char GRAPHNEW_CMD            [ ] = "=GraphNew"           ;
static const char GRAPHDEL_CMD            [ ] = "=GraphDel"           ;
static const char GRAPHCCUR_CMD           [ ] = "=GraphCCurrent"      ;
static const char GRAPHNEWNODE_CMD        [ ] = "=GraphNewNode"       ;
static const char GRAPHDELNODE_CMD        [ ] = "=GraphDelNode"       ;
static const char GRAPHADDLINK_CMD        [ ] = "=GraphAddLink"       ;
static const char GRAPHREMLINK_CMD        [ ] = "=GraphRemLink"       ;
static const char GRAPHGETDATA_CMD        [ ] = "=GraphGetData"       ;
static const char GRAPHGETSUCC_CMD        [ ] = "=GraphGetSuccessor"  ;

static const char NEWDATA_CMD             [ ] = "=NewData"            ;

void *NewData ( char data )
{
	char *ret;
	ret = (char*) malloc (sizeof(char));
	DataAlocCount++;
	*ret = data;
	return ret;
}
void DelData ( void * pdata )
{
	free (pdata);
	DataAlocCount--;
}

TST_tpCondRet TST_EfetuarComando( char * CmdTeste )
{
	int argc, iGraph, iData;
	if(! strcmp( CmdTeste , 		GRAPHNEW_CMD) ){

      		argc = LER_LerParametros ( "i", &iGraph );
		
		if ( ! argc != 1 || argc < 0 || argc > MAXGRAPHS)
			return TST_CondRetParm;
		vGraph[iGraph] = GraphNew ( DelData );
            	return TST_CompararPonteiroNulo( 1 , vGraph[iGraph],
			"Erro: Ponteiro para novo grafo e' nulo." );

	}else if(! strcmp( CmdTeste , 		GRAPHDEL_CMD) ){

      		argc = LER_LerParametros ( "i", &iGraph );
		
		if ( ! argc != 1 || argc < 0 || argc > MAXGRAPHS)
			return TST_CondRetParm;
		GraphDel ( vGraph[iGraph] );
		vGraph[iGraph] = NULL;

            	return TST_CondRetOK;
		
	}else if(! strcmp( CmdTeste , 		GRAPHCCUR_CMD) ){

		

	}else if(! strcmp( CmdTeste , 		GRAPHNEWNODE_CMD) ){
	}else if(! strcmp( CmdTeste , 		GRAPHDELNODE_CMD) ){
	}else if(! strcmp( CmdTeste , 		GRAPHADDLINK_CMD) ){
	}else if(! strcmp( CmdTeste , 		GRAPHREMLINK_CMD) ){
	}else if(! strcmp( CmdTeste , 		GRAPHGETDATA_CMD) ){
	}else if(! strcmp( CmdTeste , 		GRAPHGETSUCC_CMD) ){
	}

        return TST_CondRetNaoConhec;
}


