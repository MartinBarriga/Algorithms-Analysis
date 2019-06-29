
/*
    Ordenamiento con Árbol Binario de Búsqueda
    Lee de un archivo de texto una cantidad de números desordenados y procede a crear un árbol donde el hijo izquierdo siempre será menor que el padre y el hijo derecho será mayor que el padre.
    04/03/19
    Versión 1.0
    Autores: Barriga Vargas Martín Eduardo, Ramírez Vives José Manuel, Salinas Núñez Jaime Alejandro
*/


//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include <iostream>
using namespace std;

struct nodo {
	int dato; 
	nodo* izq;
	nodo* der;
};

nodo* crearNodo(int dato) { //Recibe un entero para crear un nodo que tiene un hijo izquierdo y derecho con un valor nulo, se le asigna a la variable dato del nodo el valor recibido
	nodo* nuevoNodo = new nodo();
	nuevoNodo->dato = dato;
	nuevoNodo->izq = nuevoNodo->der = NULL;
	return nuevoNodo;
}

nodo* insertar(nodo* raiz,int dato) { //Recibe el nodo raiz y un dato, se va desplazando en el árbol dependiendo si el dato recibido es menor o mayor que el valor del nodo en el que se encuentra, mándando llamar a la función pero ahora con alguno de los hijos como parámetro, una vez que se desplaza a un nodo que no está ocupado crea un nodo nuevo y luego regresa nuestro nodo raiz con el nodo nuevo ya incluido.
	if(raiz == NULL) {  
		raiz = crearNodo(dato);
	}
	else if(dato <= raiz->dato) {
		raiz->izq = insertar(raiz->izq,dato);
	}
	else {
		raiz->der = insertar(raiz->der,dato);
	}
	return raiz;
}

void inorden(nodo *raiz, int *arES, int *indice){ //Recibe el nodo raiz, un apuntador a el arreglo en el que guardaremos los datos ordenados y un índice que nos indica en qué posicón del arreglo debemos de meter el valor del nodo, hace un recorrido inorden pues tratará de llegar siempre al hijo máz izquierdo, pues este será el menor, luego regresará al padre y finalmente irá con el lado derecho, pues es el mayor de los tres. Todo esto de forma recursiva.
	if(raiz != NULL)
	{
		inorden(raiz->izq, arES, indice);
		arES[*indice] = raiz->dato;
        (*indice)++;
		inorden(raiz->der, arES, indice);
	}
}
void ordenamientoBST(int *arES, int tamano, nodo *raiz){ // Recibe un apuntador a arreglo que nos indica cuáles son los valores que tenemos que ordenar, el tamaño del arreglo, un nodo raiz que por ahora tiene valor de nulo pero que será la raiz de nuestro árbol
    int i, indice =0;
    for(i = 0; i < tamano; i++) //Recorremos el arreglo y cada uno de los valores lo vamos insertando en el nodo raiz
    { 
        raiz = insertar(raiz, arES[i]);
    }
    inorden(raiz, arES, &indice); // Mandamos a guardar en nuestro arreglo arEs los valores ya ordenados de nuestro árbol binario, para esto mandamos la raiz, el arreglo y un índice que indicará en que parte del arreglo debe guardarse el dato
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

	int tamano,num, *arES;

	tamano=atoi(argv[1]);

    arES = (int *) malloc(sizeof(int)*tamano);
	
	nodo* raiz = NULL;

	for(int i=0; i< tamano; i++) // leemos todos los números del archivo de texto y se guardan en un arreglo
	{
		fscanf(Numeros,"%d",&num);  
        //cin >> num;
        arES[i] = num;
			
	}	
    fclose(Numeros);

	uswtime(&utime0, &stime0, &wtime0);
    
    ordenamientoBST(arES, tamano, raiz); // Se manda a llamar al algoritmo que se encargará de todo el procedimiento, mandamos el arreglo con los datos, su tamaño y la raiz del árbol

    uswtime(&utime1, &stime1, &wtime1);
   
    for(int i=0; i< tamano; i++)
	{ 
     //   cout << arES[i] << " \n";		
	}	
	
	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("%d\n",tamano);
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


