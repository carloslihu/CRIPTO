/***************************************************************************
permutacion.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/*Definicion de constantes *************************************************/

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[256];
    char cadena[512];
    int long_index = 0;
    int perm_fila[20] = {0}, perm_columna[20] = {0}, inv_fila[20] = {0}, inv_columna[20] = {0};
    char opt, simbolo_out, fill = 'W';
    char *k1 = NULL, *k2 = NULL;
    char **matrix = NULL;
    FILE *fIn = NULL, *fOut = NULL, *fAux = NULL;
    int cifrar = -1, count = 0;
    int i = 0, j = 0, n = 0, m = 0;

    if (argc > 1) {
        strncpy(entrada, argv[1], 256);
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
                printf("K1 es %s\n", k1);
                break;

            case '2':
                k2 = optarg;
                printf("K2 es %s\n", k2);
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



    for (i = 0, j = 0; i < strlen(k1); i++) {
        if (0 < (k1[i] - '0') && (k1[i] - '0') <= strlen(k1)) {
            perm_fila[j] = (k1[i] - '0');
            m++;
            j++;
        }
    }


    for (i = 0, j = 0; i < strlen(k2); i++) {
        if (0 < (k2[i] - '0') && (k2[i] - '0') <= strlen(k2)) {
            perm_columna[j] = (k2[i] - '0');
            n++;
            j++;
        }
    }

    matrix = (char**) malloc(sizeof (char*)*m);
    for (i = 0; i < m; i++) {
        matrix[i] = (char*) malloc(sizeof (char)*n);
    }

/*    for(i=0;i<m;i++){
            printf("%d", perm_fila[i]);
        }
    printf("Tamano %d\n", m);

    for(i=0;i<n;i++){
            printf("%d", perm_columna[i]);
        }
    printf("Tamano %d\n", n);*/


    /*calculo de las permutaciones para descifrar*/
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            if (perm_fila[j] == i + 1) {
                inv_fila[i] = j + 1;
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (perm_columna[j] == i + 1) {
                inv_columna[i] = j + 1;
            }
        }
    }

    for(i=0;i<m;i++){
            printf("%d", inv_fila[i]);
    }

    for(i=0;i<n;i++){
            printf("%d", inv_columna[i]);
    }


    /*crear entrada estandar*/
    if (!fIn) {
        printf("Leyendo entrada estandar \n");
        fgets(cadena, 512, stdin);
        fIn = fopen("teclado.txt", "w");
        fwrite(cadena, 1, strlen(cadena), fIn);
        fclose(fIn);
        fIn = fopen("teclado.txt", "r");
    }


    /*rellenar texto para hacerlo modulo N*/
    /*en fAux se guarda la direccion del texto nuevo parseado*/
    count = parsear(fIn, &fAux);
    count = count % (m*n);
    for (i = 0; i < (m*n) - count && count != 0; i++) fwrite(&fill, 1, 1, fAux);
    fclose(fAux);
    fIn = fopen("auxiliar.txt", "r");


    return 0;

    /*leer fichero entrada o estandar*/
    if (fIn) {
        while (fread(cadena, sizeof (char), m*n, fIn) != 0) {

            for (i = 0; i < n; i++) {
                /*Cifrar*/
                if (cifrar == 1) {
                    simbolo_out = cadena[perm_columna[i] - 1];
                }/*Descifrar*/
                else {
                    simbolo_out = cadena[perm_columna[i] - 1];
                }

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

    printf("\n");

    return 0;


}

