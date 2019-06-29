#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>

using namespace std;


int main(){
    long long int casos, numBichos, Bvida, Bdmg, Bputazos, indice;
    long long int Hvida, Hdmg;
    vector<tuple< double, long long int, long long int>> bichos;
    cin >> casos;
    
    for(int x = 0; x < casos; x++){
        cin >> Hvida >> Hdmg;
        cin >> numBichos;
        for(int y = 0; y < numBichos; y++){
            cin >> Bvida >> Bdmg;
            if(Bvida > Hdmg){
                if(Bvida % Hdmg == 0){
                    Bputazos = Bvida / Hdmg;
                }
                else{
                    Bputazos = Bvida/Hdmg +1;
                }
            }
            else{
                Bputazos = 1;
            }
            bichos.push_back(make_tuple( Bdmg/Bputazos, Bdmg, Bputazos));
        }
        sort(bichos.begin(), bichos.end());
        ////
        indice = numBichos-1;
        long long int putazosAcum = 0;
        while(Hvida>0 && indice >=0){
           // cout << "El heroe con " << Hvida;
            putazosAcum += get<2>(bichos[indice]);
            Hvida -= get<1>(bichos[indice])* putazosAcum;
            indice --;
            //cout << " se enfrenta a un mounstro que le va a meter " << putazosAcum << " putazos. El heroe queda con " << Hvida << " Puntos de vida" << endl;

        }
        if(Hvida > 0){
            cout << Hvida << endl;
        }
        else cout << "NO" << endl;
        bichos.clear();
    }
    cout << endl;
    return 0;
}
