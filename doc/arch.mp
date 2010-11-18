input metauml;

Class.cli ("cli")
(	"- cmds : cli_reg"
)(
 	"+ call (cmd : string) : string",
	"+ register (reg : cli_reg) : void"
);

Class.graph ("graph")
()
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

Class.list ("list")
(
)(
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

Class.netmgr ("NetworkManager")
("- u : Usr (Singleton)"
)(
	"+ IsAuthenticated () : bool",
	"+ NewUser (id : string) : string",
	"+ DelMe () : string",
	"+ EditMe (name : string, interesse : int, idade : int) : string",
	"+ UsrChange (id : name) : void",
	"+ Search (buffer : string, isFriend : bool, id : string, in: string, minAge : int, maxAge : int) : string",
	"+ AddFriend (id : string) : string",
	"+ UnFriend (id : string) : string",
	"+ Write (buffer : string, int destC, destV[] : string) : string",
	"+ Read (id : int) : string",
	"+ DelMsg (id : int) : string",
	"+ WhoAmI () : string",
	"+ Mail (buffer : string)"
);

Class.user ("user")
(		"+ id : string",
		"+ name : string",
		"+ age : int",
		"+ interest : Interest",
		"+ msgs : List",
)(
	"+ New (id : string) : Usr",
	"+ Del (id : string)",
	"+ Print (u : Usr, buffer : string) : int",
	"+ MsgList (u : Usr, buffer : string) : int",
	"+ MsgDeliver (u : Usr, m : Msg) : int",
	"+ MsgPrint (u : Usr, msgId : int) : string",
	"+ MsgDel (u : Usr, msgId : int) : int",
	"+ StrToIn ( s : string ) : int"
);

beginfig(1);
cli.nw = (0, 0);
netmgr.nw = cli.sw + (-130, -15);
graph.nw = netmgr.sw + (-15, -15);
list.nw = graph.sw + (-15, -15);
user.nw = graph.ne + (60, 0);

drawObjects (cli, netmgr, graph, list, user);

clink(associationUni)(cli, netmgr);
clink(associationUni)(netmgr, graph);
clink(associationUni)(netmgr, user);
clink(associationUni)(graph, list);
clink(associationUni)(user, list);
endfig;

end
