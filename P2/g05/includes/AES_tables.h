/***************************************************************************
AES_tables.h

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#ifndef AES_TABLES_H
#define AES_TABLES_H

#include "../includes/utils.h"

/* Constantes para el AES con clave de 128 bits */
#define BYTES_PER_WORD 4
#define ROWS_PER_SBOX 16
#define COLUMNS_PER_SBOX 16
#define HEX_STRING_SIZE 3
#define MX 0b100011011
#define C 0b01100011

uint64_t SB_AES_return(uint64_t B);

#endif /* AES_TABLES_H */