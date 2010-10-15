input metauml;


Class.mm ("") 
(
)
(
	"+ Felipe Pessoa",
	"+ Oi Joao, como vai?",
	"+ Joao",
);

Class.mn ("") 
(
)
(
	"+ Mariana",
	"+ Joao, esta conseguindo fazer o trabalho?",
	"+ Joao",
);
Class.mo ("") 
(
)
(
	"+ Joao",
	"+ Nao, esta meio complicado",
	"+ Mariana",
);

Class.Joao ("Joao") ()
(
	"+ Joao da Silva",
	"+ xptoxpto",
);

Class.Mariana ("Mariana")()
(
	"+ Mariana Pinheiro ",
	"+ 312312",
);

Class.Felipe ("Felipe")()
(
	"+ Felipe Pessoa ",
	"+ 777111",
);

Class.Maira ("Maira")()
(
	"+ Maira Lopes ",
	"+ 46.98.9",
);

Class.Luis ("Luis")()
(
	"+ Luis Fernando ",
	"+ xxx1111",
);

Class.Ana ("Ana")()
(
	"+ Ana Machado",
	"+ 123c123s",
);

beginfig(1);
topToBottom (25)(Mariana, Joao, Felipe, Maira);
leftToRight (50)(Mariana, mn);
leftToRight (50)(Felipe, mm);
leftToRight (50)(Joao, mo);
leftToRight (50)(Luis, Felipe);
leftToRight (50)(Ana, Mariana);
topToBottom (75)( mn, mm);
drawObjects (Mariana,Joao,Felipe,Maira,Ana, Luis, mm,mn,mo);
clink(association)(Mariana, Joao);
clink(association)(Joao, Felipe);
clink(association)(Luis, Felipe);
clink(association)(Luis, Joao);
clink(association)(Ana, Joao);
clink(association)(Ana, Felipe);
clink(associationUni)(Felipe,mm);
clink(associationUni)(mm,Joao);
clink(associationUni)(Joao,mo);
clink(associationUni)(mo,Mariana);
clink(associationUni)(Mariana,mn);
clink(associationUni)(mn,Joao);
endfig;

end
