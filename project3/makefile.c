IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = mymalloc.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = mymalloc.o mallocdrv.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -m32 -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o -m32 $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

