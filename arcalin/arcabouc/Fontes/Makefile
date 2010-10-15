##################################################
### Makefile para gerar os binarios do arcabouco.
### 
### Autor : RLB
################################################## 

CC=gcc
CXX=g++
CFLAGS= -I. -ansi -Wall -g -O0 $(MORECFLAGS)
LFLAGS= -lm

ALLDEPS = \
CESPDIN.H\
EXBESTAT.H\
GERAALT.H\
INTRPCNT.H\
TABSIMB.H\
TST_ESPC.H\
CONTA.H\
GENERICO.H\
INTRPCED.H\
LERPARM.H\
TESTALT.H

CRIALIBOBJ = \
CESPDIN.o\
GERAALT.o\
INTRPCNT.o\
PRINCIP.o\
CONTA.o\
GENERICO.o\
INTRPCED.o\
LERPARM.o\
TABSIMB.o

ALEATORIOOBJ = \
$(CRIALIBOBJ)\
TESTALT.o

CONTADORESOBJ = \
$(CRIALIBOBJ)\
TESTCNT.o

CEDOBJ = \
$(CRIALIBOBJ)\
TESTCED.o

GENOBJ = \
$(CRIALIBOBJ)\
TESTGEN.o

LEROBJ = \
$(CRIALIBOBJ)\
TESTLER.o
	
TBSOBJ = \
$(CRIALIBOBJ)\
TESTTBS.o

PERMUTAOBJ = \
GERAALT.o\
GERAPERMUTACAO.o

ALLTARGS = \
libArcaboucoTeste.a\
TesteAleatorio\
TesteContadores\
TesteControleEspaco\
TesteFuncoes\
TesteLerParametros\
TesteTabelaSimbolos\
GeraPermutacao


libArcaboucoTeste.a: $(CRIALIBOBJ)
	ar rcs $@ $^

all:$(ALLTARGS)

%.o: %.C $(ALLDEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

TesteAleatorio: $(ALEATORIOOBJ)
	$(CC) -o $@ $^  $(CFLAGS) $(LFLAGS)

TesteContadores: $(CONTADORESOBJ)
	$(CC) -o $@ $^  $(CFLAGS) $(LFLAGS)

TesteControleEspaco: $(CEDOBJ)
	$(CC) -o $@ $^  $(CFLAGS) $(LFLAGS)
	
TesteFuncoes: $(GENOBJ)
	$(CC) -o $@ $^  $(CFLAGS) $(LFLAGS)
	
TesteLerParametros: $(LEROBJ)
	$(CC) -o $@ $^  $(CFLAGS) $(LFLAGS)
	
TesteTabelaSimbolos: $(TBSOBJ)
	$(CC) -o $@ $^  $(CFLAGS) $(LFLAGS)
	
GeraPermutacao: $(PERMUTAOBJ)
	$(CC) -o $@ $^  $(CFLAGS) $(LFLAGS)
	


.PHONY: clean
clean:
	rm -f ./*.o *~ core ./*~  ./lib*
	rm $(ALLTARGS) 2>/dev/null || true


