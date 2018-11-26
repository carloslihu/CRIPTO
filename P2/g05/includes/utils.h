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
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

/*Definicion de constantes *************************************************/
#define M 26 /* tamaño del alfabeto */
#define TAM 1000000 /*tamaño para vectores en IC*/
#define K 65 /* desplazamiento para operar A-Z en Zm */
#define SIZE 512 /*tamaño de cadenas*/
#define ERROR 0.01 /*error tolerado para la generación de SBOXES del DES*/
#define BSIZE 64 /*Tamaño en bits de los bloques*/


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

/**
 * @brief Genera numeros aleatorios siguiendo una distribución normal
 *
 * @param media de la distribución
 * @param desviación típica
 * 
 * @return el número aleatorio
 */
double randn(double mu, double sigma);

/**
 * @brief Obtenemos el bit en una posición de una palabra
 *
 * @param palabra de donde sacamos el bit
 * @param posicion donde se lee el bit de izquierda a derecha [0, 63]
 * 
 * @return el bit leido
 */
uint8_t get_bit(uint64_t bits, uint8_t pos);

/**
 * @brief Obtenemos la palabra tras escribirle un bit en una posición
 *
 * @param palabra donde escribimos el bit
 * @param posicion donde se escribe el bit de izquierda a derecha [0, 63]
 * @param valor que se escribe en la posición (1 o 0)
 * 
 * @return la palabra modificada
 */
uint64_t set_bit(uint64_t bits, uint8_t pos, uint8_t value);

/**
 * @brief Hace una rotación circular a la izquierda de una palabra de 28b
 *
 * @param palabra que desplazamos
 * @param numero de posiciones que se desplaza
 * 
 * @return la palabra modificada
 */
uint64_t rotl(uint64_t value, unsigned int count);

/**
 * @brief Hace una rotación circular a la izquierda de una palabra de 8b
 *
 * @param palabra que desplazamos
 * @param numero de posiciones que se desplaza
 * 
 * @return la palabra modificada
 */
uint64_t rotl8(uint64_t value, unsigned int count);

/**
 * @brief Genera una cadena binaria aleatoria
 *
 * @param el tamaño de la cadena (max 64 bits)
 * 
 * @return la cadena aleatoria
 */
uint64_t cadena_aleatoria(int num);


/**
 * @brief Cuenta el numero de unos de una cadena binaria
 *
 * @param la cadena de bits
 * 
 * @return el numero de unos
 */
int contar_unos(uint64_t cadena);
/**
 * @brief Devuelve la longitud real en bits de una palabra
 *
 * @param la palabra
 * 
 * @return su longitud
 */
int get_length(uint64_t bits);

#endif /* UTILS_H */

