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
    srand(time(NULL));
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

    return 0;
}