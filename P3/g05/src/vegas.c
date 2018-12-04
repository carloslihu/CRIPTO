/***************************************************************************
vegas.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/**
 * @brief Realiza el algoritmo de las Vegas para determinar los factores primos
 *        p y q tal que n = p*q del algoritmo RSA. 
 *        Sabiendo la clave pública (n,e) y el exponente de descifrado d
 *
 * @param p primer factor primo resultado (vale 0 si el algoritmo no responde)
 * @param q segundo factor primo resultado (vale 0 si el algoritmo no responde)
 * @param d exponente de descifrado
 * @param e exponente de cifrado
 * @param n producto de p y q
 *
 */
void vegas(mpz_t p, mpz_t q, const mpz_t d, const mpz_t e, const mpz_t n) {
    mpz_t n_1, ed_1, m, a, x, y, gcd;
    gmp_randstate_t state;
    int i = 0, k = 1;

    mpz_inits(n_1, ed_1, m, a, x, y, gcd, NULL);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    //n_1 = n - 1
    mpz_sub_ui(n_1, n, 1);

    // ed-1 = 2^k * m
    mpz_mul(ed_1, e, d);
    mpz_sub_ui(ed_1, ed_1, 1);
    mpz_tdiv_q_ui(m, ed_1, 2);
    while (mpz_even_p(m)) {
        mpz_tdiv_q_ui(m, m, 2);
        k++;
    }
    /*1 < a < n-1*/
    //repetimos hasta que a sea mayor que 1
    do {
        //aqui generamos 0 <= a < n-1
        mpz_urandomm(a, state, n_1);
    } while (mpz_cmp_ui(a, 2) < 0);

    //Si (a,n) > 1
    mpz_gcd(gcd, a, n);
    if (mpz_cmp_ui(gcd, 1) > 0) {
        mpz_set(p, gcd);
        mpz_tdiv_q(q, n, p);
        mpz_clears(n_1, ed_1, m, a, x, y, gcd, NULL);
        return;
    }

    // x = a^m (mod n)
    powm(x, a, m, n);
    if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_1) == 0) {
        mpz_set_ui(p, 0);
        mpz_set_ui(q, 0);
        mpz_clears(n_1, ed_1, m, a, x, y, gcd, NULL);
        return;
    }
    for (i = 1; i < k; i++) {
        //y = x
        mpz_set(y, x);
        //x = (x^2 mod n)
        mpz_mul(x, x, x);
        mpz_mod(x, x, n);

        if (mpz_cmp_ui(x, 1) == 0) {
            mpz_add_ui(y, y, 1);
            mpz_gcd(p, y, n);
            mpz_tdiv_q(q, n, p);
            mpz_clears(n_1, ed_1, m, a, x, y, gcd, NULL);
            return;
        } else if (mpz_cmp(x, n_1) == 0) {
            mpz_set_ui(p, 0);
            mpz_set_ui(q, 0);
            mpz_clears(n_1, ed_1, m, a, x, y, gcd, NULL);
            return;
        }
    }
    //p = mcd(x+1, n)
    mpz_add_ui(x, x, 1);
    mpz_gcd(p, x, n);
    mpz_tdiv_q(q, n, p);
    mpz_clears(n_1, ed_1, m, a, x, y, gcd, NULL);
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE];
    int long_index = 0;
    char opt;
    mpz_t p, q, d, e, n;


    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s {-d descifrado} {-e encriptado} {-n numero}\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"d", required_argument, 0, '1'},
        {"e", required_argument, 0, '2'},
        {"n", required_argument, 0, '3'},
        {0, 0, 0, 0}
    };
    mpz_inits(p, q, d, e, n, NULL);
    while ((opt = getopt_long_only(argc, argv, "1:2:3", options, &long_index)) != -1) {
        switch (opt) {
            case '1':
                mpz_set_str(d, optarg, 10);
                break;

            case '2':
                mpz_set_str(e, optarg, 10);
                break;

            case '3':
                mpz_set_str(n, optarg, 10);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-d descifrado} {-e encriptado} {-n numero}\n", argv[0]);
                exit(-1);
                break;
        }
    }
    vegas(p, q, d, e, n);
    gmp_printf("Factores primos de %Zd:\n%Zd\n%Zd\n", n, p, q);
    mpz_clears(p, q, d, e, n, NULL);
    return 0;
}
