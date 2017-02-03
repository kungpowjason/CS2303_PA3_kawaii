# Make file for PA3
# Written by: Yu-sen Wu (1/30/17)
#
# This makefile is used as follows to regenerate files for the sinewave program:
#   make PA3.o        --  Regenerates PA3.o by compiling
#   make wordparse.o  --  Regenerates wordparse.o by compiling
#   make tree.o  	  --  Regenerates tree.o by compiling
#   make PA3          --  Regenerates the executable PA3 file by compiling     
#	make              --  Same as "make PA3"
#

CFLAGS = -g -Wall

PA3: PA3.o wordparse.o tree.o
	gcc $(CFLAGS) PA3.o wordparse.o  tree.o -o PA3
	
PA3.o: wordparse.h PA3.c wordparse.c tree.h tree.c
	gcc $(CFLAGS) -c PA3.c wordparse.c tree.c

wordparse.o: wordparse.h wordparse.c
	gcc $(CFLAGS) -c wordparse.c
	
tree.o: tree.h tree.c
	gcc $(CFLAGS) -c tree.c
clean:
	rm -f PA3.o wordparse.o tree.o PA3

all: PA3
