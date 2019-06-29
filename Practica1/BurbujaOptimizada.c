
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
 	

	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	FILE *Numeros;  
   Numeros = fopen("numeros10millones.txt", "r");
 
	int n,i;
	n=atoi(argv[1]);
	int *arr;
	//scanf("%d",&n);
	arr = (int *) malloc(sizeof(int)*n);
	
	for (i = 0; i < n; i++)
      fscanf(Numeros,"%d",&arr[i]);     
    fclose(Numeros);

    int j,aux;

    int cambios=1;
	i=0;

	uswtime(&utime0, &stime0, &wtime0);
	while(i<n-1 && cambios!=0){
		cambios=0;
		for(j=0; j<=(n-2)-i; j++){
			if(arr[j]>arr[j+1]){
				aux = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = aux;
				cambios=1;
			}
		}
		i+=1;
	}
	uswtime(&utime1, &stime1, &wtime1);

	for(i = 0 ; i< n; i++) 
	{
	//	printf("%d\n",arr[i]);
	}
	

	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("%d\n",n);
	printf("%.10f \n",  wtime1 - wtime0);
	printf("%.10f \n",  utime1 - utime0);
	printf("%.10f \n",  stime1 - stime0);
	printf("%.10f  \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("Formato exponencial:\n");
	printf("%.10e \n",  wtime1 - wtime0);
	printf("%.10e \n",  utime1 - utime0);
	printf("%.10e \n",  stime1 - stime0);
	printf("%.10f \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}
