/***************************************************************************
seg-perf.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE], cadena[SIZE];
    int long_index = 0;
    char opt, simbolo_in, simbolo_out;
    FILE *fIn = NULL, *fOut = NULL, *fAux = NULL;
    int cifrar = -1, i = 0, j = 0, k = 0;

    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s {-C | -D -k clave -iv vectorincializacion} "
                "[-i filein] [-o fileout]\n", argv[0]);
        /*printf("Ejemplo: %s -C -m 26 -a 5 -b 4\n", argv[0]);*/
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"k", required_argument, 0, '1'},
        {"iv", required_argument, 0, '2'},
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
                break;

            case '2':
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
                printf("Ejecucion: %s {-C | -D -k clave -iv vectorincializacion} "
                        "[-i filein] [-o fileout]\n", argv[0]);
                /*printf("Ejemplo: %s -C -m 26 -a 5 -b 4\n", argv[0]);*/
                exit(-1);
                break;
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

    /*parsear texto*/
    parsear(fIn, &fAux);
    fclose(fAux);
    fIn = fopen("auxiliar.txt", "r");
    /*leer fichero entrada o estandar*/
    if (fIn) {

    }

    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;


}
