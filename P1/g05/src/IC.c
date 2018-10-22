/***************************************************************************
IC.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/
#include "../includes/utils.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE], cadena[SIZE];
    int long_index = 0, iflag = 1;
    char opt, simbolo_in;
    FILE *fIn = NULL, *fOut = NULL;
    int l = 0, i = 0, j = 0, k = 0, n = 0, o = 0;
    double IC_c = 0, IC_i = 0;
    /*Tablas de porcentajes de cada letra del alfabeto en castellano */
    double f_c[M] = {11.96, 0.92, 2.92, 6.87, 16.78, 0.52, 0.73, 0.89, 4.15,
        0.30, 0.0, 8.37, 2.12, 7.01, 8.69, 2.77, 1.53, 4.94, 7.88, 3.31, 4.80,
        0.39, 0.0, 0.06, 1.54, 0.15};
    /*Tablas de porcentajes de cada letra del alfabeto en ingles */
    double f_i[M] = {8.04, 1.54, 3.06, 3.99, 12.51, 2.30, 1.96, 5.49, 7.26,
        0.16, 0.67, 4.14, 2.53, 7.09, 7.60, 2.00, 0.11, 6.12, 6.54, 9.25, 2.71,
        0.99, 1.92, 0.19, 1.73, 0.19};
    double *IC = NULL, **Mg = NULL;
    int max = 0;
    char imax = 0;
    int **f = NULL;

    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {

        printf("Ejecucion: %s {-l Ngrama} [-i filein] [-o fileout] {-E|-C}\n"
                "(E significa English, C significa Castellano (por defecto))\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"E", no_argument, 0, 'e'},
        {"C", no_argument, 0, 'c'},
        {"l", required_argument, 0, '1'},
        {"i", required_argument, 0, '2'},
        {"o", required_argument, 0, '3'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "1:2:3:e:c", options, &long_index)) != -1) {
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
            case 'e':
                iflag = 0;
                break;

            case 'c':
                iflag = 1;
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-l Ngrama} [-i filein] [-o fileout] {-E|-C}\n"
                        "(E significa English, C significa Castellano (por defecto))\n", argv[0]);
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
    /* Calculamos los Indices de coincidencia del castellano e ingles */
    for (i = 0; i < M; i++) {
        IC_c += f_c[i] * f_c[i];
        IC_i += f_i[i] * f_i[i];
    }
    IC_c /= 10000;
    IC_i /= 10000;
    fprintf(fOut, "IC Castellano: %lf\nIC Inglés: %lf\n\n", IC_c, IC_i);

    /*Inicializamos variables*/
    f = (int**) calloc(l, sizeof (int*));
    IC = (double*) calloc(l, sizeof (double));
    Mg = (double**) calloc(l, sizeof (double*));
    for (i = 0; i < l; i++) {
        f[i] = (int*) calloc(M, sizeof (int));
        Mg[i] = (double*) calloc(M, sizeof (double));
        for (j = 0; j < M; j++) {
            f[i][j] = 0;
            Mg[i][j] = 0;
        }
        IC[i] = 0;
    }
    /*Leemos letras uno a uno y actualizamos las frecuencias absolutas */
    /*f[i][k] guardará para el vector i, la frecuencia absoluta del caracter k */
    for (i = 0, j = 0; fscanf(fIn, "%c", &simbolo_in) != EOF; i++) {
        if (i == l) {
            i = 0;
            /*En j guardo el tamaño total de cada vector*/
            j++;
        }
        f[i][(int) (simbolo_in - 65)]++;
    }
    /*Calculamos los indices de coincidencia de cada vector */
    for (i = 0; i < l; i++) {
        for (k = 0; k < M; k++) {
            IC[i] += f[i][k] * (f[i][k] - 1);
        }
        /*En j guardamos el tamaño de cada vector */
        IC[i] /= j * (j - 1);
        fprintf(fOut, "IC_%d: %lf\n", i, IC[i]);
    }
    /*Asumimos que la l usada es correcta y procedemos a calcular la Mg para buscar la clave */
    /* para cada coordenada Ki de la clave */
    for (i = 0; i < l; i++) {
        /* Si desplazamos -n las frecuencias */
        fprintf(fOut, "Valores del Mg para K_%d\n", i);
        max = 0;
        imax = 0;
        for (n = 0; n < M; n++) {
            /* Calculamos los IC */
            for (k = 0; k < M; k++) {
                /* en o guardamos el indice del desplazamiento de frecuencias */
                if ((k + n) < M) {
                    o = k + n;
                } else {
                    o = k + n - M;
                }

                if (iflag == 1) {/*Si es castellano*/
                    Mg[i][n] += f_c[k] * f[i][o];
                } else {/*Si es ingles*/
                    Mg[i][n] += f_i[k] * f[i][o];
                }
            }
            /*Caculamos de cada vector el desplazamiento mas probable para ser 
             la clave correcta */
            if (max < Mg[i][n]) {
                max = Mg[i][n];
                imax = n;
            }
            Mg[i][n] = Mg[i][n] / (j * 100);

            fprintf(fOut, "%lf\t", Mg[i][n]);
        }

        fprintf(fOut, "\nLa posible clave para K%d es %c\n\n", i, imax + K);
    }

    for (i = 0; i < l; i++) {
        free(f[i]);
        free(Mg[i]);
    }
    free(f);
    free(Mg);
    free(IC);
    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);
    printf("\n");
    return 0;
}

