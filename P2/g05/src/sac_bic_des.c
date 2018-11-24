/***************************************************************************
sac_bic_des.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/DES_tables.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {

    int i = 0, j = 0;
    double unos[32] = {0}, ceros[32] = {0};
    uint64_t cadena = 0, cadena2 = 0;
    uint32_t /*SB = 0, */ SB2 = 0;
    double repeticiones = 10000000;
    FILE *fout;

    srand(time(NULL));

    fout = fopen("SAC_BIC.txt", "w");

    for (i = 0; i < repeticiones; i++) {

        cadena = cadena_aleatoria(48);
        /* 000001 000001 000001 000001 000001 000001 000001 000001 = 0x41041041041*/
        cadena2 = cadena ^ 0x41041041041; /*cambiamos un bit de cada una de las 8 cajas de 6 bits*/

        /*SB = SB_return(cadena);*/
        /*printf("1 0x%"PRIx32"\n", SB);*/
        SB2 = SB_return(cadena2);
        /*printf("2 0x%"PRIx32"\n", SB2);*/

        /*contamos los unos y los ceros de cada una de las posiciones bi de la salida de las SBoxes*/
        for (j = 0; j < 32; j++) {
            if (get_bit((uint64_t) SB2, (uint8_t) (j + 32)) == 0) ceros[j]++;
            else unos[j]++;
        }

    }

    fprintf(fout, "Resultados de SAC\n\n");
    for (j = 0; j < 32; j++) {
        fprintf(fout, "b%d\t\tP(1) = %lf\t\tP(0) = %lf\n", j + 1, unos[j] / repeticiones, ceros[j] / repeticiones);
    }


    printf("Creado fichero SAC_BIC.txt\n");

    fclose(fout);

    return 0;

}
