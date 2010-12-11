#include    <stdio.h>
#include    <malloc.h>

#include    <string.h>
/*

#include    "../lista/lista.h"
*/

#ifdef _DEBUG
#include    "cespdin.h"
#endif

#include    "graph.h"
#include    "tst_espc.h"
#include    "generico.h"
#include    "lerparm.h"

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

static const char GRAPHNODESSTART_CMD     [ ] = "=GraphNodesStart"    ;
static const char GRAPHLINKSSTART_CMD     [ ] = "=GraphLinksStart"    ;
static const char GRAPHNODESGETNEXT_CMD   [ ] = "=GraphNodesGetNext"  ;
static const char GRAPHLINKSGETNEXT_CMD   [ ] = "=GraphLinksGetNext"  ;

static const char NEWDATA_CMD             [ ] = "=NewData"            ;
static const char CMPDATA_CMD             [ ] = "=CmpData"            ;

#ifdef _DEBUG
static const char SHOW_MEMSPACES          [ ] = "=ShowMem"            ;
#endif

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
	int argc, Ret, ExpectedRet, iGraph, iData;

	if(! strcmp( CmdTeste , 		GRAPHNEW_CMD) ){


      		argc = LER_LerParametros ( "i", &iGraph );
		
		if ( argc != 1 
			|| iGraph < 0 || iGraph > MAXGRAPHS)
			return TST_CondRetParm;
		vGraph[iGraph] = GraphNew ( DelData );
            	return TST_CompararPonteiroNulo( 1 , vGraph[iGraph],
			"Erro: Ponteiro para novo grafo e' nulo." );


#ifdef _DEBUG
	}else if(! strcmp( CmdTeste , 		SHOW_MEMSPACES) ){


		CED_ExibirTodosEspacos( CED_ExibirTodos );
		return TST_CondRetOK;
#endif


	}else if(! strcmp( CmdTeste , 		GRAPHDEL_CMD) ){


      		argc = LER_LerParametros ( "i", &iGraph );
		
		if ( argc != 1 
			|| iGraph < 0 || iGraph > MAXGRAPHS)
			return TST_CondRetParm;
		GraphDel ( vGraph[iGraph] );
		vGraph[iGraph] = NULL;

            	return TST_CondRetOK;


	}else if(! strcmp( CmdTeste , 		GRAPHCCUR_CMD) ){


      		argc = LER_LerParametros ( "iii", &iGraph, &iData,
			&ExpectedRet);
		
		if ( argc != 3 
			|| iGraph < 0 || iGraph > MAXGRAPHS
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;
		Ret = GraphCCurrent ( vGraph[iGraph],  vData[iData] );

		
		return TST_CompararInt( ExpectedRet , Ret ,
			"Erro: Condicao de retorno errada em CCurent.");


	}else if(! strcmp( CmdTeste , 		GRAPHNEWNODE_CMD) ){


      		argc = LER_LerParametros ( "iii", &iGraph, &iData,
			&ExpectedRet);
		
		if ( argc != 3
			|| iGraph < 0 || iGraph > MAXGRAPHS
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;
		Ret = GraphNewNode ( vGraph[iGraph],  vData[iData] );

		
		return TST_CompararInt( ExpectedRet , Ret ,
			"Erro: Condicao de retorno errada em NewNode.");


	}else if(! strcmp( CmdTeste , 		GRAPHDELNODE_CMD) ){


		argc = LER_LerParametros ( "i", &iGraph);
		if ( argc != 2 
			|| iGraph < 0 || iGraph > MAXGRAPHS)
			return TST_CondRetParm;
		GraphDelNode ( vGraph[iGraph] );

		
		return TST_CondRetOK;


	}else if(! strcmp( CmdTeste , 		GRAPHADDLINK_CMD) ){


      		argc = LER_LerParametros ( "iii", &iGraph, &iData,
			&ExpectedRet);
		
		if ( argc != 3 
			|| iGraph < 0 || iGraph > MAXGRAPHS
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;
		Ret = GraphAddLink ( vGraph[iGraph],  vData[iData] );

		
		return TST_CompararInt( ExpectedRet , Ret ,
			"Erro: Condicao de retorno errada em AddLink.");


	}else if(! strcmp( CmdTeste , 		GRAPHREMLINK_CMD) ){


      		argc = LER_LerParametros ( "iii", &iGraph, &iData,
			&ExpectedRet);
		
		if ( argc != 3 
			|| iGraph < 0 || iGraph > MAXGRAPHS
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;
		Ret = GraphRemLink ( vGraph[iGraph],  vData[iData] );

		
		return TST_CompararInt( ExpectedRet , Ret ,
			"Erro: Condicao de retorno errada em RemLink.");

	}else if(! strcmp( CmdTeste , 		GRAPHGETDATA_CMD) ){


      		argc = LER_LerParametros ( "ii", &iGraph, &iData);
		
		if ( argc != 2
			|| iGraph < 0 || iGraph > MAXGRAPHS
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;
		vData[iData] = GraphGetData ( vGraph[iGraph]);

		return TST_CompararPonteiroNulo( 1 , vData[iData],
			"Erro: GetData retornou NULL. Ainda assim, NULL\
			foi armazenado" );
		

	}else if (! strcmp( CmdTeste ,		GRAPHNODESSTART_CMD) ){

      		argc = LER_LerParametros ( "i", &iGraph );
		
		if ( argc != 1
			|| iGraph < 0 || iGraph > MAXGRAPHS)
			return TST_CondRetParm;
		GraphNodesStart ( vGraph[iGraph] );

            	return TST_CondRetOK;
		
	}else if (! strcmp( CmdTeste ,		GRAPHLINKSSTART_CMD) ){

      		argc = LER_LerParametros ( "i", &iGraph );
		
		if ( argc != 1
			|| iGraph < 0 || iGraph > MAXGRAPHS)
			return TST_CondRetParm;
		GraphLinksStart ( vGraph[iGraph] );

            	return TST_CondRetOK;

	}else if (! strcmp( CmdTeste ,		GRAPHNODESGETNEXT_CMD) ){

		argc = LER_LerParametros ( "ii", &iGraph, &iData);
		
		if ( argc != 2 
			|| iGraph < 0 || iGraph > MAXGRAPHS
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;
		vData[iData] = GraphNodesGetNext ( vGraph[iGraph] );

		return TST_CompararPonteiroNulo( 1 , vData[iData],
			"Erro: GraphNodesGetNext retornou NULL. Ainda assim, NULL\
			foi armazenado" );

	}else if (! strcmp( CmdTeste ,		GRAPHLINKSGETNEXT_CMD) ){

		argc = LER_LerParametros ( "ii", &iGraph, &iData);
		
		if ( argc != 2 
			|| iGraph < 0 || iGraph > MAXGRAPHS
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;
		vData[iData] = GraphLinksGetNext ( vGraph[iGraph] );

		return TST_CompararPonteiroNulo( 1 , vData[iData],
			"Erro: GraphLinksGetNext retornou NULL. Ainda assim, NULL\
			foi armazenado" );

	}else if (! strcmp( CmdTeste ,		NEWDATA_CMD) ){
		char c;

		argc = LER_LerParametros ( "ic", &iData, &c);

		if ( argc != 2
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;
		vData[iData] = NewData ( c );

		return TST_CondRetOK;

	}else if (! strcmp( CmdTeste ,		CMPDATA_CMD) ){
		char c;

		argc = LER_LerParametros ( "ic", &iData, &c);

		if ( argc != 2
			|| iData  < 0 || iData  > MAXDATAS )
			return TST_CondRetParm;

		return TST_CompararInt( c , *(char*)vData[iData] ,
			"Erro: Char diferente do esperado.");

	}



        return TST_CondRetNaoConhec;
}


