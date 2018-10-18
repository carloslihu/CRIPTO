/***************************************************************************
IC.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/
#include "../includes/utils.h"

/*Definicion de constantes *************************************************/
#define M 26

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[256];
    int long_index = 0; //, retorno = 0;
    char opt;
    FILE *fIn = NULL, *fOut = NULL;
    int l, i;
    double IC_c = 0, IC_i = 0;
    double f_c[M] = {11.96, 0.92, 2.92, 6.87, 16.78, 0.52, 0.73, 0.89, 4.15,
        0.30, 0.0, 8.37, 2.12, 7.01, 8.69, 2.77, 1.53, 4.94, 7.88, 3.31, 4.80,
        0.39, 0.0, 0.06, 1.54, 0.15};
    double f_i[M] = {8.04, 1.54, 3.06, 3.99, 12.51, 2.30, 1.96, 5.49, 7.26,
        0.16, 0.67, 4.14, 2.53, 7.09, 7.60, 2.00, 0.11, 6.12, 6.54, 9.25, 2.71,
        0.99, 1.92, 0.19, 1.73, 0.19};
    if (argc > 1) {
        strncpy(entrada, argv[1], 256);
    } else {
        printf("Ejecucion: %s {-l Ngrama} [-i filein] [-o fileout]\n", argv[0]);
        for (i = 0; i < M; i++) {
            IC_c += f_c[i] * f_c[i];
            IC_i += f_i[i] * f_i[i];
        }
        IC_c /= 10000;
        IC_i /= 10000;
        printf("IC_c: %lf\nIC_i: %lf\n", IC_c, IC_i);
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

