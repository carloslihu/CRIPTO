/***************************************************************************
IC.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/
#include "../includes/utils.h"

/*Definicion de constantes *************************************************/

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[256];
    int long_index = 0; //, retorno = 0;
    char opt;
    FILE *fIn = NULL, *fOut = NULL;
    int l;

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
    
    return 0;
}

