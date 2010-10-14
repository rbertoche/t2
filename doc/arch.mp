input metauml;

Class.cli ("cli") ()
(
	"+ run (cmd : string) : condRet",
	"+ print () : void",
	"+ readline ( line : string) : void",
);

Class.gman ("GraphManager") ()
(
	"+ login (nick : string, passwd : string) : CondRet",
	"+ logout () : void",
);

Class.user ("user")
(
	"- Name : string",
	"- Tel : string",
	"- nick : string",
	"- passwd : string",
)
(
);

Class.msg ("msg")
(
	"- mensagem : string",
	"- orig : string",
	"- dest : string",
	"- cc : List",
	"- refcount : int",
)
(
	"+ New (msg : string, orig : string, dest : string) : Msg",
	"+ GetSender (msg : Msg) : string",
	"+ GetccList (msg : Msg) : List",
);

Class.graph ("graph") ()
(
	"+ New (DestroyFunction) : Graph",
	"+ Del (g : Graph) : void",
	"+ DelNode (g : Graph) : void",
	"+ AddLink (g : Graph, d : Data) : CondRet",
	"+ RemLink (g : Graph, d : Data) : CondRet",
	"+ GetData (g : Graph) : Data",
	"+ ListStart (l : List) : void",
	"+ ListGetNext (l : List) : Data",
	"+ GetLinks (g : Graph) : List",
	"+ GetNodes (g : Graph) : List",
);

Class.list ("list") ()
(
	"+ CriarLista (DestroyFunction) : List",
	"+ DestruirLista (l : List) : void",
	"+ EsvaziarLista (l : List) : void",
	"+ InserirElementoAntes (l : List, elemento : Data) : CondRet",
	"+ InserirElementoApos (l : List, elemento : Data) : CondRet",
	"+ ExcluirElemento (l : List) : CondRet",
	"+ ObterValor (l : List) : Data",
	"+ IrInicioLista (l : List) : void",
	"+ IrFinalLista (l : Lista) : void",
	"+ AvancarElementoCorrente (l : Lista, steps : int) : CondRet",
	"+ ProcurarValor (l : Lista, dat : Data) : CondRet",
);

beginfig(1);
topToBottom (25)(cli, graph, list);
leftToRight (25)(graph, msg);
topToBottom (25)( user, msg);
drawObjects (cli, graph, list, user, msg);
clink(associationUni)(cli, graph);
clink(associationUni)(cli, user);
clink(associationUni)(graph, list);
clink(associationUni)(user, msg);
endfig;

end
