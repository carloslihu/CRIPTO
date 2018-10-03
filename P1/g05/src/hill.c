/***************************************************************************
hill.c

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

/**
 * @brief Calcula el maximo comun divisor
 *
 * @param primer entero
 * @param segundo entero
 *
 * @return el maximo comun divisor
 */
int mcd(int a, int b) {
    if (a == 0)
        return b;
    return mcd(b % a, a);
}
// Se guarda en a el inverso de a modulo m en x

/**
 * @brief Realiza la descomposición de Euclides Extendida.
 *        Calcula el inverso de a modulo m en x
 *
 * @param el entero a calcular su inverso
 * @param el modulo de la operación
 * @param el inverso de a
 * @param el otro factor por descomposición
 *
 * @return el maximo comun divisor
 */
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
    char opt, simbolo_in, simbolo_out, fill='W';
    FILE *fIn=NULL, *fOut=NULL, *fK=NULL, *fAux=NULL;
    int cifrar = -1;
    int matrix[3][3] = { 0 };
    int m=0, n=0, count=0, i=0, j=0, det=0;

    if (argc > 1) {
        strncpy(entrada, argv[1], 256);
    } else {
        printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-n NK} {-k fileK} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }

    static struct option options[] = {
        {"C", no_argument, 0, 'c'},
        {"D", no_argument, 0, 'd'},
        {"m", required_argument, 0, '1'},
        {"n", required_argument, 0, '2'},
        {"k", required_argument, 0, '3'},
        {"i", required_argument, 0, '4'},
        {"o", required_argument, 0, '5'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long_only(argc, argv, "c:d:1:2:3:4:5", options, &long_index)) != -1) {
        switch (opt) {
            case 'c':
                cifrar = 1;
                break;

            case 'd':
                cifrar = 0;
                break;

            case '1':
                m=atoi(optarg);
                break;

            case '2':
                n=atoi(optarg);
                if(n<1 || n>3){
                    printf("El tamano n de matriz debe estar en el rango [1,3]\n");
                    exit(-1);
                }
                break;

            case '3':
                fK = fopen(optarg, "r");
                if (!fK) exit(-1);
                break;

            case '4':
                fIn = fopen(optarg, "r");
                if (!fIn) exit(-1);
                break;

            case '5':
                fOut = fopen(optarg, "w");
                if (!fOut) exit(-1);
                break;

            case '?':
                break;

            default:
                printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-n NK} {-k fileK} [-i filein] [-o fileout]\n", argv[0]);
                exit(-1);
                break;
        }
    }
    //Si no se ha especificado si cifrar o descifrar
    if (cifrar == -1) {
        printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-n NK} {-k fileK} [-i filein] [-o fileout]\n", argv[0]);
        exit(-1);
    }



    /*leer fichero claves*/
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if (!fscanf(fK, "%d", &matrix[i][j])) 
                break;
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    fclose(fK);


    /*Calculo de determinante*/
    if(n==1){
        det = matrix[0][0];
    }
    else if(n==2){
        det = matrix[0][0]*matrix[1][1] - matrix[0][1]-matrix[1][0];
    }
    else if(n==3){
        det = matrix[0][0]*matrix[1][1]*matrix[2][2] + matrix[1][0]*matrix[2][1]*matrix[0][2] + matrix[0][1]*matrix[1][2]*matrix[2][0] - matrix[0][2]*matrix[1][1]*matrix[2][0] - matrix[2][1]*matrix[1][2]*matrix[0][0] - matrix[1][0]*matrix[0][1]*matrix[2][2];;
    }
    else{
        printf("La matriz de claves no puede superar 3x3\n");
        exit(-1);   
    }

    if(det==0){
        printf("La clave no puede tener determinante 0 \n");
        exit(-1);
    }

    printf("El determinante es %d\n", det);

    if (mcd(m, det) != 1) {
        printf("La clave no determina una función inyectiva\n");
        exit(-1);
    }

    /*crear entrada estandar*/
    if (!fIn) {
        printf("Leyendo entrada estandar \n");
        fgets(cadena, 256, stdin);
        fIn = fopen("teclado.txt", "w");
        fwrite(cadena, 1, strlen(cadena), fIn);
        fclose(fIn);
        fIn = fopen("teclado.txt", "r");
    }

    /*Limpiar texto de entrada con letras A-Z*/
    if (fIn) {
        fAux= fopen("auxiliar.txt", "w");
        if (fAux) {
            while (fscanf(fIn, "%c", &simbolo_in) != EOF) {
                /*convertir a mayusculas*/
                if ('a' <= simbolo_in && simbolo_in <= 'z') {
                    simbolo_in -= ('a' - 'A');
                }
                if ('A' <= simbolo_in && simbolo_in <= 'Z') {
                    /*escribir fichero auxiliar de entrada*/
                    printf("Anadiendo a auxiliar \n");    
                    fwrite(&simbolo_in, 1, 1, fAux);
                    count++;
                }
            }
            /*rellenar texto para hacerlo modulo N*/
            count = count%n;
            for(i=0; i<count; i++) fwrite(&fill, 1, 1, fAux);
            fclose(fAux);
            fIn = fopen("auxiliar.txt", "r");
        }
    }



      /*leer fichero entrada o estandar*/
    // if (fIn) {
    //     while (fread(fIn, "%c", &simbolo_in) != EOF) {
    //         /*convertir a mayusculas*/
    //         if ('a' <= simbolo_in && simbolo_in <= 'z') {
    //             simbolo_in -= ('a' - 'A');
    //         }
    //         if ('A' <= simbolo_in && simbolo_in <= 'Z') {
    //             //aux es nuestro simbolo de entrada
    //             //aux2 es nuestro simbolo de salida
    //             mpz_set_ui(aux, (int) simbolo_in);
    //             simbolo_in -= 65;

    //             /*Cifrar*/
    //             if (cifrar == 1) {

    //             }/*Descifrar*/
    //             else {
                    
    //             }

    //             convertir a double o int y sumar 65, codigo de la primera letra A
    //             simbolo_out = mpz_get_d(aux2);
    //             simbolo_out += 65;
    //         } else {
    //             /*si el simbolo no es una letra A-Z, se deja igual*/
    //             simbolo_out = simbolo_in;
    //         }
    //         /*escribir fichero salida*/
    //         if (fOut) {
    //             fwrite(&simbolo_out, 1, 1, fOut);
    //         }/*escribir salida estandar*/
    //         else {
    //             fwrite(&simbolo_out, 1, 1, stdout);
    //         }
    //     }

    // }


    // if(fOut){
    //     printf("Hay fOut\n"); 
    // }
    // else{
    //     printf("No hay fOut\n"); 
    // }






    if (fIn) fclose(fIn);
    if (fOut) fclose(fOut);

    return 0;


}

