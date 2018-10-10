/***************************************************************************
utils.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <gmp.h>
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
 * @brief Realiza el producto escalar de 2 vectores
 * 
 * @param primer vector
 * @param segundo vector
 * @param tamaño de los vectores
 *
 * @return el resultado de la operacion
 */
int mult(int *fila, char *columna, int tam) {

    int res = 0, i = 0;

    for (i = 0; i < tam; i++) {
        /*printf("Fila es %d y columna es %d\n", fila[i], columna[i]);*/
        res += fila[i] * columna[i];
        /*printf("res es %d\n", res);*/
    }
    /* printf("RES FINAL es %d\n", res);*/
    return res;
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