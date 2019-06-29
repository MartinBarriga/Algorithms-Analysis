#include <iostream>
#include <vector>
using namespace std;
vector <int> primos(14);
vector <long long int> arr(15, -1);
vector < vector<long long int> > mat(1121, arr);
int n, k;
long long int calcular(int indice, int capacidad, int cantidad){
    
    if(indice >= 14 || capacidad-primos[indice]<0 || cantidad <0){
        return 0;
    }
    else if(capacidad-primos[indice] == 0){
        return 1;
    }
    else{
        return calcular(indice+1, capacidad-primos[indice], cantidad) + calcular(indice+1, capacidad, cantidad);
    }
}
int main(){
    long long int res;
    primos[0] = 2, primos[1] = 3, primos[2] = 5, primos[3] = 7, primos[4] = 11, primos[5] = 13, primos[6] = 17, primos[7] = 19, primos[8] = 23, primos[9] = 29, primos[10] = 31, primos[11] = 37, primos[12] = 41, primos[13] = 43;
    cin >> n >> k;
    while(n != 0 && k!=0){
        res = calcular(0, n, k);
        cout << res << endl; 
        cin >> n >> k;
    }
    return 0;
}