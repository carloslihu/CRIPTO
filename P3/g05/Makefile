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

all: autores carpetas powm primo vegas

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
powm: $(OBJ) $(ODIR)/powm.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
primo: $(OBJ) $(ODIR)/primo.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
vegas: $(OBJ) $(ODIR)/vegas.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
tar:
	tar -czvf F-CSI_p3_g05.tgz ../g05/

.PHONY: clean
clean:
	-rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	-rm -f *.tar.gz
	-rm -f powm primo vegas
	-rm -f auxiliar.txt teclado.txt
