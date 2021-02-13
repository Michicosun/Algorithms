#include<iostream>
#include<algorithm>
#include<map>
#include<vector>

using namespace std;


int main(){
    int n = 8;
    vector<vector<long long int>> pr(n, vector<long long int>(n, 0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> pr[i][j];
        }
    }
    for (int i = 2; i <= n; i++){
        pr[n - i][0] += pr[n - i + 1][0];
    }
    for (int i = 1; i < n; i++){
        pr[n - 1][i] += pr[n - 1][i - 1];
    }
    for (int i = n - 2; i >= 0; i--){
        for (int j = 1; j < n; j++){
            pr[i][j] = min(pr[i][j - 1], min(pr[i + 1][j - 1], pr[i + 1][j])) + pr[i][j];
        }
    }
    cout << pr[0][7];
    return 0;
}
