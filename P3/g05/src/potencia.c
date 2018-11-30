/***************************************************************************
potencia.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"


/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE]; //, cadena[SIZE];
    int long_index = 0;
    char opt;
    mpz_t base, exp, mod, pot;

    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s -b base -e exponente -m modulo\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"b", required_argument, 0, '1'},
        {"e", required_argument, 0, '2'},
        {"m", required_argument, 0, '3'},
        {0, 0, 0, 0}
    };
    mpz_inits(base, exp, mod, pot, NULL);
    while ((opt = getopt_long_only(argc, argv, "1:2:3", options, &long_index)) != -1) {
        switch (opt) {
            case '1':
                mpz_set_str(base, optarg, 10);
                break;

            case '2':
                mpz_set_str(exp, optarg, 10);
                break;

            case '3':
                mpz_set_str(mod, optarg, 10);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s -b base -e exponente -m modulo\n", argv[0]);
                exit(-1);
                break;
        }
    }
    mpz_powm(pot, base, exp, mod);
    gmp_printf ("El resultado de la potenciación con GMP es %Zd\n", pot);
    mpz_clears(base, exp, mod, pot, NULL);
    return 0;


}
