/***************************************************************************
sboxes_lin.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/DES_tables.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    int rep = 0;
    uint64_t X = 0, Y = 0;
    uint64_t B = 0;
    uint32_t SB[3] = {0}, aux = 0;
    int counter = 0;


    srand(time(NULL));

    for(rep = 0; rep < 1000000; rep++) {
        /*Generamos vectores aleatorios X, Y de 48 bits. Debemos comrprobar que f(X + Y) != f(X) + f(Y) */

        X = cadena_aleatoria();
        /*printf("X 0x%"PRIx64"\n", X);*/
        Y = cadena_aleatoria();
        /*printf("Y 0x%"PRIx64"\n", Y);*/
        /*B es el vector de 48 bits que va a ser dividido en 8 trozos de 6*/
        B = X ^ Y;

        SB[0] = SB_return(B);
        SB[1] = SB_return(X);
        SB[2] = SB_return(Y); 

        aux = SB[1] ^ SB[2];

        if(aux == SB[0]){
            counter ++;
            printf("LINEALIDAD en rep=%d\n", rep);
        }

    }

    printf("Numero de casos lineales = %d\n", counter);


    return 0;


}
