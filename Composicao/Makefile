##################################################
### Makefile para gerar os binarios do arcabouco.
### 
### Autor : RLB
################################################## 

CC=gcc
CXX=g++
OBJ=../Objetos
TRG=../Produto
SRC=../Fontes
MYCFLAGS= -I. -I$(SRC) -ansi -Wall -g -O0 $(CFLAGS)
MYLFLAGS= -L../Objetos -lArcaboucoTeste $(LFLAGS)
DBGCFLAGS= -D_DEBUG

ARCABDEPS=\
$(SRC)/generico.h\
$(SRC)/lerparm.h\
$(SRC)/tst_espc.h

#  Dependencias de todos os .o (headers)
ALLDEPS=\
$(ARCABDEPS)\
$(SRC)/cli.h\
$(SRC)/graph.h\
$(SRC)/lista.h\
$(SRC)/netmgr.h\
$(SRC)/usr.h\
$(SRC)/cespdin.h

#  Dependencias de cada modulo
CLIOBJ=\
$(OBJ)/libArcaboucoTeste.a\
$(OBJ)/cli.o\
$(OBJ)/tstcli.o

GRAPHOBJ=\
$(OBJ)/libArcaboucoTeste.a\
$(OBJ)/lista.o\
$(OBJ)/graph.dbg.o\
$(OBJ)/tstgraph.dbg.o

LISTAOBJ=\
$(OBJ)/libArcaboucoTeste.a\
$(OBJ)/lista.o\
$(OBJ)/testlis.o

USROBJ=\
$(OBJ)/libArcaboucoTeste.a\
$(OBJ)/lista.o\
$(OBJ)/usr.o\
$(OBJ)/tstusr.o

NETMGROBJ=\
$(OBJ)/libArcaboucoTeste.a\
$(OBJ)/lista.o\
$(OBJ)/graph.o\
$(OBJ)/usr.o\
$(OBJ)/netmgr.o\
$(OBJ)/tstnetmgr.o

REDSOC=\
$(OBJ)/cli.o\
$(OBJ)/lista.o\
$(OBJ)/usr.o\
$(OBJ)/graph.o\
$(OBJ)/netmgr.o\
$(OBJ)/main.o

#  Alvos a serem compilados com `make all`
ALLTARGS = \
$(TRG)/testcli\
$(TRG)/testgraph\
$(TRG)/testlista\
$(TRG)/testusr\
$(TRG)/testnetmgr\
$(TRG)/rede_social


.PHONY: clean all debug

all:$(ALLTARGS)

clean:
	rm -f $(OBJ)/*.o
	rm $(TRG)/$(ALLTARGS) 2>/dev/null || true


%.o: $(SRC)/%.c $(ALLDEPS)
	$(CC) -c -o $@ $(MYCFLAGS) $<

# Compiled with debug only
%.dbg.o: $(SRC)/%.c $(ALLDEPS)
	$(CC) -c -o $@ $(DBGCFLAGS) $(MYCFLAGS) $<

$(OBJ)/libArcaboucoTeste.a:
	make -C ../arcalin/arcabouc/Fontes/ libArcaboucoTeste.a
	cp ../arcalin/arcabouc/Fontes/libArcaboucoTeste.a $@

$(TRG)/testcli: $(CLIOBJ)
	$(CC) -o $@ $(MYLFLAGS) $^ $(MYCFLAGS)

$(TRG)/testlista: $(LISTAOBJ)
	$(CC) -o $(TRG)/$@ $(MYLFLAGS) $^ $(MYCFLAGS)

$(TRG)/testgraph: $(GRAPHOBJ)
	$(CC) -o $(TRG)/$@ $(MYLFLAGS) $^ $(MYCFLAGS)
	
$(TRG)/testusr: $(USROBJ)
	$(CC) -o $(TRG)/$@ $(MYLFLAGS) $^ $(MYCFLAGS)

$(TRG)/testnetmgr: $(NETMGROBJ)
	$(CC) -o $(TRG)/$@ $(MYLFLAGS) $^ $(MYCFLAGS)

$(TRG)/rede_social: $(REDSOC)
	$(CC) -o $(TRG)/$@ $^ $(MYCFLAGS)


