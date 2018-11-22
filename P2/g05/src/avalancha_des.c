/***************************************************************************
avalancha_des.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/DES_tables.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {

    FILE *fIn = NULL, *fOut = NULL;
    int count;
    uint64_t key = 0;
    uint64_t* subkeys;
    uint64_t Mens;
    uint64_t C, Caux;
    uint64_t *rondas, *rondas_mensaje, *rondas_clave;


    srand(time(NULL));

    rondas = (uint64_t*)malloc(sizeof(uint64_t)*16);
    rondas_mensaje = (uint64_t*)malloc(sizeof(uint64_t)*16);
    rondas_clave = (uint64_t*)malloc(sizeof(uint64_t)*16);

    key = createKey();

    /*Obtenemos subclaves*/
    subkeys = createSubkeys(key);
    /*for (i = 0; i < 16; i++) {
        printf("K%d: %" PRIx64 "\n", i, subkeys[i]);
    }*/

    /*Aquí vamos leyendo del fichero*/
    encode_block_avalancha(Mens, subkeys, cifrar, &rondas);
    /*printf("Cifrado 0x%"PRIx64"\n", C);*/
   
    free(subkeys);
    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);


    return 0;

}
