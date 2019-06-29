
/*
    Ordenamiento heap
    Lee de un archivo de texto una cantidad de números desordenados y procede a ordenarlos utilizando el algoritmo heap sobre un arreglo
    04/03/19
    Versión 1.0
    Autores: Barriga Vargas Martín Eduardo, Ramírez Vives José Manuel, Salinas Núñez Jaime Alejandro
*/

//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include <iostream>
using namespace std;


#include <iostream>
using namespace std;

int obtenerIndiceHijoDerecho(int indicePadre){ // Recibe el valor del indice del padre y regresa el valor del índice del hijo derecho
    return (indicePadre*2 + 2);
}
int obtenerIndiceHijoIzquierdo(int indicePadre){ // Recibe el valor del indice padre y regresa el valor del indice del hijo izquierdo
    return (indicePadre*2 + 1);
}
int obtenerIndicePadre(int indiceHijo){ // Recibe el valor del indice hijo y regresa el valor del indice padre
    return (indiceHijo-1)/2 ;
}
bool tieneHijoIzquierdo (int indicePadre, int tam){ // Recibe el valor del indice padre y regresa un valor boleano dependiendo si tiene o no hijo izquierdo, comparando con la cantidad de elementos que tenemos en el arreglo
    if( obtenerIndiceHijoIzquierdo(indicePadre) < tam) return true;
    return false;
}
bool tieneHijoDerecho (int indicePadre, int tam){ // Recibe el valor del indice padre y regresa un valor boleano dependiendo si tiene o no hijo derecho, comparando con la cantidad de elementos que tenemos en el arreglo
    if( obtenerIndiceHijoDerecho(indicePadre) < tam) return true;
    return false;
}
bool tienePadre (int indiceHijo){ // Recibe el valor del indice hijo y regresa un valor booleano dependiendo si tiene padre o no, es decir si es el nodo raiz o no, simplemente observando si el ínidice de él mismo es mayor o igual a 0
    if( obtenerIndicePadre(indiceHijo) >= 0 ) return true;
    return false;
}
int obtenerHijoDerecho(int *ar, int indicePadre){ // Recibe un apuntador al arreglo y el índice padre, regresa el valor del hijo derecho, primero obteniendo su índice con uso de la función obtenerIndiceHijoDerecho
    return ar[obtenerIndiceHijoDerecho(indicePadre)];
}
int obtenerHijoIzquierdo(int *ar, int indicePadre){ // Recibe un apuntador al arreglo y el índice padre, regresa el valor del hijo izquierdo, primero obteniendo su índice con uso de la función obtenerIndiceHijoIzquierdo
    return ar[obtenerIndiceHijoIzquierdo(indicePadre)];
}
int obtenerPadre(int *ar, int indiceHijo){ // Recibe un apuntador al arreglo y el indice de uno de los hijos, regresa el valor del padre utilizando la función obtenerIndice padre primero
    return ar[obtenerIndicePadre(indiceHijo)];
}
void cambiar(int *ar, int indicePadre, int indiceHijo){ // Recibe un apuntador al arreglo, el indice padre y el indice hijo que se desean intercambiar entre ellos
    int valor = ar[indicePadre]; //Se hace el intercambio haciendo uso de una variable auxiliar
    ar[indicePadre] = ar[indiceHijo];
    ar[indiceHijo] = valor;
}
void ajustarHaciaAbajo(int *ar, int tam){ // Se recibe un apuntador al arreglo y su tamaño, es decir la cantidad de datos dentro de nuestro arreglo para hacer un ajuste hacia abajo en caso de que se acabe de sacar el nodo raiz 
    int indice = 0, indiceDelHijoMenor;
    while (tieneHijoIzquierdo(indice, tam)) // Se va a repetir el while hasta haber llegado a una hoja o a un break dentro del while
    {
        indiceDelHijoMenor = obtenerIndiceHijoIzquierdo(indice);  // asignamos el valor del hijo izquierdo a indice menor, pues no siempre existirá un hijo derecho, sin embargo siempre existirá el hijo izquierdo
        if(tieneHijoDerecho(indice, tam) && obtenerHijoDerecho(ar, indice) < ar[indiceDelHijoMenor]){ // Si tiene un hijo derecho y además su valor es menor al que teníamos asignado en hijo menor se intercambian los valores
            indiceDelHijoMenor = obtenerIndiceHijoDerecho(indice);
        }
        if(ar[indiceDelHijoMenor] > ar[indice]) break; // Si ninguno de los hijos es menor que el padre entonces se rompe el while con un break
        else {
            cambiar(ar, indice, indiceDelHijoMenor); // En caso contrario, se intercambian los valores y de estos dos y ahora nuestro nuevo indice, será el que tenía el hijo menor, así podremos ir avanzando hasta llegar a la posicion correspondiente para ese valor
            indice = indiceDelHijoMenor;
        }
    }
}
void ajustarHaciaArriba(int *ar, int tam){ // Se recibe un apuntador al arreglo, el tamaño que tiene el arreglo
    int indice = tam-1;
    while(tienePadre(indice) && obtenerPadre(ar, indice)  > ar[indice]){ // Mientras tenga padre y este tenga un valor mayor al que yo tengo entonces cambiaremos lugares, pues el que tenemos no era el correspondiente
        cambiar(ar, obtenerIndicePadre(indice), indice); // se cambian los valores
        indice = obtenerIndicePadre(indice); // nuestro nuevo indice en el arreglo, será el que tenía el padre para así poder seguir buscando hasta llegar a la posicion correspondiente
    }

}
int sacarRaiz(int *ar, int *tam){ // Se  recibe un apuntador a arreglo y apuntador a tamaño
    int valorRaiz = ar[0]; // sacamos la raiz
    ar[0] = ar[*tam-1]; // le asignamos la última hoja ingresada
    (*tam)--;
    ajustarHaciaAbajo(ar, *tam); // ajustamos hacia abajo para encontrar el valor que debe de tener la nueva raiz
    return valorRaiz;
}
void agregar(int *ar, int valor, int *tam){ 
    ar[*tam] = valor; // se le asigna una hoja a nuestro arreglo
    (*tam)++; //incrementamos el numero de elementos que tenemos en el arreglo
    ajustarHaciaArriba(ar, *tam);// agregamos un valor a la hoja y tratamos de encontrar su posicion ajustando hacia arriba
}
void ordenamientoHeap(int *arES, int *ar, int tamano){
    int tam = 0, i;
    for(i = 0 ; i < tamano; i++){ //Agregamos todos los valores del arreglo a nuestro arreglo de ordenamiento
        agregar(ar, arES[i], &tam);
    }
    for( i = 0; i < tamano; i++){
        arES[i] = sacarRaiz(ar, &tam); // sacamos el valor que tenga la raiz, siempre asegurando que es la menor
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
 
	int tamano;
	tamano=atoi(argv[1]);

	int num,i, *arES, *ar;
    //cin >> tamano;
    arES = (int *) malloc(sizeof(int)*tamano);
    ar = (int *) malloc(sizeof(int)*tamano);
    
    for(i = 0; i < tamano; i++){
        //cin >> num;
        fscanf(Numeros,"%d",&num);
        arES[i] = num;
        
    }
    fclose(Numeros);

    uswtime(&utime0, &stime0, &wtime0);

    ordenamientoHeap(arES, ar, tamano);   //ESTE ES EL ALGORITMO

    uswtime(&utime1, &stime1, &wtime1);

    for( i = 0; i < tamano; i++){
    //    cout << arES[i] << " \n";
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

