/***************************************************************************
vigenere.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[256];
    char cadena[256];
    char clave[256];
    int long_index = 0;
    char opt, fill = 'W';
    FILE *fIn, *fOut, *fAux;
    int n, i, m;
    int cifrar = -1, count = 0;

    if (argc > 1) {
        strncpy(entrada, argv[1], 256);
    } else {
        printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-k clave} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"m", required_argument, 0, '1'},
        {"k", required_argument, 0, '2'},
        {"i", required_argument, 0, '3'},
        {"o", required_argument, 0, '4'},
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
                m = atoi(optarg);
                break;

            case '2':
                strncpy(clave, optarg, 256);
                break;

            case '3':
                fIn = fopen(optarg, "r");
                if (!fIn) exit(-1);
                break;

            case '4':
                fOut = fopen(optarg, "w");
                if (!fOut) exit(-1);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-k clave} [-i filein] [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
    }
    n = strlen(clave);
    /*Si no se ha especificado si cifrar o descifrar*/
    if (cifrar == -1) {
        printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-k clave} [-i filein] [-o fileout]\n", argv[0]);
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
    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }
    /*rellenar texto para hacerlo modulo N*/
    /*en fAux se guarda la direccion del texto nuevo parseado*/
    count = parsear(fIn, &fAux);
    count = count % n;
    for (i = 0; i < n - count && count != 0; i++) fwrite(&fill, 1, 1, fAux);
    fclose(fAux);
    fIn = fopen("auxiliar.txt", "r");
    /*leer fichero entrada o estandar*/
    if (fIn) {
        /* Pasamos las claves a Zm */
        for (i = 0; i < n; i++) {
            clave[i] -= K;
        }
        while (fread(cadena, sizeof (char), n, fIn) != 0) {
            for (i = 0; i < n; i++) {
                if ('A' <= cadena[i] && cadena[i] <= 'Z') {
                    cadena[i] -= K;
                    /*Cifrar*/
                    if (cifrar == 1) {
                        cadena[i] += clave[i];
                    }/*Descifrar*/
                    else {
                        cadena[i] -= clave[i];
                    }
                    cadena[i] %= m;
                    cadena[i] += K;
                }
            }
            fwrite(cadena, sizeof (char), n, fOut);
        }
    }

    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;
}

