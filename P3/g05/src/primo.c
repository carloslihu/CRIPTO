/***************************************************************************
primo.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE]; //, cadena[SIZE];
    int long_index = 0;
    char opt;
    FILE *fOut = NULL;
    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s {-C | -D} [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"b", required_argument, 0, '1'},
        {"t", required_argument, 0, '2'},
        {"o", required_argument, 0, '3'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "1:2:3", options, &long_index)) != -1) {
        switch (opt) {
            case '1':
                break;
            case '2':
                break;

            case '3':
                fOut = fopen(optarg, "w");
                if (!fOut) exit(-1);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-C | -D} [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
    }

    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }
    /*TODO CODIGO*/

    if (fOut) fclose(fOut);

    return 0;


}
