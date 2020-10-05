#
# Makefile for turnin
#

INSTRUCTOR=pmateti
EMAILADDR=pmateti@wright.edu
TERM=2013-Fall
COURSE=ceg2350
# no trailing slash
SUBMITPARENT=/home/pmateti/ceg2350/TurnIns
INSTALL_DIR=/home/pmateti/ceg2350

CC = gcc
CFLAGS = -g -Wall -ansi -pedantic \
 -DCOURSE=\"$(COURSE)\" -DTERM=\"$(TERM)\" -DSUBMITPARENT=\"$(SUBMITPARENT)\"  \
 -DINSTRUCTOR=\"$(INSTRUCTOR)\" -DEMAILADDR=\"$(EMAILADDR)\"

turnin : turnin.o Makefile
	gcc -o turnin $(CFLAGS) turnin.o
	chmod 755 turnin
	chmod ugo+s turnin

# The program must be set to be a setuid program (mode 4755)
install: turnin
	@echo 	install -s -m 4755 turnin $(INSTALL_DIR)/turnin
	mkdir -p $(INSTALL_DIR)
	install -s -m 4755 turnin $(INSTALL_DIR)/turnin

clean:
	-@/bin/rm -f turnin *.o *~
