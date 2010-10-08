//#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

//#include    "tst_espc.h"

//#include    "generico.h"
//#include    "lerparm.h"

#include    "graph.h"

static const int MAXGRAPHS = 10;
pGraph vGraph[ MAXGRAPHS ];

static const char GRAPHNEW_CMD            [ ] = "=GraphNew"           ;
static const char GRAPHDEL_CMD            [ ] = "=GraphDel"           ;
static const char GRAPHCCUR_CMD           [ ] = "=GraphCCurrent"      ;
static const char GRAPHNEWNODE_CMD        [ ] = "=GraphNewNode"       ;
static const char GRAPHDELNODE_CMD        [ ] = "=GraphDelNode"       ;
static const char GRAPHADDLINK_CMD        [ ] = "=GraphAddLink"       ;
static const char GRAPHREMLINK_CMD        [ ] = "=GraphRemLink"       ;
static const char GRAPHGETDATA_CMD        [ ] = "=GraphGetData"       ;
static const char GRAPHGETSUCC_CMD        [ ] = "=GraphGetSuccessor"  ;




