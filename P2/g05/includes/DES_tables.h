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

uint64_t createKey();
uint64_t createIV();
/**
 * @brief Genera las subclaves del DES a partir de la clave principal
 *
 * @param la clave principal
 * 
 * @return las subclaves generadas
 */
uint64_t* createSubkeys(uint64_t key);
uint64_t encode_block(uint64_t Mens, uint64_t* subkeys, int cifrar);
#endif /* DES_TABLES_H */