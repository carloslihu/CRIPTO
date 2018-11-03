/***************************************************************************
desCBC.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/DES_tables.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[SIZE], cadena[SIZE];
    int long_index = 0;
    char opt;
    FILE *fIn = NULL, *fOut = NULL;
    int cifrar = -1, i = 0;
    int count;
    uint64_t key;
    uint64_t* subkeys;
    uint64_t Mens;
    uint64_t C;
    /*uint8_t bit;*/
    uint64_t Mens1 = 0x0123456789ABCDEF;


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
                key = strtoull(optarg, NULL, 16);
                //printf("0x%"PRIx64"\n", key);
                break;

            case '2':
                break;

            case '3':
                fIn = fopen(optarg, "rb+");
                if (!fIn) exit(-1);
                break;

            case '4':
                fOut = fopen(optarg, "wb");
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

    /*Obtenemos subclaves*/
    subkeys = createSubkeys(key);
    /*for (i = 0; i < 16; i++) {
        printf("K%d: %" PRIx64 "\n", i, subkeys[i]);
    }*/
    /*crear entrada estandar*/
    if (!fIn) {
        printf("Leyendo entrada estandar \n");
        fgets(cadena, SIZE, stdin);
        fIn = fopen("teclado.txt", "w");
        fwrite(cadena, 1, strlen(cadena), fIn);
        fclose(fIn);
        fIn = fopen("teclado.txt", "r+");
    }
    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }

    /*rellenar texto para hacerlo modulo 8 B*/
    fseek(fIn, 0, SEEK_END);
    count = ftell(fIn) % 8; /*macro para 8*/

    for (i = 0; i < 8 - count && count != 0; i++) fwrite("0", 1, 1, fIn);
    /*leer fichero entrada o estandar*/
    fseek(fIn, 0, SEEK_SET);

    /*fwrite(&Mens1, 8, 1, fOut);*/
    /*Aquí vamos leyendo del fichero*/
    if (fIn) {
        /*TODO*/
        /*en M guardamos los primeros 64 bits*/
        if (fread(&Mens, 8, 1, fIn) != 0) {
            printf("Mensaje a cifrar 0x%"PRIx64"\n", Mens);
            C = encode_block(Mens, subkeys, cifrar);
        }

        printf("Cifrado 0x%"PRIx64"\n", C);
        fwrite(&C, 8, 1, fOut);

    }
    free(subkeys);
    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;


}
