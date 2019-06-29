
/*
    Búsqueda con Árbol Binario
	Lee de un archivo de texto una cantidad de úmeros desordenados y procede a elaborar el árbol, donde el hijo izquierdo siempre será menor que el padre y el hijo derecho será mayor que el padre.. 
	Después se toma el tiempo que tarda en buscar un número deseado en los nodos del árbol.
	04/04/2019
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

struct nodo { //Estructura encargada de almacenar un valor entero, un nodo izquierdo y un nodo derecho, los cuales son del mismo tipo que la estructura
	int dato; 
	nodo* izq;
	nodo* der;
};

nodo* crearNodo(int dato) { //Recibe el dato que se va a introducir en el nodo que está por crearse, devuelve un valor tipo nodo (el nodo que ha sido creado)
	nodo* nuevoNodo = new nodo(); // se crea una instancia
	nuevoNodo->dato = dato; // se le asigna al nodo el parametro recibido 
	nuevoNodo->izq = nuevoNodo->der = NULL; //tanto a los nodos izquierdo y derecho se les asigna null, pues actualmente no sabemos si deben crearse
	return nuevoNodo; //regresamos el nodo creado
}

nodo* insertar(nodo* raiz,int dato) { //Recibimos el nodo raiz y el dato que le insertaremos, duevelve el nodo raiz
	if(raiz == NULL) {  // si el nodo recibido es nulo entonces significa que estamos en un nodo izquierdo o derecho
		raiz = crearNodo(dato); //por lo tanto creamos un nodo y se lo asignamos al nodo actual
	}
	else if(dato <= raiz->dato) { //si el dato es menor o igual al valor del nodo en el que estamos parados entonces nos dirijimos a su hijo izquierdo
		raiz->izq = insertar(raiz->izq,dato); // llamamos recursivamente a la función para seguir buscando, y nos regresará la parte izquierda del nodo ya editado
	}
	else { //si el dato es mayor entonces pertenece a la rama derecha del nodo en el que nos encontramos
		raiz->der = insertar(raiz->der,dato);// llamamos recursivamente a la función para seguir buscando, y nos regresará la parte derecha del nodo ya editado
	}
	return raiz; //regresamos el nodo editado
}

nodo* recorridoInsertar(int *arES, int tamano, nodo *raiz){ //Recibimos el nodo raiz, un arreglo y el tamaño del arreglo, devolvemos un nodo, el cuál es la raiz del arbol
    int i, indice =0;
    for(i = 0; i < tamano; i++)  //recorremos el arreglo
    { 
        raiz = insertar(raiz, arES[i]); //por cada elemento en el arreglo mandamos a llamar la función insertar con el valor que tiene el arreglo en el indice indicado y la raiz del árbol, guardamos la raiz del árbol con el nodo ya añadido
    }
    return raiz; //regresamos la raiz del árbol
}	

int busqueda(nodo *raiz, int numBusq){ //Recibimos el nodo raiz de nuestro árbol y nuestro número a buscar, regresamos un entero indicando si se encontró o no el número
    if(raiz == NULL) return 0;  //Si el nodo que acabo de recibir es nulo, entonces significa que el número no está y regresamos un 0. Si el número estuviera ya hubiera aparecido antes
    if(raiz->dato == numBusq) return 1; //Si el dato del nodo en el que estoy parado es igual al que estoy buscando entonces regresamos un 1, indicando que sí se encuentra
	if(numBusq > raiz->dato) {//Si el número buscando es más grande que el valor del nodo en el que estoy parado entonces me dirijo a su nodo derecho
		return busqueda(raiz->der, numBusq); //regreso el valor que obtenga de haber buscado en el nodo derecho
	}
	else {
		return busqueda(raiz->izq,numBusq);//regreso el valor que obtenga de haber buscado en el nodo izquierdo
	} 
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

	int tamano,num, *arES,res,numBusq;

	tamano=atoi(argv[1]); //leemos el tamaño
	numBusq = atoi(argv[2]);//leemos el numero que vamos a buscar
    arES = (int *) malloc(sizeof(int)*tamano); //creamos un arreglo dinámico
	
	nodo* raiz = NULL; //creamos un nodo raiz con un valor nulo

	for(int i=0; i< tamano; i++) // leemos todos los números del archivo de texto y se guardan en un arreglo
	{
		fscanf(Numeros,"%d",&num);  
        //cin >> num;
        arES[i] = num;
			
	}	
    fclose(Numeros);

	raiz = recorridoInsertar(arES, tamano, raiz); //llamamos a una función para insertar nuestros valores del arreglo en nuestra raíz, mandando la raiz, el arreglo y su tamaño 
	uswtime(&utime0, &stime0, &wtime0);    
    res =  busqueda(raiz, numBusq); //mandamos a llamar a la función búsqueda con la raiz de nuestro árbol y el número a buscar. Guardamos el valor que regresa la función, representando si se encuentra o no el valor en el árbol
    uswtime(&utime1, &stime1, &wtime1);
	

	//Cálculo del tiempo de ejecución del programa
	printf("%.10f\n",  ((wtime1 - wtime0))*10000);
	//printf("%.10f\n",  utime1 - utime0);
	//if(res == 0) cout << "No" << endl;
	//else cout << "Si" << endl;
	//printf("%.10f s\n",  stime1 - stime0);
	//printf("%.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	//printf("\n");
	
	//******************************************************************
	//Terminar programa normalmente	
	exit (0);	
}


