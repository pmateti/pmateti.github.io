
# Makefile for StudyPrograms of Getting Started Lab

LAB=L1

CC=gcc
CFLAGS = -g -Wall -ansi -pedantic

recurse:	recurse.o
	$(CC) $(CFLAGS) -o $@ $^
	size $@
	ldd $@
	nm $@
	strace ./$@

# include similar lines for other programs

indent:
	indent -kr -i2 -pmt *.c *.h

tar archive: clean
	(cd ..; tar cvvfj ./$(LAB).tbz $(LAB); ls -l $(LAB).tbz)

clean:
	rm -frv *.o *~ *.out recurse
