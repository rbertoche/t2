# Generates pdf, dvi, etc, from tex.
# graph:$(GRAPH)

# Disable default implicit rules (or my dvi rule will never be used)
.SUFFIXES:

# do not remove blank line above

# uncomment this to use pdflatex
# LATEX = pdflatex

GRAPH = graph.pdf
ALLTARGS = \
$(GRAPH)

LATEXDEPS = \
arch.1\
fisico.eps

PDFLATEXDEPS = \
arch.1\
fisico.pdf

ifeq ($(LATEX),pdflatex)
TEXIMGEXT=%.pdf
else
TEXIMGEXT=%.eps
endif

all: $(ALLTARGS)


# convert is found at ImageMagick
$(TEXIMGEXT): %.jpg
	convert $< $@
$(TEXIMGEXT): %.gif
	convert $< $@
$(TEXIMGEXT): %.png
	convert $< $@
$(TEXIMGEXT): %.svg
	convert $< $@

%.eps: %.pdf
	pdftops -eps $< $@


%.1: %.mp
	mpost $<


ifeq ($(LATEX),pdflatex)
%.pdf: %.tex $(PDFLATEXDEPS)
	pdflatex $<
else
%.dvi: %.tex $(LATEXDEPS)
	latex $<
%.pdf: %.dvi %.tex $(LATEXDEPS)
	dvipdf $<
endif

.PHONY: clean

clean:
	$(RM) *.1 *.dvi *.aux *.log $(GRAPH)
