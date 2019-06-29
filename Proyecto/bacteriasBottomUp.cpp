#include <iostream>
#include <vector>
using namespace std;
vector <int> arr(101, 90001);
vector <vector <int> > mat(101, arr);
int bacterias(int m, int n){
    for(int i = m-1; i >=0; i--){
        for(int j = n-1; j >=0; j--){
            if(i != m-1 || j!= n-1) mat[i][j] += min(mat[i+1][j], mat[i][j+1]);  
        }
    }
    return mat[0][0];
}
int main(){
    int n, m;
    cin >> m >> n;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> mat[i][j];
        }
    }
     cout << bacterias(m, n) << endl;
   
    return 0;
}