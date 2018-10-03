/***************************************************************************
vigenere.c

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

/*Definicion de constantes *************************************************/

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

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[256];
    char cadena[256];
    char clave[256];
    int long_index = 0;
    char opt;
    FILE *fIn, *fOut;
    int n, i, m = 26;
    int cifrar = -1;

    if (argc > 1) {
        strncpy(entrada, argv[1], 256);
    } else {
        printf("Ejecucion: %s {-C|-D} {-k clave} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"k", required_argument, 0, '1'},
        {"i", required_argument, 0, '2'},
        {"o", required_argument, 0, '3'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "c:d:1:2:3", options, &long_index)) != -1) {
        switch (opt) {
            case 'c':
                cifrar = 1;
                break;

            case 'd':
                cifrar = 0;
                break;

            case '1':
                strncpy(clave, optarg, 256);
                break;

            case '2':
                fIn = fopen(optarg, "r");
                if (!fIn) exit(-1);
                break;

            case '3':
                fOut = fopen(optarg, "w");
                if (!fOut) exit(-1);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-C|-D} {-k clave} [-i filein] [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
    }
    /*Si no se ha especificado si cifrar o descifrar*/
    if (cifrar == -1) {
        printf("Ejecucion: %s {-C|-D} {-k clave} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }

    /*crear entrada estandar*/
    if (!fIn) {
        printf("Leyendo entrada estandar \n");
        fgets(cadena, 256, stdin);
        /*se guarda la entrada en un fichero para reutilizar codigo*/
        fIn = fopen("teclado.txt", "w");
        fwrite(cadena, 1, strlen(cadena), fIn);
        fclose(fIn);
        fIn = fopen("teclado.txt", "r");
    }

    /*leer fichero entrada o estandar*/
    if (fIn) {
        n = strlen(clave);
        while (fread(cadena, sizeof (char), n, fIn) != 0) {
            for (i = 0; i < n; i++) {
                /*convertir a mayusculas*/
                if ('a' <= cadena[i] && cadena[i] <= 'z') {
                    cadena[i] -= ('a' - 'A');
                }
                if ('A' <= cadena[i] && cadena[i] <= 'Z') {
                    cadena[i] -= 65;

                    /*Cifrar*/
                    if (cifrar == 1) {
                        cadena[i] += clave[i];
                    }/*Descifrar*/
                    else {
                        cadena[i] -= clave[i];
                    }
                    cadena[i] %= m;
                    cadena[i] += 65;
                }
                /*escribir fichero salida*/
                if (fOut) {
                    fwrite(cadena, sizeof(char), n, fOut);
                }/*escribir salida estandar*/
                else {
                    fwrite(cadena, sizeof(char), n, stdout);
                }
            }
        }

    }

    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;


}

