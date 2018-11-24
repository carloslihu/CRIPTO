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
    if (get_bit(bits, (uint8_t) 56) == 1) {
        return ((bits << 1) & 0xFF) ^ 0x1B;
    } else {
        return bits << 1;
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
    uint64_t r = 0, x;
    int min, max;
    int l_a, l_b, l_min, i;
    l_a = get_length(a);
    l_b = get_length(b);

    /*Para optimizar el proceso, 
     * realizaremos xtime sobre la palabra de menor longitud*/
    if (l_a < l_b) {
        min = a;
        max = b;
        l_min = l_a;
    } else {
        min = b;
        max = a;
        l_min = l_b;
    }
    /*Término inicial antes de realizar xtime*/
    x = max;
    if (get_bit(min, 63) == 1) {
        r ^= x;
    }
    for (i = 1; i < l_min; i++) {
        x = xtime(x);
        /*Suma el término del xtime si aparece en min*/
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
    /*Caso en que no se pueda dividir (n ya es módulo d)*/
    if (l_dist < 0) {
        *q = 0;
        *r = n;
    } else {/*Caso en que se dividir*/
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
    uint64_t prod;
    if (a == 0) {
        *x = 0;
        *y = 1;
        return m;
    }

    uint64_t q, r, x1, y1;
    pol_division(m, a, &q, &r);
    uint64_t mcd = AES_mcdExtended(r, a, &x1, &y1);
    prod = AES_product(q, x1);
    *x = y1 ^ prod;
    *y = x1;

    return mcd;
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE]; //, cadena[SIZE];
    int long_index = 0;
    char opt;
    FILE *fOut = NULL;
    int cifrar = -1, i, j, k, l;
    uint64_t x, y;
    char DIRECT_SBOX_PROP[ROWS_PER_SBOX][COLUMNS_PER_SBOX][HEX_STRING_SIZE];
    char INVERSE_SBOX_PROP[ROWS_PER_SBOX][COLUMNS_PER_SBOX][HEX_STRING_SIZE];
    uint64_t s;
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
                fOut = fopen(optarg, "w");
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

    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }
    /*Calculamos ambas Sboxes a la vez*/
    for (i = 0; i < ROWS_PER_SBOX; i++) {
        for (j = 0; j < COLUMNS_PER_SBOX; j++) {
            /*concatenamos indices*/
            s = (i << 4) | j;
            /*calculamos el inverso de s*/
            AES_mcdExtended(s, MX, &x, &y);
            /*Aplicamos la matriz*/
            s = x ^ rotl8(x, 1) ^ rotl8(x, 2) ^ rotl8(x, 3) ^ rotl8(x, 4) ^ C;

            sprintf(DIRECT_SBOX_PROP[i][j], "%02x", (unsigned int) s);
            /*Asignamos la Sbox inversa asociada*/
            k = s >> 4;
            l = s & 0xF;
            sprintf(INVERSE_SBOX_PROP[k][l], "%02x", (i << 4) | j);
        }
    }
    /*Imprimimos la Sbox directa*/
    if (cifrar == 1) {
        for (i = 0; i < ROWS_PER_SBOX; i++) {
            for (j = 0; j < COLUMNS_PER_SBOX; j++) {
                printf("%s ", DIRECT_SBOX_PROP[i][j]);
            }
            printf("\n");
        }
        /*Imprimimos la Sbox Inversa*/
    } else {
        for (i = 0; i < ROWS_PER_SBOX; i++) {
            for (j = 0; j < COLUMNS_PER_SBOX; j++) {
                printf("%s ", INVERSE_SBOX_PROP[i][j]);
            }
            printf("\n");
        }
    }

    if (fOut) fclose(fOut);

    return 0;


}
