#include<iostream>
#include<algorithm>
#include<map>
#include<vector>

using namespace std;


int main(){
    long long int k, n;
    cin >> n >> k;
    vector<vector<long long int>> dp(2 * n + 1, vector<long long int>(n + 2, 0));
    dp[2 * n][0] = 1;
    for (long long int pos = 2 * n - 1; pos >= 0; --pos) {
        for (long long int bal = 0; bal <= n; ++bal) {
            dp[pos][bal] = dp[pos + 1][bal + 1];
            if (bal != 0){
                dp[pos][bal] += dp[pos + 1][bal - 1];
            }
        }
    }
    if (k >= dp[0][0])cout << "N/A";
    else{
        int bal = 0;
        string s;
        for (int i = 0; i < 2 * n; i++){
            if (k < dp[i + 1][bal + 1]){
                s.push_back('(');
                bal++;
            }else{
                s.push_back(')');
                k -= dp[i + 1][bal + 1];
                bal--;
            }
        }
        cout << s;
    }
    return 0;
}
