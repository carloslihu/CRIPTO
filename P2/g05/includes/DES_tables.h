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
 * @param 1 si estamos ifrando, 0 si descifrando
 * 
 * @return el texto de 64 bits cifrado
 */
uint64_t encode_block(uint64_t Mens, uint64_t* subkeys, int cifrar);

#endif /* DES_TABLES_H */