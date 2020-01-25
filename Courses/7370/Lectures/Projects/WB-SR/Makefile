#
# Makefile for 730 WhiteBoard in SR

CC = gcc
SR = sr
SRFLAGS = 
I = ./Interfaces

link: a.out

a.out: $I/wbclient.o $I/main.o $I/wbserver.o $I/g.o xwindow.o
	srl -v -L2 -o wb wbclient wbserver g main xwindow.o -lX11 -lc

compile: $I/wbclient.o $I/main.o $I/wbserver.o $I/g.o xwindow.o

run: link
	a.out 

$I/wbclient.o: $I/wbserver.spec $I/g.spec $I/g.o $I/wbclient.spec client.sr
	$(SR) $(SRFLAGS) -b client.sr

$I/wbclient.spec: specs.sr
	$(SR) $(SRFLAGS) -s specs.sr

$I/main.o: $I/g.spec $I/g.o $I/wbclient.spec $I/wbserver.spec $I/main.spec\
 main.sr
	$(SR) $(SRFLAGS) -b main.sr

$I/main.spec: main.sr
	$(SR) $(SRFLAGS) -s main.sr

$I/wbserver.o: $I/wbclient.spec $I/g.spec $I/g.o $I/wbserver.spec server.sr
	$(SR) $(SRFLAGS) -b server.sr

$I/wbserver.spec: specs.sr
	$(SR) $(SRFLAGS) -s specs.sr

$I/g.o: $I/g.spec specs.sr
	$(SR) $(SRFLAGS) -b specs.sr

$I/g.spec: specs.sr
	$(SR) $(SRFLAGS) -s specs.sr

clean:
	rm -rf $I  xwindow.o wb

cleanx: clean
	rm -f core a.out

ls:
	@echo client.sr main.sr server.sr specs.sr xwindow.c

make:
	srm client.sr main.sr server.sr specs.sr xwindow.c

