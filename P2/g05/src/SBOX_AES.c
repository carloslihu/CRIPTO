/***************************************************************************
SBOX_AES.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/AES_tables.h"

/**
 * @brief realiza el xtime del AES sobre 8b
 *
 * @param palabra a aplicar xtime
 *
 * @return resultado
 */
uint64_t xtime(uint64_t bits) {
    if (get_bit(bits, BSIZE - 8) == 1) {
        return bits << 1;
    } else {
        return ((bits << 1) & 0xFF) ^ 0x1B;
    }
}

/**
 * @brief realiza el producto de 2 polinomios del AES sobre 8b
 *
 * @param primer operando
 * @param primer operando
 *
 * @return resultado
 */
uint64_t AES_product(uint64_t a, uint64_t b) {
    uint64_t r, x;
    int min, max;
    int l_a, l_b, l_min, i;
    l_a = get_length(a);
    l_b = get_length(b);
    /*TODO esto era recursivo
     criterio para decidir cual hacer xtime?*/

    if (l_a < l_b) {
        min = a;
        max = b;
        l_min = l_a;
    } else {
        min = b;
        max = a;
        l_min = l_b;
    }
    x = max;
    if (get_bit(min, 63) == 1) {
        r = x;
    }
    for (i = 1; i < l_min; i++) {
        x = xtime(x);
        if (get_bit(min, 63 - i) == 1) {
            r ^= x;
        }
    }
    return r;
}

/**
 * @brief pasandole n y d, calcula n/d, dando como resultados
 * el cociente q y el resto r
 *
 * @param n dividendo de la division
 * @param d divisor de la division
 * @param q cociente de la división
 * @param r resto de la division 
 *
 */
void pol_division(const uint64_t n, const uint64_t d, uint64_t *q, uint64_t *r) {
    int l_d, l_n, l_dist;
    int i;
    l_d = get_length(d);
    l_n = get_length(n);
    l_dist = l_n - l_d;
    *q = 0;
    *r = n;
    /*Caso en que se pueda dividir*/
    if (l_dist >= 0) {
        *r = (n >> l_dist) ^ d;
        *q = 1;
        for (i = 1; i <= l_dist; i++) {
            /*a r le añadimos el siguiente termino del dividendo */
            *r = (*r << 1) | ((n >> (l_dist - i)) & 1);

            /*Caso longitud resto < longitud divisor*/
            if (get_length(*r) < l_d) {
                /*q le añadimos un 0*/
                *q <<= 1;
            } else {/*Caso longitud resto = longitud divisor*/
                *r = *r ^ d;
                *q = (*q << 1) | 1;
            }
        }
    }
}

/**
 * @brief Calcula el maximo comun divisor en GF(2⁸)
 *
 * @param primer polinomio
 * @param segundo polinomio
 *
 * @return el maximo comun divisor
 */
uint64_t AES_mcd(uint64_t a, uint64_t b) {
    uint64_t q, r;
    if (a == 0)
        return b;
    pol_division(b, a, &q, &r);
    return AES_mcd(r, a);
}

/**
 * @brief Realiza la descomposición de Euclides Extendida para polinomios.
 *        Calcula el inverso de a modulo m(x) del AES en x
 *
 * @param el polinomio a calcular su inverso
 * @param el inverso de a
 * @param el otro factor por descomposición
 *
 * @return el maximo comun divisor
 */

uint64_t AES_mcdExtended(uint64_t a, uint64_t m, uint64_t *x, uint64_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return m;
    }

    uint64_t q, r, x1, y1;
    pol_division(m, a, &q, &r);
    uint64_t mcd = AES_mcdExtended(r, a, &x1, &y1);
    /*TODO FDB nos ha colado un puto xtime D:*/
    //*x = y1 - q * x1;
    *y = x1;

    return mcd;
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE]; //, cadena[SIZE];
    int long_index = 0;
    char opt;
    FILE *fOut = NULL;
    int cifrar = -1;


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
        /*uint64_t n = 0b10011,
                d = 0b10111,
                q, r;
        pol_division(n, d, &q, &r);
        printf("q: %"PRIx64"\n"
                "r: %"PRIx64"\n", q, r);*/
        /*uint64_t n = 0b1011,
                d = 0b100,
                q, r;

        printf("n: %"PRIx64"\n"
                "d: %"PRIx64"\n"
                "mcd: %"PRIx64"\n", n, d, mcd(n, d));*/

        //uint64_t m = 0b100011011;

    }
    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }

    if (fOut) fclose(fOut);

    return 0;


}
