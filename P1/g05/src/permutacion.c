/***************************************************************************
permutacion.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE];
    char cadena[SIZE];
    int long_index = 0;
    int perm_fila[20] = {0}, perm_columna[20] = {0}, inv_fila[20] = {0}, inv_columna[20] = {0};
    char opt, fill = 'W';
    char *k1 = NULL, *k2 = NULL;
    char **matrix = NULL, **matrix2 = NULL, **matrix3 = NULL;
    FILE *fIn = NULL, *fOut = NULL, *fAux = NULL;
    int cifrar = -1, count = 0;
    int i = 0, j = 0, n = 0, m = 0, r = 0, s = 0, t = 0;

    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s {-C | -D} {-k1 K1 -k2 K2} [-i filein] [-o fileout]\n", argv[0]);
        printf("Ejemplo: %s -C -k1 \"4 3 2 1\" -k2 \"3 2 1\" -i entrada.txt -o cifrado.txt\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"k1", required_argument, 0, '1'},
        {"k2", required_argument, 0, '2'},
        {"i", required_argument, 0, '3'},
        {"o", required_argument, 0, '4'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "c:d:1:2:3:4", options, &long_index)) != -1) {
        switch (opt) {
            case 'c':
                cifrar = 1;
                break;

            case 'd':
                cifrar = 0;
                break;

            case '1':
                k1 = optarg;
                break;

            case '2':
                k2 = optarg;
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
                printf("Ejecucion: %s {-C | -D} {-k1 K1 -k2 K2} [-i filein] [-o fileout]\n", argv[0]);
                printf("Ejemplo: %s -C -k1 \"4 3 2 1\" -k2 \"3 2 1\" -i entrada.txt -o cifrado.txt\n", argv[0]);
                exit(-1);
                break;
        }
    }

    //Si no se ha especificado si cifrar o descifrar
    if (cifrar == -1) {
        printf("Ejecucion: %s {-C | -D} {-k1 K1 -k2 K2} [-i filein] [-o fileout]\n", argv[0]);
        printf("Ejemplo: %s -C -k1 \"4 3 2 1\" -k2 \"3 2 1\" -i entrada.txt -o cifrado.txt\n", argv[0]);
        exit(-1);
    }


    /*crear vector de permutacion de filas*/
    /*en m se guarda el tamaño de k1 (nº de filas)*/
    for (i = 0; i < strlen(k1); i++) {
        if (0 < (k1[i] - '0') && (k1[i] - '0') <= strlen(k1)) {
            perm_fila[m] = (k1[i] - '0');
            m++;
        }
    }

    /*crear vector de permutacion de columnas*/
    /*en n se guarda el tamaño de k2 (nº de columnas)*/
    for (i = 0; i < strlen(k2); i++) {
        if (0 < (k2[i] - '0') && (k2[i] - '0') <= strlen(k2)) {
            perm_columna[n] = (k2[i] - '0');
            n++;
        }
    }

    /*matrices para las permutaciones del metodo*/
    matrix = (char**) malloc(sizeof (char*)*m);
    matrix2 = (char**) malloc(sizeof (char*)*m);
    matrix3 = (char**) malloc(sizeof (char*)*m);
    for (i = 0; i < m; i++) {
        matrix[i] = (char*) malloc(sizeof (char)*n);
        matrix2[i] = (char*) malloc(sizeof (char)*n);
        matrix3[i] = (char*) malloc(sizeof (char)*n);
    }

    /*calculo de las permutaciones para descifrar filas*/
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            if (perm_fila[j] == i + 1) {
                inv_fila[i] = j + 1;
            }
        }
    }
    /*calculo de las permutaciones para descifrar columnas */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (perm_columna[j] == i + 1) {
                inv_columna[i] = j + 1;
            }
        }
    }

    /*crear entrada estandar*/
    if (!fIn) {
        printf("Leyendo entrada estandar \n");
        fgets(cadena, SIZE, stdin);
        fIn = fopen("teclado.txt", "w");
        fwrite(cadena, 1, strlen(cadena), fIn);
        fclose(fIn);
        fIn = fopen("teclado.txt", "r");
    }

    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }
    /*rellenar texto para hacerlo modulo m*n */
    /*en fAux se guarda la direccion del texto nuevo parseado*/
    count = parsear(fIn, &fAux);
    count = count % (m * n);
    for (i = 0; i < (m * n) - count && count != 0; i++) fwrite(&fill, 1, 1, fAux);
    fclose(fAux);
    fIn = fopen("auxiliar.txt", "r");


    /*leer fichero entrada o estandar*/
    if (fIn) {
        while (fread(cadena, sizeof (char), m * n, fIn) != 0) {

            for (i = 0; i < m; i++) {
                memcpy(matrix[i], cadena + (n * i), n);
            }

            /*Cifrar*/
            if (cifrar == 1) {
                /*permutar filas*/
                for (r = 0; r < m; r++) {
                    t = perm_fila[r];
                    for (s = 0; s < n; s++) {
                        matrix2[r][s] = matrix[t - 1][s];
                    }
                }
                /*permutar columnas*/
                for (r = 0; r < n; r++) {
                    t = perm_columna[r];
                    for (s = 0; s < m; s++) {
                        matrix3[s][r] = matrix2[s][t - 1];
                    }
                }
            }/*Descifrar*/
            else {
                /*permutar columnas*/
                for (r = 0; r < n; r++) {
                    t = inv_columna[r];
                    for (s = 0; s < m; s++) {
                        matrix2[s][r] = matrix[s][t - 1];
                    }
                }
                /*permutar filas*/
                for (r = 0; r < m; r++) {
                    t = inv_fila[r];
                    for (s = 0; s < n; s++) {
                        matrix3[r][s] = matrix2[t - 1][s];
                    }
                }
            }
            for (i = 0; i < m; i++) {
                for (j = 0; j < n; j++) {
                    fwrite(&matrix3[i][j], 1, 1, fOut);
                }
            }
        }
    }

    for (i = 0; i < m; i++) {
        free(matrix[i]);
        free(matrix2[i]);
        free(matrix3[i]);
    }

    free(matrix);
    free(matrix2);
    free(matrix3);

    printf("\n");

    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;


}

