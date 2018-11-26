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


    /*realizamos tantas repeticiones como N*/
    for (rep = 0; rep < N; rep++) {
        /*Generamos vectores aleatorios X, Y de 64 bits. Debemos comprobar que f(X + Y) != f(X) + f(Y) */
        X = cadena_aleatoria(64);
        Y = cadena_aleatoria(64);
        /*B es el vector de 64 bits que va a ser dividido en 8 trozos de 8*/
        B = X ^ Y;

        /*Resultado de SBOX de X+Y*/
        SB[0] = SB_AES_return(B);
        /*Resultado de SBOX de X*/
        SB[1] = SB_AES_return(X);
        /*Resultado de SBOX de Y*/
        SB[2] = SB_AES_return(Y);
        
        /*Resultado sbox(X) xor sbox(Y)*/
        aux = SB[1] ^ SB[2];

        /*Comparamos ambos resultados, para ver que si coinciden (no deberian)*/
        if (aux == SB[0]) {
            counter++;
            printf("LINEALIDAD en rep=%d\n", rep);
        }

    }

    /*Resultados de la prueba*/
    printf("Casos probados = %d\n", N);
    printf("Numero de casos lineales = %d\n", counter);


    return 0;


}
