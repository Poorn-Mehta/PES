IDIR =../inc
CC=gcc
CFLAGS=-I$(IDIR) -lcunit

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = Custom_Circular_Buffer.h Custom_Main.h Custom_Sys_Identifier.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Custom_Circular_Buffer.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJ2 = Custom_Circular_Buffer.o test.o
OBJ2 = $(patsubst %,$(ODIR)/%,$(_OBJ2))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

project: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
test: $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 