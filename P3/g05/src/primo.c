/***************************************************************************
primo.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"
#define PSIZE 303 /*numero de primos menores que 2000*/
#define COMPUESTO 0
#define POSIBLE_PRIMO 1
#define PRIMO 2

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
    mpz_t n_1, m, a, x;
    gmp_randstate_t state;
    int i = 0, j = 0, k = 1, p_flag;

    mpz_inits(n_1, m, a, x, NULL);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));
    
    // n-1 = 2^k * m
    mpz_sub_ui(n_1, n, 1);
    mpz_tdiv_q_ui(m, n_1, 2);
    while (mpz_even_p(m)) {
        mpz_tdiv_q_ui(m, m, 2);
        k++;
    }
    /*Pasamos el test reps veces*/
    for (i = 0; i < reps; i++) {
        p_flag = 0;
        /*1 < a < n-1*/
        mpz_urandomm(a, state, n);
        powm(x, a, n_1, n);
        if ((mpz_cmp_ui(x, 1) == 0) || (mpz_cmp(x, n_1) == 0)) {
            continue;
        }
        for (j = 1; j < k; j++) {
            mpz_mul(x, x, x);
            mpz_mod(x, x, n);
            if (mpz_cmp_ui(x, 1) == 0) {
                return COMPUESTO;
            } else if (mpz_cmp(x, n_1) == 0) {
                p_flag = 1;
                break;
            }
        }
        if (p_flag == 1) {
            continue;
        }
        return COMPUESTO;
    }
    mpz_clears(n_1, m, a, x, NULL);
    return POSIBLE_PRIMO;
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE];
    int long_index = 0;
    char opt;
    FILE *fOut = NULL;
    mpz_t num;
    gmp_randstate_t state;
    int sec, p;
    unsigned long bits;
    unsigned int primes[PSIZE] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999};
    int i = 0, p_flag = false;
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

    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    /*TODO iterar hasta que sea primo*/
    while (p_flag == false) {
        p_flag = true;
        /*Generamos num un numero aleatorio de bits*/
        mpz_urandomb(num, state, bits);
        mpz_setbit(num, bits - 1);
        mpz_setbit(num, 0);
        for (i = 0; i < PSIZE; i++) {
            /*si no es primo*/
            if (mpz_fdiv_ui(num, primes[i]) == 0) {
                p_flag = false;
                break;
            }
        }
        if (p_flag == false) {
            continue;
        }
        /*Si nos devuelve compuesto repetimos*/
        if (miller_rabin_test(num, sec) == COMPUESTO)
            continue;
    }
    gmp_printf("%Zd\nTEST: POSIBLE_PRIMO\nGMP: ", num);
    p = mpz_probab_prime_p(num, sec);
    if (p == PRIMO) {
        printf("PRIMO\n");
    } else if (p == POSIBLE_PRIMO) {
        printf("POSIBLE_PRIMO\n");
    } else if (p == COMPUESTO) {
        printf("COMPUESTO\n");
    }

    if (fOut) fclose(fOut);
    mpz_clears(num, NULL);
    return 0;


}
