#include<iostream>
#include<algorithm>
#include<set>
#include<vector>

using namespace std;

const int mod = 1e9 + 7;

int din(vector<vector<int>> dp, int n, int k){
    if (k == 0)return 0;
    for (int pos = 2 * n - 1; pos >= 0; --pos) {
        for (int bal = 0; bal <= n; ++bal) {
            if (bal == k)dp[pos][bal] = ((long long int)dp[pos][bal] + dp[pos + 1][bal - 1]) % mod;
            else{
                dp[pos][bal] = (long long int)dp[pos + 1][bal + 1] % mod;
                if (bal > 0) dp[pos][bal] = ((long long int)dp[pos][bal] + dp[pos + 1][bal - 1]) % mod;
            }
        }
    }
    return dp[0][0];
}

int main(){
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dp(2 * n + 1, vector<int>(n + 2, 0));
    dp[2 * n][0] = 1;
    cout << (din(dp, n, k) - din(dp, n, k - 1) + mod) % mod;
    return 0;
}
