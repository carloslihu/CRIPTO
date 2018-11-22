IDIR=includes
ODIR=obj
SDIR=src
CC=gcc
CFLAGS= -g -Wall
LIBS= -lgmp -L. -lm

_DEPS =utils.h DES_tables.h AES_tables.h
_OBJ =utils.o DES_tables.o AES_tables.o

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: autores carpetas seg-perf desCBC tripleDESCBC sboxes_lin_des sboxes_lin_aes SBOX_AES

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
	
desCBC: $(OBJ) $(ODIR)/desCBC.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

tripleDESCBC: $(OBJ) $(ODIR)/tripleDESCBC.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
sboxes_lin_des: $(OBJ) $(ODIR)/sboxes_lin_des.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
sboxes_lin_aes: $(OBJ) $(ODIR)/sboxes_lin_aes.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

SBOX_AES: $(OBJ) $(ODIR)/SBOX_AES.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
tar:
	tar -czvf F-CSI_p2_g05.tgz ../g05/

.PHONY: clean
clean:
	-rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	-rm -f *.tar.gz
	-rm -f seg-perf desCBC tripleDESCBC sboxes_lin_des sboxes_lin_aes SBOX_AES
	-rm -f auxiliar.txt teclado.txt
