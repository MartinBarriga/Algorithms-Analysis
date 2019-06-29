#include <iostream>
#include <string>
using namespace std;
void palabra(int i, int j, string a, string b){
    cout << a << endl;
    if(j < b.size()){
        palabra(i, j+1, a,b);
        a.push_back(b[j]);
        palabra(i+1, j+1, a, b);
    }
   
}
int main(){
    string x,y;
    cin >> x ;
    palabra(0,0,"",x);
    return 0;
}