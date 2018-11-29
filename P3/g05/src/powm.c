/***************************************************************************
powm.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/utils.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE]; //, cadena[SIZE];
    int long_index = 0;
    char opt;
    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s -p potencia -b base -e exponente -m modulo\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"p", required_argument, 0, '1'},
        {"b", required_argument, 0, '2'},
        {"e", required_argument, 0, '3'},
        {"m", required_argument, 0, '4'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "1:2:3:4", options, &long_index)) != -1) {
        switch (opt) {
            case '1':
                break;

            case '2':
                break;

            case '3':
                break;

            case '4':
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s -p potencia -b base -e exponente -m modulo\n", argv[0]);
                exit(-1);
                break;
        }
    }

    return 0;


}
