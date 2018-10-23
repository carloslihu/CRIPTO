/***************************************************************************
kasiski.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/
#include "../includes/utils.h"

int main(int argc, char **argv) {
    char entrada[SIZE], cadena[SIZE];
    int long_index = 0;
    char opt;
    FILE *fIn = NULL, *fOut = NULL;
    int l = 3, Clen;
    int i, j, k, m;
    char C[TAM], R[TAM]; /*En C guardamos la cadena cifrada
                          * En R las subcadenas repetidas*/
    int mcd, dist[TAM] = {0};
    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
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
        fgets(cadena, SIZE, stdin);
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
    /*Tamaño del texto cifrado*/
    Clen = strlen(C) + 1;
    for (i = 0; i < Clen; i++) {
        m = 0;
        for (j = i + 1; j < Clen; j++) {
            /*Vemos cuantos caracteres coinciden seguidos */
            for (k = 0; C[i + k] == C[j + k]; k++) {
                /*En R se guarda la subcadena posible */
                R[k] = C[i + k];
            }
            /*No coinciden mas caracteres para esta subcadena */
            R[k] = '\0';
            /* Numero de caracteres que coinciden
             Vemos si superan el valor minimo pedido*/
            if (k >= l) {
                dist[m] = j - i;
                fprintf(fOut, "%s\tposiciones: %d  y %d con distancia %d\n", R, i, j, dist[m]);
                m++;
            }
        }
        /*En caso de más de una distancia para la misma subcadena */
        if (m > 1) {
            mcd = mcdRec(dist, m);
            fprintf(fOut, "MCD: %d\n\n", mcd);
        }
    }
    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);
    printf("\n");
    return 0;
}