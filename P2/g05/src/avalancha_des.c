/***************************************************************************
avalancha_des.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/DES_tables.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {

    int i = 0, cambios = 0;
    uint64_t key = 0, key2 = 0;
    uint64_t Mens = 0, Mens2 = 0;
    uint64_t *rondas, *rondas_mensaje, *rondas_clave;
    uint64_t diferencia[17] = {0};
    int bits_diferentes[17] = {0};
    int bits_xor[3] = {8, 12, 14}; /*cambiar bits en xor, teniendo en cuenta la clave con la ultima cifra de paridad 1000, 1100, 1110*/
    FILE *fout; 

    srand(time(NULL));

    fout = fopen("avalancha.txt", "w");

    rondas = (uint64_t*) malloc(sizeof (uint64_t)*17);
    rondas_mensaje = (uint64_t*) malloc(sizeof (uint64_t)*17);
    rondas_clave = (uint64_t*) malloc(sizeof (uint64_t)*17);

    key = createKey();
    Mens = 0x0123456789ABCDEF;


    encode_block_avalancha(Mens, key, 1, &rondas);

    /*vamos realizando cambios en el numero de bits*/
    for (cambios = 1; cambios < 4; cambios++) {

        /*cambios en el mensaje*/
        Mens2 = Mens ^ bits_xor[cambios - 1];
        encode_block_avalancha(Mens2, key, 1, &rondas_mensaje);
        fprintf(fout, "\nCambiando %d bits del mensaje\n", cambios);
        for (i = 0; i < 17; i++) {
            diferencia[i] = rondas[i] ^ rondas_mensaje[i];
            bits_diferentes[i] = contar_unos(diferencia[i]);
            fprintf(fout, "Ronda %d:\tbits diferentes = %d\n", i, bits_diferentes[i]);
        }

        /*cambios en la clave*/
        key2 = key ^ bits_xor[cambios - 1];
        encode_block_avalancha(Mens, key2, 1, &rondas_clave);
        fprintf(fout, "\nCambiando %d bits de la clave\n", cambios);
        for (i = 0; i < 17; i++) {
            diferencia[i] = rondas[i] ^ rondas_clave[i];
            bits_diferentes[i] = contar_unos(diferencia[i]);
            fprintf(fout, "Ronda %d:\tbits diferentes = %d\n", i, bits_diferentes[i]);
        }
    }

    free(rondas);
    free(rondas_mensaje);
    free(rondas_clave);

    printf("Creado fichero avalancha.txt\n");

    fclose(fout);

    return 0;

}
