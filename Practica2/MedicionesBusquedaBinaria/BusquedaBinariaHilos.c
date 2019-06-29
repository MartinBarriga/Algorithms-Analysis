//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n numeroabuscar" (Linux y MAC OS)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include <pthread.h>

struct Parametros{
	int ni;
	int ns;
	int num;
	int *A;
};

double utime0, stime0, wtime0,utime1, stime1, wtime1;
int encontrado=0;

void BusquedaBinariaHilos(struct Parametros *parametros){
	int superior, inferior;
	int mitad;

	inferior = parametros->ni;
	superior = parametros->ns;

		while((inferior <= superior) && (encontrado == 0)) 
		{
  			mitad =(inferior+superior)/2;
  		
  			if(parametros->A[mitad]==parametros->num){
   				encontrado = 1;
  			}
  			else if(parametros->A[mitad]>parametros->num){
   				superior = mitad - 1;
  			}
  			else{
   				inferior = mitad + 1;
  			}
 		}

} 		

int main (int argc, char* argv[])
{	
	
	FILE *Numeros;  

	int n, i, numero, *arr;

	pthread_t Hilo1,Hilo2,Hilo3;
	
	Numeros = fopen("10MOrdenados.txt", "r");
	
	n = atoi(argv[1]);
	numero = atoi(argv[2]);
	
	arr = (int *) malloc(sizeof(int)*n);
	
	for (i = 0; i < n; i++)
      fscanf(Numeros,"%d",&arr[i]);     
    fclose(Numeros);
	
	struct Parametros param1 = {n*(2/3),n,numero,arr};
	struct Parametros param2 = {n*(1/3),n*(2/3),numero,arr};
	struct Parametros param3 = {0,n*(1/3),numero,arr};

	uswtime(&utime0, &stime0, &wtime0);

	pthread_create(&Hilo1,NULL, (void*)BusquedaBinariaHilos, (void*)&param1);
	pthread_create(&Hilo2,NULL, (void*)BusquedaBinariaHilos, (void*)&param2);
	pthread_create(&Hilo3,NULL, (void*)BusquedaBinariaHilos, (void*)&param3);

	pthread_join(Hilo1, NULL);
	pthread_join(Hilo2, NULL);
	pthread_join(Hilo3, NULL);

 	uswtime(&utime1, &stime1, &wtime1);
	
	//Cálculo del tiempo de ejecución del programa
	//printf("\n");
	//printf("%d\n",n);
	//printf("%d\n",numero);
	//printf("%d\n",mitad+1);
	//if(encontrado==0)
	//	printf("No\n");
	//else
	//	printf("Si\n");
	
	printf("%.10f\n",(wtime1 - wtime0)*10000);
	//printf("%.5f\n",  (utime1 - utime0)*10000);
	//printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	//printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	//printf("\n");

	//Terminar programa normalmente	
	exit (0);	
}
