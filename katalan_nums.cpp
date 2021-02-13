#include<iostream>
#include<vector>

using namespace std;

const int mod = 1e9 + 7;

int fpow(int a, int n){
    if(n == 0)return 1;
    else if(n % 2 == 1){
        return (long long int)a * fpow(a, n - 1) % mod;
    }else{
        return fpow((long long int)a * a % mod, n / 2);
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> fact(2 * n + 1, 1);
    for(int i = 1; i <= 2 * n; i++){
        fact[i] = ((long long int)fact[i - 1] * i) % mod;
    }
    int s = ((long long int)fact[n] * fact[n + 1]) % mod;
    int second = (fpow(s, mod - 2));
    cout << ((long long int)fact[2 * n] * second) % mod;
    return 0;
}
