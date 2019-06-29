#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"

/*
    Búsqueda Lineal
    Versión 1.0
    Autores: Barriga Vargas Martín Eduardo, Ramírez Vives José Manuel, Salinas Núñez Jaime Alejandro
*/


//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************


int buscarNumero(int *ar, int tam, int numBuscado){ //Se encarga de buscar el número, recibe el arreglo, su tamaño y el numero a buscar, devuelve un entero indicando si se encontró o no el número
    for(int i = 0; i < tam; i++){//Se recorre el arreglo
        if(ar[i] == numBuscado) return i; //Si el número del arreglo corresponde con el número buscado se regresa un número indicando la posición del arreglo
    }
    return -1;//Si se llega hasta esta línea, se regresa un -1 indicando que no se encontró el número
}

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
    int i,tamano, *ar, resultado,num,numBusq;

    tamano=atoi(argv[1]); //lee el tamaño
	numBusq = atoi(argv[2]);//lee el número a buscar


    ar = (int *) malloc(sizeof(int)*tamano); //crea el arreglo dinámico
    for(i=0; i < tamano; i++){//Recorre el arreglo
        fscanf(Numeros,"%d",&num);   //lee el numero desde el archivo de texto y lo guarda en el arreglo
        ar[i] = num;
    }
    fclose(Numeros);

    uswtime(&utime0, &stime0, &wtime0);//Comienza a medir tiempos
    resultado = buscarNumero(ar, tamano, numBusq); //Llama a la función de búsqueda, mandando como parámetros el arreglo, su tamaño y el número a buscar, recibe un entero indicando si se encontró o no el número
    uswtime(&utime1, &stime1, &wtime1);//Finaliza la medición de tiempos

    //Cálculo del tiempo de ejecución del programa
	printf("%.10f\n",  ((wtime1 - wtime0))*10000);
	//printf("%.10f\n",  utime1 - utime0);
	/*if(resultado>=0){
        printf("Si\n");
    }
    else{
        printf("No\n");
    }*/
	//printf("%.10f s\n",  stime1 - stime0);
	//printf("%.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	//printf("\n");
	
	//******************************************************************
	//Terminar programa normalmente	
	exit (0);	
    
}