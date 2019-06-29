/*
    Búsqueda con Árbol Binario Con Hilos
	Lee de un archivo de texto una cantidad de úmeros desordenados y procede a elaborar el árbol, donde el hijo izquierdo siempre será menor que el padre y el hijo derecho será mayor que el padre.. 
	Después se toma el tiempo que tarda en buscar un número deseado en los nodos del árbol utilizando dos hilos, uno que se encarga de analizar lo que está del lado izquierdo del árbol y otro que se encarga de analizar todo el lado derecho del árbol
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
#include <pthread.h>

struct nodo {  //Estructura encargada de almacenar un valor entero, un nodo izquierdo y un nodo derecho, los cuales son del mismo tipo que la estructura
	int dato; 
	struct nodo* izq;
	struct nodo* der;
};
struct Parametros{ //Estructura encargada de guardar la raiz de nuestro árbol, el número a bucar y un indicador de si se encontró o no el número
    struct nodo* raiz; 
	int numBusq;
	int encontrado;
};

struct nodo* crearNodo(int dato) {//Recibe el dato que se va a introducir en el nodo que está por crearse, devuelve un valor tipo nodo (el nodo que ha sido creado)
	struct nodo* nuevoNodo = malloc(sizeof(struct nodo)); // se crea una instancia
	nuevoNodo->dato = dato;// se le asigna al nodo el parametro recibido 
	nuevoNodo->izq = nuevoNodo->der = NULL; //tanto a los nodos izquierdo y derecho se les asigna null, pues actualmente no sabemos si deben crearse
	return nuevoNodo;//regresamos el nodo creado
}

struct nodo* insertar(struct nodo* raiz,int dato) {//Recibimos el nodo raiz y el dato que le insertaremos, duevelve el nodo raiz
	if(raiz == NULL) { // si el nodo recibido es nulo entonces significa que estamos en un nodo izquierdo o derecho
		raiz = crearNodo(dato);//por lo tanto creamos un nodo y se lo asignamos al nodo actual
	}
	else if(dato <= raiz->dato) { //si el dato es menor o igual al valor del nodo en el que estamos parados entonces nos dirijimos a su hijo izquierdo
		raiz->izq = insertar(raiz->izq,dato); // llamamos recursivamente a la función para seguir buscando, y nos regresará la parte izquierda del nodo ya editado
	}
	else {//si el dato es mayor entonces pertenece a la rama derecha del nodo en el que nos encontramos
		raiz->der = insertar(raiz->der,dato); // llamamos recursivamente a la función para seguir buscando, y nos regresará la parte derecha del nodo ya editado
	}
	return raiz;//regresamos el nodo editado
}

struct nodo* recorridoInsertar(int *arES, int tamano, struct nodo *raiz){ //Recibimos el nodo raiz, un arreglo y el tamaño del arreglo, devolvemos un nodo, el cuál es la raiz del arbol
    int i, indice =0; 
    struct nodo *nuevoNodo = NULL;//recorremos el arreglo
    for(i = 0; i < tamano; i++) 
    { 
        raiz = insertar(raiz, arES[i]);//por cada elemento en el arreglo mandamos a llamar la función insertar con el valor que tiene el arreglo en el indice indicado y la raiz del árbol, guardamos la raiz del árbol con el nodo ya añadido
    }
    return raiz; //regresamos la raiz del árbol
}	


void busqueda( struct Parametros *parametros){ //Se encarga de buscar el número y recibe como parámetro una estructura tipo parámetros con toda la información dentro
    
    if(parametros->raiz == NULL){ //Si el nodo que acabo de recibir es nulo, entonces significa que el número no está y regresamos un 0. Si el número estuviera ya hubiera aparecido antes
		
	}
    else if(parametros->raiz->dato == parametros->numBusq){ //Si el dato del nodo actual es igual al valor que estamos buscando entonces actualizamos el valor de "encontrado" a 1
		parametros->encontrado = 1;
	}
	else if(parametros->numBusq > parametros->raiz->dato) {//En caso de que el número buscado sea mayor que el dato que guarda el nodo en el que estamos parados le asignamos al nodo el valor de nuestra raiz derecha y mandamos a buscar nuevamente 
		parametros->raiz = parametros->raiz->der;
		busqueda(parametros); 
	}
	else if(parametros->numBusq < parametros->raiz->dato){//En caso de que el número buscado sea menor que el dato que guarda el nodo en el que estamos parados le asignamos al nodo el valor de nuestra raiz izquierda y mandamos a buscar nuevamente 
		parametros->raiz = parametros->raiz->izq;
		busqueda(parametros);
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
	pthread_t Hilo1,Hilo2; //Declaramos los hilos
	FILE *Numeros;  
	
    Numeros = fopen("numeros10millones.txt", "r");

	int tamano,num, *arES,res,numBusq;

	tamano=atoi(argv[1]);//leemos el tamaño
	numBusq = atoi(argv[2]);//leemos el numero que vamos a buscar
    arES = (int *) malloc(sizeof(int)*tamano);//creamos un arreglo dinámico
	
	struct nodo* raiz = NULL;//creamos un nodo raiz con un valor nulo

	for(int i=0; i< tamano; i++) // leemos todos los números del archivo de texto y se guardan en un arreglo
	{
		fscanf(Numeros,"%d",&num);   
        //cin >> num;
        arES[i] = num;
			
	}	
    fclose(Numeros);
	raiz = recorridoInsertar(arES, tamano, raiz);  //llamamos a una función para insertar nuestros valores del arreglo en nuestra raíz, mandando la raiz, el arreglo y su tamaño 
	struct Parametros param1 = {raiz->izq, numBusq,0}; //Instanciamos una estructura de tipo Parametros, le mandamos el nodo iquierdo del árbol, el numero a buscar y un valor 0 indicando que aún no se ha encontrado el número
	struct Parametros param2= {raiz->der, numBusq,0};//Instanciamos una estructura de tipo Parametros, le mandamos el nodo derecho del árbol, el numero a buscar y un valor 0 indicando que aún no se ha encontrado el número
	uswtime(&utime0, &stime0, &wtime0);   
	if(raiz->dato != numBusq){ //En caso de que el número que nos piden buscar no sea la raiz utiliamos un hilo para buscar del lado del nodo izquierdo del árbol y otro hilo para bucar del lado derecho
    	pthread_create(&Hilo1,NULL, (void*)busqueda, (void*)&param1); //Creamos los hilos, mandando como parámetros la función y sus estructuras parámetros correspondientes
		pthread_create(&Hilo2,NULL, (void*)busqueda, (void*)&param2);
		pthread_join(Hilo1, NULL);//Ejecutamos los hilos
		pthread_join(Hilo2, NULL);
	}
    uswtime(&utime1, &stime1, &wtime1);
	

	//Cálculo del tiempo de ejecución del programa
	printf("%.10f\n",  ((wtime1 - wtime0))*10000);
	/*printf("%.10f\n",  utime1 - utime0);
	if(res == 0) cout << "No" << endl;
	else cout << "Si" << endl;
	printf("%.10f s\n",  stime1 - stime0);
	printf("%.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");*/
	
	//******************************************************************
	//Terminar programa normalmente	
	exit (0);	
}