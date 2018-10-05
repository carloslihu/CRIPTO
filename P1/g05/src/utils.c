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
                }/*miramos si hay acentos*/
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