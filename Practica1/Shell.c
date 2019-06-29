
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

void Insercion(int *, int);

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

	int k = n/2, b,temp,x;

	uswtime(&utime0, &stime0, &wtime0);
	
	while(k>=1){
		b=1;
		while(b!=0){
			b=0;
			for(i=k; i<=n-1; i++){
				if(arr[i-k]>arr[i]){
					temp=arr[i];
					arr[i]=arr[i-k];
					arr[i-k]=temp;
					b=b+1;
				}
			}
		}
		k=k/2;
	}

	uswtime(&utime1, &stime1, &wtime1);
	
	for (i = 0; i < n; i++)
	{
		    //  printf("%d\n",arr[i]);  

	}

	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("%d\n",n);
	printf("%.10f s\n",  wtime1 - wtime0);
	printf("%.10f s\n",  utime1 - utime0);
	printf("%.10f s\n",  stime1 - stime0);
	printf("%.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("Formato exponencial:\n");
	printf("%.10e s\n",  wtime1 - wtime0);
	printf("%.10e s\n",  utime1 - utime0);
	printf("%.10e s\n",  stime1 - stime0);
	printf("%.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente	
	exit (0);	
}

