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
$(SRC)/usr.h

#  Dependencias de cada modulo
CLIOBJ=\
$(OBJ)/cli.o\
$(OBJ)/tstcli.o

GRAPHOBJ=\
$(OBJ)/lista.o\
$(OBJ)/graph.o\
$(OBJ)/tstgraph.o

LISTAOBJ=\
$(OBJ)/lista.o\
$(OBJ)/testlis.o

NETMGROBJ=\
$(OBJ)/usr.o\
$(OBJ)/graph.o\
$(OBJ)/netmgr.o\
$(OBJ)/tstnetmgr.o

USROBJ=\
$(OBJ)/lista.o\
$(OBJ)/usr.o\
$(OBJ)/tstusr.o

#  Alvos a serem compilados com `make all`
ALLTARGS = \
testcli\
testgraph\
testlista\
testnetmgr\
testusr

all:$(ALLTARGS)

%.o: $(SRC)/%.c $(ALLDEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

testcli: $(CLIOBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS)

testlista: $(LISTAOBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS) 

testgraph: $(GRAPHOBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS)
	
testnetmgr: $(NETMGROBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS)

testusr: $(USROBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS)


.PHONY: clean
clean:
	rm -f $(OBJ)/*.o 
	rm $(TRG)/$(ALLTARGS) 2>/dev/null || true


