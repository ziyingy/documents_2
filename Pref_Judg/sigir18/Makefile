FYLE = sp1234

pdf:
	pdflatex p

bbl:
	pdflatex p
	bibtex p
	pdflatex p
	pdflatex p

final:
	latexpand --expand-bbl ./p.bbl ./p.tex > $(FYLE).tex
	pdflatex $(FYLE)
	pdflatex $(FYLE)
	pdflatex $(FYLE)

clean:
	rm -f *~ *.bak *.aux *.blg *.log
