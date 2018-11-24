/***************************************************************************
sac_bic_des.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/DES_tables.h"

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv) {

    int i = 0, j = 0, r = 0, s = 0, cajas = 0;
    double unos[32] = {0}, ceros[32] = {0};
    double ceros_b[4] = {0};
    double pares_ceros[4][4] = {0};
    uint64_t cadena = 0, cadena2 = 0;
    uint32_t /*SB = 0, */ SB2 = 0;
    double repeticiones = 1000000;
    FILE *fout;
    uint8_t b = 0, sb = 0;

    srand(time(NULL));

    fout = fopen("SAC_BIC.txt", "w");

    /*------------- SAC -------------*/

    fprintf(fout, "Resultados de SAC\n\n");

    for(i = 0; i<repeticiones; i++){

        cadena = cadena_aleatoria(48);
        /* 000001 000001 000001 000001 000001 000001 000001 000001 = 0x41041041041*/
        cadena2 = cadena ^ 0x41041041041; /*cambiamos un bit de cada una de las 8 cajas de 6 bits*/

        SB2 = SB_return(cadena2);

        /*contamos los unos y los ceros de cada una de las posiciones bi de la salida de las SBoxes*/
        for(j = 0; j<32; j++){
            if(get_bit((uint64_t)SB2, (uint8_t)(j+32)) == 0) ceros[j] ++;
            else unos[j] ++;
        }

    }

    for(j = 0; j<32; j++){
        fprintf(fout, "b%d\t\tP(1) = %lf\t\tP(0) = %lf\n", j+1, unos[j]/repeticiones, ceros[j]/repeticiones);
    }

    /*------------- BIC -------------*/

    fprintf(fout, "\nResultados de BIC\n\n");

    /*iteramos por cada caja*/
    for(cajas = 0; cajas < 8; cajas++){

        for(i = 0; i<repeticiones; i++){

            b = (uint8_t) cadena_aleatoria(6);

            sb = SBox_result(b, cajas);

            /*comprobamos los ceros en cada bi, deberian ser la mitad (1/2)*/
            for(j = 0; j < 4; j++){
                if(get_bit((uint64_t)sb, (uint8_t)(j+60)) == 0) ceros_b[j] ++;
            }
            /*calculamos ceros conjuntos, por cada par, deberia ser (1/4)*/
            for(r = 0; r < 4; r++){
                for(s = r+1; s < 4; s++){
                    if(get_bit((uint64_t)sb, (uint8_t)(r+60)) == 0 && get_bit((uint64_t)sb, (uint8_t)(s+60)) == 0) pares_ceros[r][s] ++;
                }
            }

        }

        fprintf(fout, "\nSBOX %d\n", cajas+1);
        /*probabilidades simples*/
        for(r = 0; r < 4; r++){
            fprintf(fout, "b%d\tP(0) = %lf\n", r+1, ceros_b[r]/repeticiones);
            ceros_b[r] = 0;
        }
        /*probabilidades conjuntas*/
        for(r = 0; r < 4; r++){
            for(s = r+1; s < 4; s++){
                fprintf(fout, "b%d,%d\tP(0,0) = %lf\n", r+1, s+1, pares_ceros[r][s]/repeticiones);
                pares_ceros[r][s] = 0;
                }
        }
    }


    printf("Creado fichero SAC_BIC.txt\n");

    fclose(fout);

    return 0;

}
