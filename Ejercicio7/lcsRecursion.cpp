#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> arr(1001, -1);
vector<vector<int> > mat(1001, arr);
int lcs(int i, int j, string x, string y){
    if(mat[i][j] != -1) return mat[i][j];
    if( i == x.size() || j == y.size() ){
        mat[i][j] =0;
        return mat[i][j]; 
    } 
    
    else if(x[i] == y[j]) 
    {
        mat[i][j] = 1 + lcs(i+1, j+1, x, y);
        return mat[i][j];
    }
    else{
        int indicex, indicey;
        indicex = lcs (i+1, j, x, y);
        indicey =  lcs(i, j+1, x, y);
        if( indicex > indicey ){
            mat[i][j] = indicex;
        }
        else{
            mat[i][j] = indicey;
        }
        return  mat[i][j];
    }
}
int main(){
    string x,y;
    cin >> x >> y;

    int resultado = lcs(0,0,x,y);
    for(int i =0;  i <=x. size(); i++){
        for(int j = 0; j <= y.size(); j++){
            cout << mat[i][j] << " ";    
        }
        cout << endl;
    }
    cout << resultado << endl;
    return 0;
}