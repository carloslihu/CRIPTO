/***************************************************************************
utils.h

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/


#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <gmp.h>

/**
 * @brief Lee el fichero fIn las letras, y las pasa a mayusculas y les quita el acento.
 *  se escriben en fAux sólo los caracteres en mayuscula (ignora los espacios)
 * 
 * @param el fichero a parsear
 * @param el fichero de salida con el texto parseado
 *
 * @return el numero de letras escritas en fAux
 */
int parsear(FILE *fIn, FILE **fAux);

/**
 * @brief Realiza el producto escalar de 2 vectores
 * 
 * @param primer vector
 * @param segundo vector
 * @param tamaño de los vectores
 *
 * @return el resultado de la operacion
 */
int mult(int *fila, char *columna, int tam);

/**
 * @brief Calcula el maximo comun divisor
 *
 * @param primer entero
 * @param segundo entero
 *
 * @return el maximo comun divisor
 */
int mcd(int a, int b);

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
int mcdExtended(int a, int m, int *x, int *y);


#endif /* UTILS_H */

