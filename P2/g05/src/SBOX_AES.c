/***************************************************************************
SBOX_AES.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/AES_tables.h"

/**
 * @brief Calcula el maximo comun divisor en GF(2⁸)
 *
 * @param primer polinomio
 * @param segundo polinomio
 *
 * @return el maximo comun divisor
 */
uint64_t AES_mcd(uint64_t a, uint64_t b) {
    uint64_t resto = 0;
    if (a == 0)
        return b;

    //return AES_mcd(b % a, a);
}
/**
 * @brief Realiza la descomposición de Euclides Extendida.
 *        Calcula el inverso de a modulo m en x
 *
 * @param el entero a calcular su inverso
 * @param el modulo de la operación
 * @param el inverso de a
 * @param el otro factor por descomposición
 *
 * @return el maximo comun divisor
 */
/*
int AES_mcdExtended(int a, int m, int *x, int *y) {
    if (a == 0) {
 *x = 0;
 *y = 1;
        return m;
    }

    int x1, y1;
    int mcd = mcdExtended(m % a, a, &x1, &y1);

 *x = y1 - (m / a) * x1;
 *y = x1;

    return mcd;
}*/

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE], cadena[SIZE];
    int long_index = 0;
    char opt;
    FILE *fOut = NULL;
    int cifrar = -1, i = 0;


    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s {-C | -D} [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"o", required_argument, 0, '1'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "c:d:1", options, &long_index)) != -1) {
        switch (opt) {
            case 'c':
                cifrar = 1;
                break;

            case 'd':
                cifrar = 0;
                break;

            case '1':
                fOut = fopen(optarg, "wb");
                if (!fOut) exit(-1);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-C | -D} [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
    }

    if (cifrar == 1) {
    }
    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }

    if (fOut) fclose(fOut);

    return 0;


}
