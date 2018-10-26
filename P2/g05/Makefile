IDIR=includes
ODIR=obj
SDIR=src
CC=gcc
CFLAGS= -g -Wall
LIBS= -lgmp -L. -lm

_DEPS =utils.h
_OBJ =utils.o

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: autores carpetas seg-perf

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


autores: 
	@echo "---------------------------------------"
	@echo "|             Carlos Li Hu            |"
	@echo "|           David Lopez Ramos         |"
	@echo "---------------------------------------"


carpetas:
	mkdir -p includes
	mkdir -p obj

#EJECUTABLES
seg-perf: $(OBJ) $(ODIR)/seg-perf.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
#P3
tar:
	tar -czvf F-CSI_p2_g05.tgz ../g05/

.PHONY: clean
clean:
	-rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	-rm -f *.tar.gz
	-rm -f seg-perf
