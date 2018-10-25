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
#include <time.h>

/*Definicion de constantes *************************************************/
#define M 26 /* tamaño del alfabeto */
#define TAM 1000000 /*tamaño para vectores en IC*/
#define K 65 /* desplazamiento para operar A-Z en Zm */
#define SIZE 512 /*tamaño de cadenas*/
#define ERROR 0.01 /*error tolerado para IC*/

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
 * @brief Calcula el maximo comun divisor
 *
 * @param primer entero
 * @param segundo entero
 *
 * @return el maximo comun divisor
 */
int mcd(int a, int b);

/**
 * @brief Calcula el maximo comun divisor para un array de valores
 *
 * @param tabla con los valores a calcular el mcd
 * @param tamaño de la tabla
 *
 * @return el maximo comun divisor
 */
int mcdRec(int*t, int n);

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

