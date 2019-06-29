#include <iostream>
#include <vector>
#include <set>
#include <iterator>
using namespace std;
int columna1[10000], columna2[10000];
int indiceC=0;
int orden(int *ar, int n){
    int cambios = 0, i;
    set <int> unos;
    set <int> dos;
    set <int> tres;
    set<int>::iterator posicion;

    //insertamos en los sets los índices de los números que vayamos encontrando
    for( i = 0; i < n; i++){
        if(ar[i] == 1) unos.insert(i);
        else if(ar[i] == 2) dos.insert(i);
        else tres.insert(i);
    }
    //recorremos el vector que contiene los números desordenados
    for( i = 0; i < n; i++){
        //si aún hay valores en nuestro set de unos entramos en este if
        if(unos.size()>0){
            if(ar[i] == 1){ //preguntamos si el número en el que estamos parados es un uno, si lo es simplemente eliminamos el primer indice del set de unos
                posicion = unos.begin();
                unos.erase(*posicion);
            }
            else if(ar[i] == 2){ // preguntamos si el número es un dos, en ese caso haremos el cambio de números tanto en el arreglo, así como la eliminación del inicio en el set de unos y el final de dos. Luego agregamos en el set de dos, la posición en la que se encontraba el uno que cambiamos
                posicion = unos.end();
                posicion--;
                ar[i] = 1;
                ar[*posicion] = 2;
                columna1[indiceC] = i+1; //agregamos nuestros indices de respuesta a los arreglos
                columna2[indiceC] = *posicion+1;
                indiceC++;
                posicion = dos.begin();
                dos.erase(*posicion);
                posicion = unos.end();
                posicion--;
                dos.insert(*posicion);
                unos.erase(*posicion);
                cambios++;
            }
            else { // si entra aquí significa que el número era un tres, hacemos lo mismo que cuando encontramos el dos
                posicion = unos.end();
                posicion--;
                ar[i] = 1;
                ar[*posicion] = 3;
                columna1[indiceC] = i+1;  //agregamos nuestros indices de respuesta a los arreglos
                columna2[indiceC] = *posicion+1;
                indiceC++;
                posicion = tres.begin();
                tres.erase(*posicion);
                posicion = unos.end();
                posicion--;
                tres.insert(*posicion);
                unos.erase(*posicion);
                cambios++;
            }
        }
         //si no hay valores en nuestro set de unos pero si hay valores en nuestro set de dos entramos en este else
        else if(dos.size()>0){
            if(ar[i] == 2) { //preguntamos si el número en el que estamos parados es un dos, si lo es simplemente eliminamos el primer indice del set de dos
                posicion = dos.begin();
                dos.erase(*posicion);
            }
            else{         //Si entra aquí significa que hay un tres, pues los unos se suponen que para este entonces ya no los vamos a topar. Hacemos los cambios en el arreglo
                posicion = dos.end();
                posicion--;
                ar[i] = 2;
                ar[*posicion] = 3;
                columna1[indiceC] = i+1; //agregamos nuestros indices de respuesta a los arreglos y la eliminación del inicio en el set de dos y el final de tres. Luego agregamos en el set de tres, la posición en la que se encontraba el dos que cambiamos
                columna2[indiceC] = *posicion+1;
                indiceC++;
                posicion = tres.begin();
                tres.erase(*posicion);
                posicion = dos.end();
                posicion--;
                tres.insert(*posicion);
                dos.erase(*posicion);
                cambios ++;
            }
        }
    }
    return cambios;
}
int main(){
    int n,i;
    cin >> n;
    int num[n];
    for( i = 0; i < n; i++){
        cin >> num[i];
    }
    cout << orden(num, n) << endl;
    for( i = 0; i < indiceC; i++){
        cout << columna1[i] << " " << columna2[i] << endl;
    }
    return 0;
}