/***************************************************************************
kasiski.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/
#include "../includes/utils.h"

int main(int argc, char **argv) {
    char entrada[256], cadena[256];
    int long_index = 0;
    char opt;
    FILE *fIn = NULL, *fOut = NULL;
    int l = 3, Clen;
    int i, j, k;
    char C[TAM], R[TAM]; /*En C guardamos la cadena cifrada
                          * En R las subcadenas repetidas*/

    if (argc > 1) {
        strncpy(entrada, argv[1], 256);
    } else {
        printf("Ejecucion: %s {-l Ngrama} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"l", required_argument, 0, '1'},
        {"i", required_argument, 0, '2'},
        {"o", required_argument, 0, '3'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "1:2:3", options, &long_index)) != -1) {
        switch (opt) {
            case '1':
                l = atoi(optarg);
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
                printf("Ejecucion: %s {-l Ngrama} [-i filein] [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
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
    fscanf(fIn, "%s", C);
    Clen = strlen(C) + 1;
    for (i = 0; i < Clen; i++) {
        for (j = i + 1; j < Clen; j++) {
            for (k = 0; C[i + k] == C[j + k]; k++) {
                R[k] = C[i + k];
            }
            R[k] = '\0';
            if (k >= l) {
                fprintf(fOut, "%s\tposiciones: %d  y %d con distancia %d\n", R, i, j, j - i);
            }
        }
    }
    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);
    return 0;
}