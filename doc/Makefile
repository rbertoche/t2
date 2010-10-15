# Generates Doc from asciidoc .txt files.

.PHONY: all clean graph html
all: pdf

graph:$(GRAPH)

clean:
	$(RM) $(HTML) $(GRAPH)
pdf:
	mpost arch.mp
	mpost example.mp
	latex graph.tex
	dvipdf graph.dvi
