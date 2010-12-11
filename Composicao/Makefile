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
CFLAGS= -I. -I$(SRC) -ansi -Wall -g -O0 $(MORECFLAGS)
LFLAGS= -L../Objetos -lArcaboucoTeste


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
$(OBJ)/graph.o\
$(OBJ)/tstgraph.o

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


all:$(ALLTARGS)

%.o: $(SRC)/%.c $(ALLDEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean all

$(OBJ)/libArcaboucoTeste.a:
	make -C ../arcalin/arcabouc/Fontes/ libArcaboucoTeste.a
	cp ../arcalin/arcabouc/Fontes/libArcaboucoTeste.a $@

$(TRG)/testcli: $(CLIOBJ)
	$(CC) -o $@ $(LFLAGS) $^ $(CFLAGS)

$(TRG)/testlista: $(LISTAOBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS) 

$(TRG)/testgraph: $(GRAPHOBJ)
	$(CC) -c -o $(OBJ)/graph.o $(CFLAGS) -D_DEBUG $(SRC)/graph.c
	$(CC) -c -o $(OBJ)/tstgraph.o $(CFLAGS) -D_DEBUG $(SRC)/tstgraph.c
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS)
	
$(TRG)/testusr: $(USROBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS)

$(TRG)/testnetmgr: $(NETMGROBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS)

$(TRG)/rede_social: $(REDSOC)
	$(CC) -c -o $(OBJ)/graph.o $(CFLAGS) $(SRC)/graph.c
	$(CC) -o $(TRG)/$@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ)/*.o 
	rm $(TRG)/$(ALLTARGS) 2>/dev/null || true


