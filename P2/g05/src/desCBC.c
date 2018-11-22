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
    uint64_t key = 0, iv = 0;
    uint64_t* subkeys;
    uint64_t Mens;
    uint64_t C, Caux;


    if (argc > 1) {
        strncpy(entrada, argv[1], SIZE);
    } else {
        printf("Ejecucion: %s {-C | -D -k clave -iv vectorincializacion} "
                "[-i filein] [-o fileout]\n", argv[0]);
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
                break;

            case '2':
                iv = strtoull(optarg, NULL, 16);
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
                exit(-1);
                break;
        }
    }

    if (cifrar == 1) {
        srand(time(NULL));
        key = createKey();
        iv = createIV();
    }


    /*Obtenemos subclaves*/
    subkeys = createSubkeys(key);
    /*crear entrada estandar*/
    if (!fIn) {
        printf("Leyendo entrada estandar \n");
        fgets(cadena, SIZE, stdin);
        fIn = fopen("teclado.txt", "wb");
        fwrite(cadena, 1, strlen(cadena), fIn);
        fclose(fIn);
        fIn = fopen("teclado.txt", "rb+");
    }
    /* Si no se especifica, usamos salida estandar */
    if (!fOut) {
        fOut = stdout;
    }

    /*rellenar texto para hacerlo modulo 8 B*/
    fseek(fIn, 0, SEEK_END);
    count = ftell(fIn) % 8; /*macro para 8*/
    for (i = 0; i < 8 - count && count != 0; i++) fwrite("0", 1, 1, fIn);
    fseek(fIn, 0, SEEK_SET);

    /*Aquí vamos leyendo del fichero*/
    if (fIn) {
        if (cifrar == 1) {
            //            C = iv; /*comentar para ECB*/
            while (fread(&Mens, 8, 1, fIn) != 0) {
                //                Mens ^= C; /*comentar para ECB*/
                C = encode_block(Mens, subkeys, cifrar);
                fwrite(&C, 8, 1, fOut);
            }
        } else {
            //            Caux = iv; /*comentar para ECB*/
            while (fread(&C, 8, 1, fIn) != 0) {
                Mens = encode_block(C, subkeys, cifrar);
                //                Mens ^= Caux; /*comentar para ECB*/
                fwrite(&Mens, 8, 1, fOut);
                //                Caux = C; /*comentar para ECB*/
            }
        }
    }

    free(subkeys);
    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;


}
