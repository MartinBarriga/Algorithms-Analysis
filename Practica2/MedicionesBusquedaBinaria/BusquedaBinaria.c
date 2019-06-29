//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n numeroabuscar" (Linux y MAC OS)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

void BusquedaBinaria(int *, int, int);
double utime0, stime0, wtime0,utime1, stime1, wtime1;
int mitad, encontrado=0;

int main (int argc, char* argv[])
{	
		
	//double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	
	FILE *Numeros;  
    Numeros = fopen("10MOrdenados.txt", "r");
 
	int n,i, numero;
	
	n = atoi(argv[1]);
	numero = atoi(argv[2]);
	
	int *arr;
	
	arr = (int *) malloc(sizeof(int)*n);
	
	for (i = 0; i < n; i++)
      fscanf(Numeros,"%d",&arr[i]);     
    fclose(Numeros);

	//uswtime(&utime0, &stime0, &wtime0);
	
	BusquedaBinaria(arr,numero,n);

	//uswtime(&utime1, &stime1, &wtime1);
	
	//Cálculo del tiempo de ejecución del programa
	//printf("\n");
	//printf("%d\n",n);
	//printf("%d\n",numero);
	//printf("%d\n",mitad+1);
	//if(encontrado==0)
	//	printf("No\n");
	//else
	//	printf("Si\n");
	
	//printf("%.10f\n",  ((wtime1 - wtime0))*10000);
	printf("%.5f\n",  (utime1 - utime0)*100000);
	//printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	//printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	//printf("\n");

	//Terminar programa normalmente	
	exit (0);	
}

void BusquedaBinaria(int *A, int num, int n){
	int superior, inferior;

	inferior = 0;
	superior = n;

	/*while(inferior<=superior)
	{
		mitad = (inferior + superior)/2;

		if(A[mitad]==num){
			encontrado=1;
			break;
		}
		if(A[mitad]>num){
			superior=mitad;
			mitad=(superior+inferior)/2;
		}
		if(A[mitad]<num){
			inferior=mitad;
			mitad=(superior+inferior)/2;
		}
		
	}*/
uswtime(&utime0, &stime0, &wtime0);
	while((inferior <= superior) && (encontrado == 0)) 
	{
  		

  		mitad =(inferior+superior)/2;
  		
  		if(A[mitad]==num){
   			encontrado = 1;
  		}
  		else if(A[mitad]>num){
   			superior = mitad - 1;
  		}
  		else{
   			inferior = mitad + 1;
  		}
 	}
 	uswtime(&utime1, &stime1, &wtime1);
}
