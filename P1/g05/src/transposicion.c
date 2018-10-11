/***************************************************************************
transposicion.c

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
    int *permutacion=NULL, *inversa=NULL;
    char opt, simbolo_out, fill = 'W';
    char* p=NULL;
    FILE *fIn = NULL, *fOut = NULL, *fAux = NULL;
    int cifrar = -1, resultado = 0, count=0;
    int i=0, j=0, n=0;

    if (argc > 1) {
        strncpy(entrada, argv[1], 256);
    } else {
        printf("Ejecucion: %s {-C | -D} {-p permutacion | -n Nperm} [-i filein] [-o fileout]\n", argv[0]);
        printf("Ejemplo: %s -C -p \"5 4 3 2 1\" -n 5 -i entrada.txt -o codificado.txt\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"p", required_argument, 0, '1'},
        {"n", required_argument, 0, '2'},
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
                p = optarg;
                printf("P es %s\n", p);
                break;

            case '2':
                n = atoi(optarg);
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
                printf("Ejecucion: %s {-C | -D} {-p permutacion | -n Nperm} [-i filein] [-o fileout]\n", argv[0]);
                printf("Ejemplo: %s -C -p \"5 4 3 2 1\" -n 5 -i entrada.txt -o codificado.txt\n", argv[0]);
                exit(-1);
                break;
        }
    }

    //Si no se ha especificado si cifrar o descifrar
    if (cifrar == -1) {
        printf("Ejecucion: %s {-C | -D} {-p permutacion | -n Nperm} [-i filein] [-o fileout]\n", argv[0]);
        printf("Ejemplo: %s -C -p \"5 4 3 2 1\" -n 5 -i entrada.txt -o codificado.txt\n", argv[0]);
        exit(-1);
    }


    /*leer fichero claves*/
    permutacion =(int*)malloc(sizeof(int)*n);
    inversa =(int*)malloc(sizeof(int)*n);

    for(i=0,j=0;i<strlen(p);i++){
        if(0<(p[i]-'0') && (p[i]-'0')<=n){
            permutacion[j]=(p[i]-'0');
            j++;
        }
    }

    for(i=0;i<n;i++){
        printf("%d", permutacion[i]);
    }
    printf("\n");


    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(permutacion[j]==i+1){
                inversa[i]=j+1;
            } 
        }

    }

    for(i=0;i<n;i++){
        printf("%d", inversa[i]);
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
    count = count % n;
    for (i = 0; i < n - count && count != 0; i++) fwrite(&fill, 1, 1, fAux);
    fclose(fAux);
    fIn = fopen("auxiliar.txt", "r");


    /*leer fichero entrada o estandar*/
    if (fIn) {
        while (fread(cadena, sizeof (char), n, fIn) != 0) {

            for (i = 0; i < n; i++) {
                /*Cifrar*/
                if (cifrar == 1) {
                    simbolo_out = cadena[permutacion[i]-1];
                }/*Descifrar*/
                else {
                    simbolo_out = cadena[permutacion[i]-1];
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

