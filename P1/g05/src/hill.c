/***************************************************************************
hill.c

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

/*Definicion de constantes *************************************************/

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[256];
    char cadena[256];
    int long_index = 0; //, retorno = 0;
    char opt, simbolo_out, fill = 'W';
    FILE *fIn = NULL, *fOut = NULL, *fK = NULL, *fAux = NULL;
    int cifrar = -1, resultado = 0, inv = 0, muda = 0;
    int matrix[3][3] = {0}, inversa[3][3] = {0}, adjunta[3][3] = {0};
    int m = 0, n = 0, count = 0, i = 0, j = 0, det = 0;

    if (argc > 1) {
        strncpy(entrada, argv[1], 256);
    } else {
        printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-n NK} {-k fileK} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"m", required_argument, 0, '1'},
        {"n", required_argument, 0, '2'},
        {"k", required_argument, 0, '3'},
        {"i", required_argument, 0, '4'},
        {"o", required_argument, 0, '5'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "c:d:1:2:3:4:5", options, &long_index)) != -1) {
        switch (opt) {
            case 'c':
                cifrar = 1;
                break;

            case 'd':
                cifrar = 0;
                break;

            case '1':
                m = atoi(optarg);
                break;

            case '2':
                n = atoi(optarg);
                if (n < 1 || n > 3) {
                    printf("El tamano n de matriz debe estar en el rango [1,3]\n");
                    exit(-1);
                }
                break;

            case '3':
                fK = fopen(optarg, "r");
                if (!fK) exit(-1);
                break;

            case '4':
                fIn = fopen(optarg, "r");
                if (!fIn) exit(-1);
                break;

            case '5':
                fOut = fopen(optarg, "w");
                if (!fOut) exit(-1);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-n NK} {-k fileK} [-i filein] [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
    }
    //Si no se ha especificado si cifrar o descifrar
    if (cifrar == -1) {
        printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-n NK} {-k fileK} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }



    /*leer fichero claves*/
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (!fscanf(fK, "%d", &matrix[i][j]))
                break;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    fclose(fK);


    /*Calculo de determinante*/
    if (n == 1) {
        det = matrix[0][0];
    } else if (n == 2) {
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] - matrix[1][0];
    } else if (n == 3) {
        det = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[1][0] * matrix[2][1] * matrix[0][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[2][1] * matrix[1][2] * matrix[0][0] - matrix[1][0] * matrix[0][1] * matrix[2][2];
    } else {
        printf("La matriz de claves no puede superar 3x3\n");
        exit(-1);
    }

    if (det == 0) {
        printf("La clave no puede tener determinante 0 \n");
        exit(-1);
    }

    printf("El determinante es %d\n", det);
    mcdExtended(det, m, &inv, &muda);

    if (mcd(m, det) != 1) {
        printf("La clave no determina una función inyectiva\n");
        exit(-1);
    }/*calculo de la inversa*/
    else {
        if (n == 1) {
            inversa[0][0] = inv;
        } else if (n == 2) {
            inversa[0][0] = matrix[1][1];
            inversa[1][1] = matrix[0][0];
            inversa[0][1] = -matrix[0][1] % m;
            if (inversa[0][1] < 0) inversa[0][1] += m;
            inversa[1][0] = -matrix[1][0] % m;
            if (inversa[1][0] < 0) inversa[1][0] += m;
        } else if (n == 3) {
            /*calculamos la adjunta de la matriz*/
            adjunta[0][0] =   matrix[1][1]*matrix[2][2] - matrix[2][1]*matrix[1][2];
            adjunta[0][1] = -(matrix[1][0]*matrix[2][2] - matrix[2][0]*matrix[1][2]);
            adjunta[0][2] =   matrix[1][0]*matrix[2][1] - matrix[2][0]*matrix[1][1];
            adjunta[1][0] = -(matrix[0][1]*matrix[2][2] - matrix[2][1]*matrix[0][2]);
            adjunta[1][1] =   matrix[0][0]*matrix[2][2] - matrix[2][0]*matrix[0][2];
            adjunta[1][2] = -(matrix[0][0]*matrix[2][1] - matrix[2][0]*matrix[0][1]);
            adjunta[2][0] =   matrix[0][1]*matrix[1][2] - matrix[1][1]*matrix[0][2];
            adjunta[2][1] = -(matrix[0][0]*matrix[1][2] - matrix[1][0]*matrix[0][2]);
            adjunta[2][2] =   matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];


            /*traspuesta y multiplicar por el inverso*/
            for(i=0; i<3 ; i++) {
                for(j=0; j<3 ; j++) {
                    inversa[i][j] = (adjunta[j][i]*inv)%m;
                    if(inversa[i][j]<0) inversa[i][j] += m;
                }
            }

        }
    }

    /*crear entrada estandar*/
    if (!fIn) {
        printf("Leyendo entrada estandar \n");
        fgets(cadena, 256, stdin);
        fIn = fopen("teclado.txt", "w");
        fwrite(cadena, 1, strlen(cadena), fIn);
        fclose(fIn);
        fIn = fopen("teclado.txt", "r");
    }


    /*rellenar texto para hacerlo modulo N*/
    /*en fAux se guarda la direccion del texto nuevo parseado*/
    count = parsear(fIn, &fAux);
    /*printf("Retorno count es %d\n", count);*/
    count = count % n;
    /*fAux  = fopen("auxiliar.txt", "a");*/
    for (i = 0; i < n - count && count != 0; i++) fwrite(&fill, 1, 1, fAux);
    fclose(fAux);
    fIn = fopen("auxiliar.txt", "r");

    /*leer fichero entrada o estandar*/
    if (fIn) {
        while (fread(cadena, sizeof (char), n, fIn) != 0) {
            /*convertir a formatao 0,...,n-1*/
            for (i = 0; i < n; i++) {
                cadena[i] -= 65;
                /*printf("Simbolo in: %d \n", cadena[i]);*/
            }

            for (i = 0; i < n; i++) { 
                /*Cifrar*/
                if (cifrar == 1) {
                    resultado = mult(matrix[i], cadena, n);
                }/*Descifrar*/
                else {
                    resultado = mult(inversa[i], cadena, n);
                }
                /*printf("RES tras mult: %d \n",resultado);*/
                simbolo_out = resultado % m;
                /*printf("Simbolo out tras mult: %d \n",simbolo_out);*/
                /*modulos con resultado de operacion negativa*/
                if (simbolo_out < 0) simbolo_out += m;
                /*printf("Simbolo out tras modulo: %d \n", simbolo_out);*/
                simbolo_out += 65;
                /*escribir fichero salida*/
                if (fOut) {
                    fwrite(&simbolo_out, 1, 1, fOut);
                }/*escribir salida estandar*/
                else {
                    fwrite(&simbolo_out, 1, 1, stdout);
                }
            }

        }

    }

    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;


}

