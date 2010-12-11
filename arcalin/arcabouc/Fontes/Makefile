##################################################
### Makefile para gerar os binarios do arcabouco.
### 
### Autor : RLB
################################################## 

CC=gcc
CXX=g++
MYCFLAGS= -I. -ansi -Wall -g -O0 $(CFLAGS)
MYLFLAGS= -lm $(LFLAGS)

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
	$(CC) -c -o $@ $(MYCFLAGS) $<

TesteAleatorio: $(ALEATORIOOBJ)
	$(CC) -o $@ $^  $(MYCFLAGS) $(MYLFLAGS)

TesteContadores: $(CONTADORESOBJ)
	$(CC) -o $@ $^  $(MYCFLAGS) $(MYLFLAGS)

TesteControleEspaco: $(CEDOBJ)
	$(CC) -o $@ $^  $(MYCFLAGS) $(MYLFLAGS)
	
TesteFuncoes: $(GENOBJ)
	$(CC) -o $@ $^  $(MYCFLAGS) $(MYLFLAGS)
	
TesteLerParametros: $(LEROBJ)
	$(CC) -o $@ $^  $(MYCFLAGS) $(MYLFLAGS)
	
TesteTabelaSimbolos: $(TBSOBJ)
	$(CC) -o $@ $^  $(MYCFLAGS) $(MYLFLAGS)
	
GeraPermutacao: $(PERMUTAOBJ)
	$(CC) -o $@ $^  $(MYCFLAGS) $(MYLFLAGS)
	


.PHONY: clean
clean:
	rm -f ./*.o *~ core ./*~  ./lib*
	rm $(ALLTARGS) 2>/dev/null || true


