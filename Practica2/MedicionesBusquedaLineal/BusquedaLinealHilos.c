#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "tiempo.h"

/*
    Búsqueda Lineal Con Hilos
    Lee de un archivo de texto una cantidad de números desordenados, los guarda en un arreglo y procede a realizar una búsqueda utilizando hilos, indicándole a cada hilo con ayuda de estructuras qué porción del arreglo buscará
    04/04/2019
    Versión 1.0
    Autores: Barriga Vargas Martín Eduardo, Ramírez Vives José Manuel, Salinas Núñez Jaime Alejandro
*/


//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************

struct Parametros{ //Estructura elaborada para guardar el contenido de los datos necesarios para hacer la búsqueda del número, los cuales son: El inicio de donde debemos empezar a buscar, el final, el número buscado, el arreglo en el que se encuentran los números y una variable que representa si ya se encontró el dato
	int inicio;
    int fin;
	int numBuscado;
	int *ar;
    int encontrado;
};


void buscarNumero(struct Parametros *parametros){ //Se encarga de buscar el número en un rango, recibe una estructura tipo parámetro y no regresa nada
    int i,tam = parametros->fin; //se le asigna a la variable tam el valor fin, que dice hasta donde debe de dejar de buscar
    for(i = parametros->inicio; i < tam; i++){ //Hacemos un recorrido del valor inicio que viene en parámetros hasta tam
        if(parametros->ar[i] == parametros->numBuscado) { //Si encontramos el número buscado en el arreglo entonces modificamos el valor de encontrado y rompemos el ciclo
            parametros->encontrado = 1;
            break;
        }
    }
    //en caso de que no se haya encontrado el número, el valor encontrado se queda en 0
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
    pthread_t Hilo1,Hilo2; //Creamos nuestros hilos
    Numeros = fopen("numeros10millones.txt", "r");
    int i,tamano, *ar, resultado,num,numBusq;

    tamano=atoi(argv[1]); //leemos el tamaño
	numBusq = atoi(argv[2]);//leemos el número a buscar


    ar = (int *) malloc(sizeof(int)*tamano);//Creamos un arreglo dinámico en el que vamos a guardar los números
    for(i=0; i < tamano; i++){ //Se recorre el archivo e introducimos los números en el arreglo
        fscanf(Numeros,"%d",&num);  
        ar[i] = num;
    }
    fclose(Numeros);

    struct Parametros param1 = {0,tamano/2,numBusq,ar,0};//Creamos una instancia tipo parámetros en el que indicamos que el punto de inicio es 0, el fin de búsqueda es el tamaño entre dos, le indicamos el número a buscar y le asignamos el valor 0 a la variable "encontrado"
	struct Parametros param2 = {tamano/2,tamano,numBusq,ar,0}; //Creamos una instancia tipo parámetros en el que indicamos que el punto de inicio es tamaño entre dos, el fin de búsqueda es el tamaño, le indicamos el número a buscar y le asignamos el valor 0 a la variable "encontrado"

    uswtime(&utime0, &stime0, &wtime0); //Comenzamos a medir el tiempo
    	pthread_create(&Hilo1,NULL, (void*)buscarNumero, (void*)&param1); //creamos el hilo1, indicándole la instancia, null, la función que ejecutará y la estructura que le enviará a dicha función
	    pthread_create(&Hilo2,NULL, (void*)buscarNumero, (void*)&param2); //creamos el hilo2, indicándole la instancia, null, la función que ejecutará y la estructura que le enviará a dicha función
        pthread_join(Hilo1, NULL);//Ejecutamos el hilo1
	    pthread_join(Hilo2, NULL);//Ejecutamos el hilo2
    uswtime(&utime1, &stime1, &wtime1);//Finalizamos la medición de tiempo

    //Cálculo del tiempo de ejecución del programa
	printf("%.10f\n",  ((wtime1 - wtime0))*10000);
	//printf("%.10f\n",  utime1 - utime0);
	/*if(param1.encontrado == 1 || param2.encontrado==1){
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