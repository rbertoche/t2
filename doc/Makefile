# Generates Doc from asciidoc .txt files.

.PHONY: all clean graph html
all: pdf

graph:$(GRAPH)

clean:
	$(RM) $(HTML) $(GRAPH)
pdf:
	mpost arch.mp
	pdflatex graph.tex
