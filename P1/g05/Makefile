IDIR=includes
ODIR=obj
SDIR=src
CC=gcc
CFLAGS= -g -Wall
LIBS= -lgmp -L.

_DEPS =utils.h
_OBJ =utils.o

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: autores carpetas afin hill vigenere IC kasiski transposicion permutacion


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
afin: $(OBJ) $(ODIR)/afin.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

hill: $(OBJ) $(ODIR)/hill.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
vigenere: $(OBJ) $(ODIR)/vigenere.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

IC: $(OBJ) $(ODIR)/IC.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
kasiski: $(OBJ) $(ODIR)/kasiski.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
transposicion: $(OBJ) $(ODIR)/transposicion.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

permutacion: $(OBJ) $(ODIR)/permutacion.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
#P3
tar:
	tar -czvf F-CSI_p1_g05.tgz ../g05/

.PHONY: clean
clean:
	-rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	-rm -f *.tar.gz
	-rm -f afin hill vigenere IC kasiski transposicion permutacion
	-rm -f auxiliar.txt teclado.txt
