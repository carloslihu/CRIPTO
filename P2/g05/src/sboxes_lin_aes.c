/***************************************************************************
sboxes_lin_aes.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/AES_tables.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    int rep = 0;
    uint64_t X = 0, Y = 0;
    uint64_t B = 0;
    uint64_t SB[3] = {0}, aux = 0;
    int counter = 0, N = 1000000;


    srand(time(NULL));

    for (rep = 0; rep < N; rep++) {
        /*Generamos vectores aleatorios X, Y de 64 bits. Debemos comprobar que f(X + Y) != f(X) + f(Y) */

        X = cadena_aleatoria(64);
        Y = cadena_aleatoria(64);
        /*B es el vector de 64 bits que va a ser dividido en 8 trozos de 8*/
        B = X ^ Y;

        /* printf("0x%"PRIx64"\n", B);*/
        SB[0] = SB_AES_return(B);
        /*printf("0x%"PRIx64"\n", SB[0]);*/
        /*printf("0x%"PRIx64"\n", X);*/
        SB[1] = SB_AES_return(X);
        /*printf("0x%"PRIx64"\n", SB[1]);*/
        /*printf("0x%"PRIx64"\n", Y);*/
        SB[2] = SB_AES_return(Y);
        /*printf("0x%"PRIx64"\n", SB[2]);*/

        aux = SB[1] ^ SB[2];

        /*printf("0x%"PRIx64"\n", aux);*/

        if (aux == SB[0]) {
            counter++;
            printf("LINEALIDAD en rep=%d\n", rep);
        }

    }

    printf("Casos probados = %d\n", N);
    printf("Numero de casos lineales = %d\n", counter);


    return 0;


}
