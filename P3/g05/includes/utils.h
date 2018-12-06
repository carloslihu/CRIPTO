/***************************************************************************
utils.h

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
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
 * @brief Calcula la potenciación modular rop=base^exp (mod mod)
 *
 * @param el resultado de la potenciación modular
 * @param la base de la potencia
 * @param el exponente de la potencia
 * @param el módulo
 * 
 */
void powm(mpz_t rop, const mpz_t base, const mpz_t exp, const mpz_t mod);
#endif /* UTILS_H */

