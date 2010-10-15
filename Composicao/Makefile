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


ALLDEPS=\
$(SRC)/lista.h\
$(SRC)/graph.h\
$(SRC)/generico.h\
$(SRC)/lerparm.h\
$(SRC)/tst_espc.h

LISTAOBJ=\
$(OBJ)/lista.o\
$(OBJ)/testlis.o

GRAPHOBJ=\
$(OBJ)/graph.o\
$(OBJ)/lista.o\
$(OBJ)/tstgraph.o

ALLTARGS = \
testgraph\
testelista

all:$(ALLTARGS)

%.o: $(SRC)/%.c $(ALLDEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

testlista: $(LISTAOBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS) 

testgraph: $(GRAPHOBJ)
	$(CC) -o $(TRG)/$@ $(LFLAGS) $^ $(CFLAGS)
	


.PHONY: clean
clean:
	rm -f $(OBJ)/*.o 
	rm $(TRG)/$(ALLTARGS) 2>/dev/null || true


