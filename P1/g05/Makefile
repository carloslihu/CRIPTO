IDIR=includes
ODIR=obj
SDIR=src
CC=gcc
CFLAGS= -g -Wall
LIBS= -lgmp -L.

#_DEPS =
#_OBJ =

#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: autores carpetas afin hill vigenere

$(ODIR)/%.o: $(SDIR)/%.c #$(DEPS)
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
afin: $(ODIR)/afin.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

hill: $(ODIR)/hill.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
vigenere: $(ODIR)/vigenere.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
#P3
tar:
	tar -czvf F-CSI_p1_g05.tgz ../g05/

.PHONY: clean
clean:
	-rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	-rm -f *.tar.gz
	-rm -f afin hill vigenere
