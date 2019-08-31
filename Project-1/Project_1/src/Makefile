IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = Help.h Main.h Input.h Memalloc.h Memfree.h Meminv.h Memread.h Memwrite.h Patterngen.h Patternverify.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Help.o Main.o Input.o Memalloc.o Memfree.o Meminv.o Memread.o Memwrite.o Patterngen.o Patternverify.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Project: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
Test: ./Project testing
	./Project < testing

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 