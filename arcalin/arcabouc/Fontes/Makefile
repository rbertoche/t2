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
cespdin.h\
exbestat.h\
geraalt.h\
intrpcnt.h\
tabsimb.h\
tst_espc.h\
conta.h\
generico.h\
intrpced.h\
lerparm.h\
testalt.h

CRIALIBOBJ = \
cespdin.o\
geraalt.o\
intrpcnt.o\
princip.o\
conta.o\
generico.o\
intrpced.o\
lerparm.o\
tabsimb.o

ALEATORIOOBJ = \
$(CRIALIBOBJ)\
testalt.o

CONTADORESOBJ = \
$(CRIALIBOBJ)\
testcnt.o

CEDOBJ = \
$(CRIALIBOBJ)\
testced.o

GENOBJ = \
$(CRIALIBOBJ)\
testgen.o

LEROBJ = \
$(CRIALIBOBJ)\
testler.o
	
TBSOBJ = \
$(CRIALIBOBJ)\
testtbs.o

PERMUTAOBJ = \
geraalt.o\
gerapermutacao.o

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

%.o: %.c $(ALLDEPS)
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


