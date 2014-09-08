.PHONY: all clean tidy

all:	sc14-tut.pdf

%.pdf:	%.tex
	pdflatex $*
	pdflatex $*

tidy:
	rm -f *.aux *.dvi *.log *.out *.toc

clean:	tidy
	rm -f *.pdf
