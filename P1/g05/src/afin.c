/***************************************************************************
afin.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <gmp.h>

/*Definicion de constantes *************************************************/

int mcd(int a, int b) {
    if (a == 0)
        return b;
    return mcd(b % a, a);
}
// Se guarda en a el inverso de a modulo m en x

int mcdExtended(int a, int m, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return m;
    }

    int x1, y1;
    int mcd = mcdExtended(m % a, a, &x1, &y1);

    *x = y1 - (m / a) * x1;
    *y = x1;

    return mcd;
}

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {
    char entrada[256];
    char cadena[256];
    int long_index = 0; //, retorno = 0;
    char opt, simbolo_in, simbolo_out;
    mpz_t a, b, m, inv, aux, aux2;
    FILE *fIn, *fOut;
    int cifrar = -1;
    if (argc > 1) {
        if (strlen(argv[1]) < 256) {
            strcpy(entrada, argv[1]);
        }

    } else {
        printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"m", required_argument, 0, '1'},
        {"a", required_argument, 0, '2'},
        {"b", required_argument, 0, '3'},
        {"i", required_argument, 0, '4'},
        {"o", required_argument, 0, '5'},
        {0, 0, 0, 0}
    };
    mpz_inits(a, b, m, inv, aux, aux2, NULL);

    //Simple lectura por parametros por completar casos de error
    while ((opt = getopt_long_only(argc, argv, "c:d:1:2:3:4:5", options, &long_index)) != -1) {
        switch (opt) {
            case 'c':
                printf("Leida opcion -C \n");
                cifrar = 1;
                break;

            case 'd':
                printf("Leida opcion -D \n");
                cifrar = 0;
                break;

            case '1':
                printf("Leida opcion -m: %s\n", optarg);
                mpz_set_str(m, optarg, 10);
                break;

            case '2':
                printf("Leida opcion -a: %s\n", optarg);
                mpz_set_str(a, optarg, 10);
                break;

            case '3':
                printf("Leida opcion -b: %s\n", optarg);
                mpz_set_str(b, optarg, 10);
                break;

            case '4':
                printf("Leida opcion -i: %s\n", optarg);
                fIn = fopen(optarg, "r");
                if (!fIn) exit(-1);

                break;

            case '5':
                printf("Leida opcion -o: %s\n", optarg);
                fOut = fopen(optarg, "w");
                if (!fOut) exit(-1);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
    }
    if(cifrar == -1){
        printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }
        
    
    if (mpz_invert(inv, a, m) != 0) {
        gmp_printf("El inverso es: %Zd\n", inv);
    } else {
        printf("La clave no determina una función afín inyectiva\n");
        exit(-1);
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

    /*leer fichero entrada o estandar*/
    if (fIn) {
        /*printf("Leyendo \n");*/
        while (fscanf(fIn, "%c", &simbolo_in) != EOF) {
            /*convertir a mayusculas*/
            if ('a' <= simbolo_in && simbolo_in <= 'z') {
                simbolo_in -= ('a' - 'A');
            }
            if ('A' <= simbolo_in && simbolo_in <= 'Z') {
                //aux = simbolo de entrada
                mpz_set_ui(aux, (int) simbolo_in);
                /*Cifrar*/
                simbolo_in-=65;
                if (cifrar == 1) {
                    /*gmp_printf ("Cifrando % Zd \n", aux);*/
                    mpz_mul(aux2, a, aux);
                    mpz_mod(aux2, aux2, m);
                    mpz_add(aux2, aux2, b);
                    mpz_mod(aux2, aux2, m);
                }/*Descifrar*/
                else {
                    /*simbolo_out = (inv*(simbolo_in - b)) % m;*/
                    /*gmp_printf ("Descifrando % Zd \n", aux);*/
                    mpz_sub(aux2, aux, b);
                    mpz_mul(aux2, aux2, inv);
                    mpz_mod(aux2, aux2, m);
                }

                /*convertir a double o int y sumar 65, codigo de la primera letra A*/
                simbolo_out = mpz_get_d(aux2);
                simbolo_out += 65;
            } else {
                /*si el simbolo no es una letra A-Z, se deja igual*/
                simbolo_out = simbolo_in;
            }
            /*escribir fichero salida*/
            if (fOut) {
                fwrite(&simbolo_out, 1, 1, fOut);
            }/*escribir salida estandar*/
            else {
                fwrite(&simbolo_out, 1, 1, stdout);
            }
        }

    }

    mpz_clears(a, b, m, inv, aux, aux2, NULL);
    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;


}

