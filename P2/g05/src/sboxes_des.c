/***************************************************************************
sboxes_des.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/DES_tables.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    unsigned short S_BOXES_PROP[NUM_S_BOXES][ROWS_PER_SBOX][COLUMNS_PER_SBOX];
    int i = 0, j = 0, k = 0, l = 0;
    unsigned short temp;

    int rep = 0;
    uint64_t X = 0, Y = 0;
    uint64_t B = 0;
    uint32_t SB[3] = {0}, aux = 0;
    int counter = 1, N = 1000, iter = 0;

    int r = 0, s = 0, cajas = 0;
    double unos[32] = {0}, ceros[32] = {0};
    double ceros_b[4] = {0};
    double pares_ceros[4][4] = {0};
    uint64_t cadena = 0, cadena2 = 0;
    uint32_t SB2 = 0;
    double repeticiones = 1000, media = 0;
    uint8_t b = 0, sb = 0;

    srand(time(NULL));
    while (counter != 0) {
        counter = 0;
        iter++;
        /*Generamos las Sboxes aleatorias*/
        for (i = 0; i < NUM_S_BOXES; i++) {
            for (j = 0; j < ROWS_PER_SBOX; j++) {
                /*Generamos elementos aleatorios entre 0 y 15 sin repetición
                 y en un orden aleatorio*/
                for (k = 0; k < COLUMNS_PER_SBOX; k++) {
                    S_BOXES_PROP[i][j][k] = k;
                }
                for (k = 0; k < COLUMNS_PER_SBOX; k++) {
                    l = (rand() % COLUMNS_PER_SBOX);
                    temp = S_BOXES_PROP[i][j][k];
                    S_BOXES_PROP[i][j][k] = S_BOXES_PROP[i][j][l];
                    S_BOXES_PROP[i][j][l] = temp;
                }
            }
        }
        /*------------- LINEALIDAD -------------*/
        for (rep = 0; rep < N; rep++) {
            /*Generamos vectores aleatorios X, Y de 48 bits. Debemos comrprobar que f(X + Y) != f(X) + f(Y) */

            X = cadena_aleatoria(48);
            Y = cadena_aleatoria(48);
            /*B es el vector de 48 bits que va a ser dividido en 8 trozos de 6*/

            SB[0] = SB_return(B, S_BOXES_PROP);
            SB[1] = SB_return(X, S_BOXES_PROP);
            SB[2] = SB_return(Y, S_BOXES_PROP);

            aux = SB[1] ^ SB[2];

            if (aux == SB[0]) {
                counter++;
                printf("LINEALIDAD en rep=%d\n", rep);
            }
        }
        if (counter > 0) {
            continue;
        }
        /*------------- SAC -------------*/

        for (i = 0; i < repeticiones; i++) {
            cadena = cadena_aleatoria(48);
            /* 000001 000001 000001 000001 000001 000001 000001 000001 = 0x41041041041*/
            cadena2 = cadena ^ 0x41041041041; /*cambiamos un bit de cada una de las 8 cajas de 6 bits*/

            SB2 = SB_return(cadena2, S_BOXES_PROP);

            /*contamos los unos y los ceros de cada una de las posiciones bi de la salida de las SBoxes*/
            for (j = 0; j < 32; j++) {
                if (get_bit((uint64_t) SB2, (uint8_t) (j + 32)) == 0) ceros[j]++;
                else unos[j]++;
            }
        }

        for (media = 0, j = 0; j < 32; j++) {
            media += unos[j] / repeticiones;
            unos[j] = 0;
        }
        media /= 32;
        if (fabs(media - 0.5) > ERROR) {
            counter = 1;
            continue;
        }
        /*------------- BIC -------------*/

        /*iteramos por cada caja*/
        for (cajas = 0; cajas < 8; cajas++) {
            /*numero de repeticiones fijadas*/
            for (i = 0; i < repeticiones; i++) {
                b = (uint8_t) cadena_aleatoria(6);
                sb = SBox_result(b, cajas, S_BOXES_PROP);

                /*comprobamos los ceros en cada bi, deberian ser la mitad (1/2)*/
                for (j = 0; j < 4; j++) {
                    if (get_bit((uint64_t) sb, (uint8_t) (j + 60)) == 0) ceros_b[j]++;
                }
                /*calculamos ceros conjuntos, por cada par, deberia ser (1/4)*/
                for (r = 0; r < 4; r++) {
                    for (s = r + 1; s < 4; s++) {
                        if (get_bit((uint64_t) sb, (uint8_t) (r + 60)) == 0 && get_bit((uint64_t) sb, (uint8_t) (s + 60)) == 0) pares_ceros[r][s]++;
                    }
                }

            }

            /*probabilidades simples*/
            for (media = 0, r = 0; r < 4; r++) {
                media += ceros_b[r] / repeticiones;
                ceros_b[r] = 0;
            }
            media /= 4;
            if (fabs(media - 0.5) > ERROR) {
                counter = 1;
                continue;
            }
            /*probabilidades conjuntas*/
            for (media = 0, r = 0; r < 4; r++) {
                for (s = r + 1; s < 4; s++) {
                    media += pares_ceros[r][s] / repeticiones;
                    pares_ceros[r][s] = 0;
                }
            }
            media /= 6;
            if (fabs(media - 0.25) > ERROR) {
                counter = 1;
                break;
            }
        }
        if (fabs(media - 0.25) > ERROR) {
            counter = 1;
            continue;
        }
    }
    printf("Tras %d iteraciones\n", iter);
    /*Imprimimos las Sboxes que ha pasado las pruebas*/
    for (i = 0; i < NUM_S_BOXES; i++) {
        printf("SBOX %d:\n", i);
        for (j = 0; j < ROWS_PER_SBOX; j++) {
            printf("Fila %d: ", j);
            for (k = 0; k < COLUMNS_PER_SBOX; k++) {
                printf("%hu ", S_BOXES_PROP[i][j][k]);
            }
            printf("\n");
        }
    }
    return 0;
}