/***************************************************************************
utils.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/**
 * @brief Lee el fichero fIn las letras, y las pasa a mayusculas y les quita el acento.
 *  se escriben en fAux sólo los caracteres en mayuscula (ignora los espacios)
 * 
 * @param el fichero a parsear
 * @param el fichero de salida con el texto parseado
 *
 * @return el numero de letras escritas en fAux
 */
int parsear(FILE *fIn, FILE **fAux) {

    char simbolo_in;
    int count = 0;

    /*Limpiar texto de entrada con letras A-Z*/
    if (fIn) {
        *fAux = fopen("auxiliar.txt", "w");
        if (fAux) {
            while (fscanf(fIn, "%c", &simbolo_in) != EOF) {
                /*convertir a mayusculas*/
                if ('a' <= simbolo_in && simbolo_in <= 'z') {
                    simbolo_in -= ('a' - 'A');
                }/*quitamos los acentos*/
                else {
                    if (simbolo_in == -127 || simbolo_in == -95) simbolo_in = 'A';
                    else if (simbolo_in == -119 || simbolo_in == -87) simbolo_in = 'E';
                    else if (simbolo_in == -115 || simbolo_in == -83) simbolo_in = 'I';
                    else if (simbolo_in == -109 || simbolo_in == -77) simbolo_in = 'O';
                    else if (simbolo_in == -102 || simbolo_in == -70) simbolo_in = 'U';
                }

                if ('A' <= simbolo_in && simbolo_in <= 'Z') {
                    /*escribir fichero auxiliar de entrada*/
                    /*printf("Anadiendo a auxiliar \n");  */
                    fwrite(&simbolo_in, 1, 1, *fAux);
                    count++;
                }
            }
        }
    }
    /*fclose(*fAux);*/
    return count;
}

/**
 * @brief Calcula el maximo comun divisor
 *
 * @param primer entero
 * @param segundo entero
 *
 * @return el maximo comun divisor
 */
int mcd(int a, int b) {
    if (a == 0)
        return b;
    return mcd(b % a, a);
}

/**
 * @brief Calcula el maximo comun divisor para un array de valores
 *
 * @param tabla con los valores a calcular el mcd
 * @param tamaño de la tabla
 *
 * @return el maximo comun divisor
 */
int mcdRec(int*t, int n) {
    int i, gcd = 0;
    for (i = 0; i < n; i++) {
        gcd = mcd(gcd, t[i]);
    }
    return gcd;
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
int mcdExtended(int a, int m, int *x, int *y) {
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
}

/**
 * @brief Genera numeros aleatorios siguiendo una distribución normal
 *
 * @param media de la distribución
 * @param desviación típica
 * 
 * @return el número aleatorio
 */
double randn(double mu, double sigma) {
    double U1, U2, W, mult;
    static double X1, X2;
    static int call = 0;

    if (call == 1) {
        call = !call;
        return (mu + sigma * (double) X2);
    }

    do {
        U1 = -1 + ((double) rand() / RAND_MAX) * 2;
        U2 = -1 + ((double) rand() / RAND_MAX) * 2;
        W = pow(U1, 2) + pow(U2, 2);
    } while (W >= 1 || W == 0);

    mult = sqrt((-2 * log(W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;

    call = !call;

    return (mu + sigma * (double) X1);
}

/**
 * @brief Obtenemos el bit en una posición de una palabra
 *
 * @param palabra de donde sacamos el bit
 * @param posicion donde se lee el bit de izquierda a derecha [0, 63]
 * 
 * @return el bit leido
 */
uint8_t get_bit(uint64_t bits, uint8_t pos) {

    return ((bits >> (63 - pos)) & 0x01);
}

/**
 * @brief Obtenemos la palabra tras escribirle un bit en una posición
 *
 * @param palabra donde escribimos el bit
 * @param posicion donde se escribe el bit de izquierda a derecha [0, 63]
 * @param valor que se escribe en la posición (1 o 0)
 * 
 * @return la palabra modificada
 */
uint64_t set_bit(uint64_t bits, uint8_t pos, uint8_t value) {
    uint64_t mask = 1LL << (63 - pos);
    if (value)
        bits |= mask;
    else
        bits &= ~mask;
    return bits;
}

/**
 * @brief Hace una rotación circular a la izquierda de una palabra de 28b
 *
 * @param palabra que desplazamos
 * @param numero de posiciones que se desplaza
 * 
 * @return la palabra modificada
 */
uint64_t rotl(uint64_t value, unsigned int count) {
    return (value << count | value >> (28 - count)) & 0x0FFFFFFF;
}


/**
 * @brief Genera una cadena binaria aleatoria
 *
 * @param el tamaño de la cadena (max 64 bits)
 * 
 * @return la cadena aleatoria
 */
uint64_t cadena_aleatoria(int num){

    int i=0;
    uint64_t cadena = 0;
    uint8_t bit = 0;

    for(i=64-num; i<64; i++){
        bit= (uint8_t) (rand()%2);
        cadena = set_bit(cadena, (uint8_t) i, bit);
    }

    return cadena;
}

/**
 * @brief Cuenta el numero de unos de una cadena binaria
 *
 * @param la cadena de bits
 * 
 * @return el numero de unos
 */
int contar_unos(uint64_t cadena) { 

    int count = 0; 

    while (cadena) { 
        count += cadena & 1; 
        cadena >>= 1; 
    } 

    return count; 
} 