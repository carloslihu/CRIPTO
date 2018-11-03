/***************************************************************************
DES_tables.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/
#include "../includes/DES_tables.h"

/* "permutaci�n" PC1 */
static const unsigned short PC1[BITS_IN_PC1] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

/* "permutaci�n" PC2 */
static const unsigned short PC2[BITS_IN_PC2] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

/* n�mero de bits que hay que rotar cada semiclave seg�n el n�mero de ronda */
static const unsigned short ROUND_SHIFTS[ROUNDS] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

/* permutaci�n IP */
static const unsigned short IP[BITS_IN_IP] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

/* inversa de IP */
static const unsigned short IP_INV[BITS_IN_IP] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

/* expansi�n E */
static const unsigned short E[BITS_IN_E] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

/* permutaci�n P */
static const unsigned short P[BITS_IN_P] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};

/* cajas S */
static const unsigned short S_BOXES[NUM_S_BOXES][ROWS_PER_SBOX][COLUMNS_PER_SBOX] = {
    {
        { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },

    {
        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },

    {
        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

/**
 * @brief Genera las subclaves del DES a partir de la clave principal
 *
 * @param la clave principal
 * 
 * @return las subclaves generadas
 */
uint64_t* createSubkeys(uint64_t key) {
    uint64_t* subkeys;
    uint64_t key_plus = 0, CD[16] = {0};
    uint64_t C[17] = {0}, D[17] = {0};
    int i = 0, j = 0;
    /*Inicializamos las variables*/
    subkeys = (uint64_t*) calloc(16, sizeof (uint64_t));
    for (i = 0; i < 16; i++) {
        subkeys[i] = 0;
    }
    /*Creamos K+ (56b) a partir de la clave K y PC-1*/
    for (i = 0; i < BITS_IN_PC1; i++) {
        //printf("%" PRIx8 "\n", get_bit(key, PC1[i] - 1));
        key_plus = set_bit(key_plus, i + 8, get_bit(key, PC1[i] - 1));
    }
    //printf("%" PRIx64 "\n", key_plus);
    /* Generamos las subclaves C0(28b) y D0(28b) separando por la mitad K+*/
    for (i = 0; i < (BITS_IN_PC1 / 2); i++) {
        C[0] = set_bit(C[0], i + 64 - 28, get_bit(key_plus, i + 8));
        D[0] = set_bit(D[0], i + 64 - 28, get_bit(key_plus, i + 8 + 28));
    }
    //printf("%" PRIx32 "\n%" PRIx32 "\n", C[0], D[0]);
    /*Generamos C1,...,C16 y D1,...,D16 (de 28b) haciendo rotaciones circulares*/
    for (i = 0; i < ROUNDS; i++) {
        C[i + 1] = rotl(C[i], ROUND_SHIFTS[i]);
        D[i + 1] = rotl(D[i], ROUND_SHIFTS[i]);
        //printf("C%d: %" PRIx64 "\nD%d:%" PRIx64 "\n", i + 1, C[i + 1], i + 1, D[i + 1]);
    }
    /*Concatenamos los C y D en CD (56b), y permutamos CD usando PC-2
     para generar las subclaves (48b)*/
    for (i = 0; i < ROUNDS; i++) {
        CD[i] = (C[i + 1] << 28) | D[i + 1];
        //printf("CD%d: %" PRIx64 "\n", i, CD[i]);
        for (j = 0; j < BITS_IN_PC2; j++) {
            subkeys[i] = set_bit(subkeys[i], j + (64 - 48), get_bit(CD[i], PC2[j] + (64 - 56) - 1));
        }
        //printf("K%d: %" PRIx64 "\n", i, subkeys[i]);
    }
    return subkeys;
} 

uint32_t f(uint32_t R, uint64_t Key){

    uint64_t EE = 0, B = 0, aux3 = 0, aux4 = 0; 
    uint32_t SB = 0, aux2 = 0, efe = 0;
    uint8_t bit = 0, aux = 0, b[NUM_S_BOXES] = {0}, sb[NUM_S_BOXES] = {0};
    int i=0;
    unsigned short fila = 0, columna = 0;

    /*printf("R 0x%"PRIx32"\n", R);
    printf("K 0x%"PRIx64"\n", Key);*/

    B = (uint64_t)R << 32;
    /*printf("B 0x%"PRIx64"\n", B);*/

    for(i=0; i<BITS_IN_E; i++){
        bit = get_bit(B, (uint8_t) E[i]-1);
        EE = set_bit(EE, (uint8_t) i, bit);
    }
    /*convertimos a 48 bits, quitando los ultimos 4 0s*/
    EE = EE >> 16;
    /*printf("E 0x%"PRIx64"\n", EE);*/
    B = Key ^ EE;
    /*printf("E+K 0x%"PRIx64"\n", B);*/

    /*calculo de SBoxes*/
    /*NUM_S_BOXES 8 ROWS_PER_SBOX 4 COLUMNS_PER_SBOX 16*/
    /*tenemos que separar B en 8 bloques de 6 bits*/
    for(i=0; i<NUM_S_BOXES; i++){
        aux = 0;
        b[i] = B >> 6*(8-(i+1));
        b[i] = b[i] & 0b00111111;
        /*printf("b%d 0x%"PRIx8"\n", i+1, b[i]);*/
        /*De cada Bi sacamos la fila y la columna con los correspondientes bits*/
        /*sacar fila*/
        bit = get_bit((uint64_t)b[i], (uint8_t) 58);
        aux = set_bit(aux, (uint8_t) 62, bit);
        bit = get_bit((uint64_t)b[i], (uint8_t) 63);
        aux = set_bit(aux, (uint8_t) 63, bit);
        /*printf("auxf%i 0x%"PRIx8"\n", i+1, aux);*/
        fila = (unsigned short) aux;
        /*printf("fila%i %d\n", i+1, fila);*/
        /*sacar columna*/
        aux = b[i] >> 1;
        aux = aux & 0b00001111;
        /*printf("auxc%i 0x%"PRIx8"\n", i+1, aux);*/
        columna = (unsigned short) aux;
        /*printf("columna%i %d\n", i+1, columna);*/

        /*consultamos la tabla SBoxes*/
        sb[i] = S_BOXES[i][fila][columna];
        /*printf("sb%d 0x%"PRIx8"\n", i+1, sb[i]);*/
    }
    /*juntamos los sbi para formar SB de 32 bits*/
    for(i=0; i<NUM_S_BOXES; i++){
        aux2 = (uint32_t) sb[i];
        SB = SB | (aux2<<(4*(7-i)));
    }
    /*printf("SB 0x%"PRIx32"\n", SB);*/

    aux3 = ((uint64_t) SB) << 32;

    for(i=0; i<BITS_IN_P; i++){
        bit = get_bit(aux3, (uint8_t) P[i]-1);
        aux4 = set_bit(aux4, (uint8_t) i, bit);
    }
    efe = (uint32_t) (aux4 >> 32);
    /*printf("F 0x%"PRIx32"\n", efe);*/

    return efe;
}

uint64_t encode_block(uint64_t Mens, uint64_t* subkeys){

    uint64_t ip, aux, C = 0;
    uint32_t L[17] = {0}, R[17] = {0}, efe = 0;
    uint8_t bit;
    int i = 0;

    /*en M guardamos los primeros 64 bits*/
    /*creamos IP a partir de M con las permutaciones de la tabla IP*/
    for(i=0; i<BITS_IN_IP; i++){
        bit = get_bit(Mens, (uint8_t) IP[i]-1);
        ip = set_bit(ip, (uint8_t) i, bit);
    }
    /*printf("IP 0x%"PRIx64"\n", ip);*/

    /*separamos ip en L0 y R0, de 32 bits cada una*/
    L[0] = ip >> 32;
    aux = ip << 32;
    R[0] = aux >> 32;
    /*printf("L0 0x%"PRIx32"\n", L[0]);
    printf("R0 0x%"PRIx32"\n", R[0]);*/

    for(i=1; i<=ROUNDS; i++){
        L[i] = R[i-1];
        /*printf("L%d 0x%"PRIx32"\n",i, L[i]);*/
        /*el indice de las subclaves K va de 0 a 15*/
        efe = f(R[i-1], subkeys[i-1]);
        /*printf("EFE 0x%"PRIx32"\n", efe);*/
        R[i] = L[i-1] ^ efe;
        /*printf("R%d 0x%"PRIx32"\n", i, R[i]);*/
    }

    /*cambiamos de orden L16R16 para formar R16L16*/
    aux = (((uint64_t)R[16]) << 32) | L[16];
    /*printf("R16L16 0x%"PRIx64"\n", aux);*/

    /*permutamos L16R16 con IP^-1*/
    for(i=0; i<BITS_IN_IP; i++){
        bit = get_bit(aux, (uint8_t) IP_INV[i]-1);
        C = set_bit(C, (uint8_t) i, bit);
    }
    /*printf("C 0x%"PRIx64"\n", C);*/

    return C;
}
