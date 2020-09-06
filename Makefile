# Makefile for sysvshmem examples
#
# Jim Teresco, CS 432
# The College of Saint Rose
#
# Mon Feb  8 12:25:42 EST 2016
#
# $Id$
#
CFILES=sysvshmem.c
OFILES=$(CFILES:.c=.o)
CC=gcc -Wall

sysvshmem:	$(OFILES)
	$(CC) -o sysvshmem $(OFILES)

clean::
	/bin/rm -f sysvshmem $(OFILES)
