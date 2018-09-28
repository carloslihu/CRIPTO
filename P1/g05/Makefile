IDIR=includes
ODIR=obj
SDIR=src
CC=gcc
CFLAGS= -g -Wall
LIBS= -lgmp -L.

#_DEPS =
_OBJ =afin.o

#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: afin

$(ODIR)/%.o: $(SDIR)/%.c #$(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


#EJECUTABLES
afin: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
#P3
tar:
	tar -czvf F-CSI_p1_g05.tgz ../g05/

.PHONY: clean
clean:
	-rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	-rm -f *.tar.gz
	-rm -f afin
