IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = custom_help.h custom_main.h custom_input.h custom_memalloc.h custom_memfree.h custom_meminv.h custom_memread.h custom_memwrite.h custom_patterngen.h custom_patternverify.h custom_system_identifier.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = custom_help.o custom_main.o custom_input.o custom_memalloc.o custom_memfree.o custom_meminv.o custom_memread.o custom_memwrite.o custom_patterngen.o custom_patternverify.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Dual: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
Test: ./Dual testing
	./Dual < testing

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 