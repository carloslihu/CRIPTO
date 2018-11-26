/***************************************************************************
DES_tables.h

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#ifndef DES_TABLES_H
#define DES_TABLES_H

#include "../includes/utils.h"

/* Constantes para el DES */
#define BITS_IN_PC1 56
#define BITS_IN_PC2 48
#define ROUNDS 16
#define BITS_IN_IP 64
#define BITS_IN_E 48
#define BITS_IN_P 32
#define NUM_S_BOXES 8
#define ROWS_PER_SBOX 4
#define COLUMNS_PER_SBOX 16

/**
 * @brief Genera una clave de 64b con un bit de paridad impar en cada
 *        bit multiplo de 8
 * 
 * @return la clave
 */
uint64_t createKey();

/**
 * @brief Genera un vector de inicialización aleatorio sin restricciones
 * 
 * @return el vector de inicialización
 */
uint64_t createIV();
/**
 * @brief Genera las subclaves del DES a partir de la clave principal
 *
 * @param la clave principal
 * 
 * @return las subclaves generadas
 */
uint64_t* createSubkeys(uint64_t key);


/**
 * @brief Devuelve la salida de 4 bits de los 6 bits de entrada de la SBOX
 *
 * @param la 6 bits entrada
 * @param numero de SBOX
 * @param s_boxes a usar, si es NULL se usa la del DES
 * 
 * @return salida de la sbox, 4 bits
 */
uint8_t SBox_result(uint8_t b, unsigned int number_box, unsigned short s_boxes[NUM_S_BOXES][ROWS_PER_SBOX][COLUMNS_PER_SBOX]);

/**
 * @brief Funcion que calcula los valores de la SBoxes
 *
 * @param cadena de 48 bits que va a ser pasada por las SBoxes
 * @param s_boxes a usar, si es NULL se usa la del DES
 * 
 * @return valor de retorno de 32 bits de las SBoxes
 */
uint32_t SB_return(uint64_t B, unsigned short s_boxes[NUM_S_BOXES][ROWS_PER_SBOX][COLUMNS_PER_SBOX]);

/**
 * @brief Calcula la funcion f a partir de Rn-1 y Kn
 *
 * @param Rn-1 de 32b
 * @param clave Kn de 48b
 * 
 * @return resultado de f de 32b
 */
uint32_t f(uint32_t R, uint64_t Key);

/**
 * @brief Cifra un texto de 64 bits usando DES
 *
 * @param Mensaje de 64 bits a cifrar
 * @param el conjunto de claves generadas en step 1
 * @param 1 si estamos cifrando, 0 si descifrando
 * 
 * @return el texto de 64 bits cifrado
 */
uint64_t encode_block(uint64_t Mens, uint64_t* subkeys, int cifrar);

/**
 * @brief Cifra un texto de 64 bits usando DES, especial para ejercicio de avalancha
 *
 * @param Mensaje de 64 bits a cifrar
 * @param el clave
 * @param 1 si estamos cifrando, 0 si descifrando
 * @param puntero donde se guardarán los valores de cada ronda
 * 
 * @return el texto de 64 bits cifrado
 */
uint64_t encode_block_avalancha(uint64_t Mens, uint64_t key, int cifrar, uint64_t** rondas);

#endif /* DES_TABLES_H */