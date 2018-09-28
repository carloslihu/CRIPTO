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

int mcd(int a, int b) 
{ 
    if (a == 0) 
        return b; 
    return mcd(b%a, a); 
}
// Se guarda en a el inverso de a modulo m en x
int mcdExtended(int a, int m, int *x, int *y) 
{ 
    // Base Case 
    if (a == 0) 
    { 
        *x = 0; 
        *y = 1; 
        return m; 
    } 
  
    int x1, y1; // To store results of recursive call 
    int mcd = mcdExtended(m%a, a, &x1, &y1); 
  
    // Update x and y using results of recursive 
    // call 
    *x = y1 - (m/a) * x1; 
    *y = x1; 
  
    return mcd; 
}  

/* PROGRAMA PRINCIPAL */
int main(int argc, char **argv)
{
	char entrada[256];
	int long_index = 0;//, retorno = 0;
	char opt;

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
		{"D", no_argument, 0,'d'},
		{"m", required_argument, 0, '1'},
		{"a", required_argument, 0, '2'},
		{"b", required_argument, 0, '3'},
		{"i", required_argument, 0, '4'},
		{"o", required_argument, 0, '5'},
		{0, 0, 0, 0}
	};

	//Simple lectura por parametros por completar casos de error
	while ((opt = getopt_long_only(argc, argv, "c:d:1:2:3:4:5", options, &long_index)) != -1) {
		switch (opt) {
		case 'c' :
			printf("Leida opcion -C \n");

			break;

		case 'd' :
			printf("Leida opcion -D \n");

			break;

		case '1' : 
			printf("Leida opcion -m: %s\n", optarg);

			break;

		case '2' :
			printf("Leida opcion -a: %s\n", optarg);

			break;

		case '3' :
			printf("Leida opcion -b: %s\n", optarg);
			break;

		case '4' :
			printf("Leida opcion -i: %s\n", optarg);

			break;

		case '5' :
			printf("Leida opcion -o: %s\n", optarg);

			break;

		case '?' :

		default:
			printf("Ejecucion: %s {-C|-D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]\n", argv[0]);
			exit(-1);
			break;
		}
	}
	int x, y; 
	int a = 488 , b= 721; 
	int g = mcdExtended(a, b, &x, &y); 
	printf("mcd(%d, %d) = %d\n", a, b, mcd(a, b)); 
	printf("gcd(%d, %d) = %d, x=%d, y=%d\n", a, b, g,x,y);




	return 0;


}

