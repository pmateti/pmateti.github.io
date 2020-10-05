
# AlephOne Examples and Exploits; 
# Makefile and a few minor changes to fix gcc warnings by pmateti@wright.edu

# see 00-ReadMe.txt

# part of your lab: fix so no erros or warnings are produced;

CFLAGS = -ansi -pedantic -Wall -Wno-format
FILES = Makefile \
	example1.c  exit.c      exploit3.c  recurse.c         testsc.c \
	example2.c  exploit1.c  exploit4.c  salloc.c          vulnerable.c \
	execsh.c    exploit2.c  modret.c    size-of-arrays.c  yasc.c

# all programs will have the non-std .prg extension

%.prg: %.c Makefile
	gcc $(CFLAGS) -o $@ $<

# to produce assembled machine code with assembly source listing

%.lst: %.c
	gcc $(CFLAGS) -Wa,-alh $< > $@

# generate the assembly code for the c file

%.s: %.c
	gcc -S $<

all:	\
 example1.prg  exit.prg      exploit3.prg  recurse.prg         testsc.prg \
 example2.prg  exploit1.prg  exploit4.prg  size-of-arrays.prg  yasc.prg \
 execsh.prg    exploit2.prg  modret.prg    vulnerable.prg

clean:
	rm -f *~ *.o *.prg *.s *.lst core* a.out \#*

tar archive: clean
	(cd ..; tar -cjf AlephOne`date  '+%G%m%d%H%M'`.tbz AlephOne)

