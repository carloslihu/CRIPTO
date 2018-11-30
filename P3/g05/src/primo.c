/***************************************************************************
primo.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/**
 * @brief Realiza el algoritmo de Miller-Rabin para determinar si un numero 
 *        es primo o compuesto.
 *
 * @param el número a comprobar
 * @param el número de repeticiones del algoritmo
 * 
 * @return 2 si es definitivamente primo
 *         1 si puede ser primo
 *         0 si es compuesto
 */
int miller_rabin_test(const mpz_t n, int reps) {
    /*TODO CODIGO*/
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE]; //, cadena[SIZE];
    int long_index = 0;
    char opt;
    FILE *fOut = NULL;
    mpz_t num;
    gmp_randstate_t state;
    int sec, p;
    unsigned long bits;

    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s -b bits -t sec [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"b", required_argument, 0, '1'},
        {"t", required_argument, 0, '2'},
        {"o", required_argument, 0, '3'},
        {0, 0, 0, 0}
    };
    mpz_inits(num, NULL);
    while ((opt = getopt_long_only(argc, argv, "1:2:3", options, &long_index)) != -1) {
        switch (opt) {
            case '1':
                bits = strtoul(optarg, NULL, 10);
                break;
            case '2':
                sec = atoi(optarg);
                break;

            case '3':
                fOut = fopen(optarg, "w");
                if (!fOut) exit(-1);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s -b bits -t sec [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
    }

    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }
    /*Librería GMP*/
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));
    /*TODO iterar hasta que sea primo*/
    mpz_urandomb(num, state, bits);
    gmp_printf("Resultado: %Zd ", num);
    p = mpz_probab_prime_p(num, sec);
    if (p == 2) {
        printf("es primo seguro\n");
    } else if (p == 1) {
        printf("es primo probablemente\n");
    } else if (p == 0) {
        printf("es compuesto seguro\n");
    }

    if (fOut) fclose(fOut);
    mpz_clears(num, NULL);
    return 0;


}
