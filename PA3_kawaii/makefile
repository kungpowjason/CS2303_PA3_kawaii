# Make file for PA3
# Written by: Yu-sen Wu (1/30/17)
#
# This makefile is used as follows to regenerate files for the sinewave program:
#   make PA3.o        --  Regenerates PA3.o by compiling
#   make wordparse.o  --  Regenerates wordparse.o by compiling
#   make PA3          --  Regenerates the executable PA3 file by compiling     
#	make              --  Same as "make PA3"
#

CFLAGS = -g -Wall

PA3: PA3.o wordparse.o
	gcc $(CFLAGS) PA3.o wordparse.o -o PA3
	
PA3.o: wordparse.h PA3.c wordparse.c 
	gcc $(CFLAGS) -c PA3.c wordparse.c

wordparse.o: wordparse.h wordparse.c
	gcc $(CFLAGS) -c wordparse.c

clean:
	rm -f PA3.o wordparse.o PA3

all: PA3
