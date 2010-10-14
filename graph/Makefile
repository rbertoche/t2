##################################################
### Makefile para gerar os binarios do simples.
### 
### Autor : RLB
################################################## 

CC=gcc
CXX=g++
CFLAGS= -I. -ansi -Wall -g -O0 $(MORECFLAGS)


ALLDEPS = \
../lista/lista.h\
../arcab/generico.h\
../arcab/lerparm.h\
../arcab/tst_espc.h
   

SMOBJ = \
tstgraph.o\
graph.o

ALLTARGS = \
TestGraph\

TestGraph: $(SMOBJ)
	$(CXX) -static -o $@ $^ -L. -lArcaboucoTeste 

all: $(ALLTARGS)

%.o: %.C $(ALLDEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f ./*.o *~ core ./*~ 
	rm $(ALLTARGS) 2>/dev/null || true

