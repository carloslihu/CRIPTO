/***************************************************************************
key_gen.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE];
    int long_index = 0;
    char opt;
    mpz_t p, q, d, e, n, fi_n, gcd;
    gmp_randstate_t state;

    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s {-p primo} {-q primo}\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"p", required_argument, 0, '1'},
        {"q", required_argument, 0, '2'},
        {0, 0, 0, 0}
    };
    mpz_inits(p, q, d, e, n, fi_n, gcd, NULL);
    while ((opt = getopt_long_only(argc, argv, "1:2", options, &long_index)) != -1) {
        switch (opt) {
            case '1':
                mpz_set_str(p, optarg, 10);
                break;

            case '2':
                mpz_set_str(q, optarg, 10);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-p primo} {-q primo}\n", argv[0]);
                exit(-1);
                break;
        }
    }
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    //calculamos n
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    //calculamos fi_n
    mpz_mul(fi_n, p, q);

    /*1 < e < fi_n*/
    //repetimos hasta que e sea mayor que 1 y sea coprimo con fi_n
    do {
        //aqui generamos 0 <= e < fi_n
        mpz_urandomm(e, state, fi_n);
        mpz_gcd(gcd, e, fi_n);
    } while (mpz_cmp_ui(e, 2) < 0 || mpz_cmp_ui(gcd, 1) != 0);
    //d = (e)^-1 mod fi_n
    mpz_invert(d, e, fi_n);

    gmp_printf("\nn:\n%Zd\n\ne:\n%Zd\n\nd:\n%Zd\n", n, e, d);

    mpz_clears(p, q, d, e, n, fi_n, gcd, NULL);
    return 0;
}
