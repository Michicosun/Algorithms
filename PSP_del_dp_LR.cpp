#include<iostream>
#include<algorithm>
#include<map>
#include<vector>

using namespace std;

bool is_cur(char c, char c1){
    return (abs(c - c1) <= 2) && c != c1;
}

int main(){
    string s;
    cin >> s;
    s = ' ' + s;
    int n = (int)s.size();
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    vector<vector<string>> ans(n + 2, vector<string>(n + 2, ""));
    for (int len = 1; len <= n; len++){
        for (int l = 1; l <= n - len + 1; l++){
            int r = l + len - 1;
            if (s[l] == '(' || s[l] == '[' || s[l] == '{'){
                for (int m = l + 1; m <= r; m++){
                    if (is_cur(s[l], s[m])){
                        if (m >= 1 && l <= n && m <= n){
                            if (dp[l][r] < dp[l + 1][m - 1] + dp[m + 1][r] + 2){
                                dp[l][r] = dp[l + 1][m - 1] + dp[m + 1][r] + 2;
                                if (s[l] == '('){
                                    ans[l][r] = '(' + ans[l + 1][m - 1] + ')' + ans[m + 1][r];
                                }else if (s[l] == '['){
                                    ans[l][r] = '[' + ans[l + 1][m - 1] + ']' + ans[m + 1][r];
                                }else if (s[l] == '{'){
                                    ans[l][r] = '{' + ans[l + 1][m - 1] + '}' + ans[m + 1][r];
                                }
                            }
                        }
                    }
                }
            }
            if (s[r] == ')' || s[r] == ']' || s[r] == '}'){
                for (int m = r - 1; m >= l; m--){
                    if (is_cur(s[r], s[m])){
                        if (m >= 1 && m <= n && r >= 0){
                            if (dp[l][r] < dp[l][m - 1] + dp[m + 1][r - 1] + 2){
                                dp[l][r] = dp[l][m - 1] + dp[m + 1][r - 1] + 2;
                                if (s[r] == ')'){
                                    ans[l][r] = ans[l][m - 1] + '(' + ans[m + 1][r - 1] + ')';
                                }else if (s[r] == ']'){
                                    ans[l][r] = ans[l][m - 1] + '[' + ans[m + 1][r - 1] + ']';
                                }else if (s[r] == '}'){
                                    ans[l][r] = ans[l][m - 1] + '{' + ans[m + 1][r - 1] + '}';
                                }
                            }
                        }
                    }
                }
            }
            for (int m = l; m <= r; m++){
                if (dp[l][r] < dp[l][m] + dp[m + 1][r]){
                    if (m < n){
                        dp[l][r] = dp[l][m] + dp[m + 1][r];
                        ans[l][r] = ans[l][m] + ans[m + 1][r];
                    }
                }
            }
        }
    }
    cout << ans[1][n];
    return 0;
}
