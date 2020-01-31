
# file: Makefile

PAPER = ipfs-2018

ipfs-2018.pdf: ipfs-2018.blg
	-pdflatex $(PAPER).tex
	-@echo 
	-@echo TBDs to be taken care of:
	-grep TBD -Rn Sections

ipfs-2018.aux: ipfs-2018.tex
	-pdflatex $(PAPER).tex

ipfs-2018.blg: ipfs-2018.aux
	-bibtex $(PAPER)

tar archive: clean
	-mkdir -p ../TBD
	-tar -cjhlf ../TBD/$(PAPER)-`date +%G%m%d%H%M`.tbz  ../$(PAPER)
	-ls -lR ../TBD
clean:
	-rm -f *~ *.aux *.bbl *.blg *.log *.out *.toc # $(PAPER).pdf

