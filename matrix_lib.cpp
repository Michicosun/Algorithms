#include<iostream>
#include<cmath>
#include<map>
#include<stack>
#include<set>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

#define int long long int

typedef vector<vector<int>> matrix;

const int mod = 1e9 + 7;

matrix mult(const matrix& A, const matrix& B) {
    matrix ans(A.size(), vector<int>(B.front().size()));
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.front().size(); ++j) {
            for (int k = 0; k < B.size(); ++k) {
                ans[i][j] = (ans[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
            }
        }
    }
    return ans;
}

matrix getE(int n) {
    matrix ans(n, vector<int>(n));
    for (int i = 0; i < n; ++i) ans[i][i] = 1;
    return ans;
}

matrix fastPow(const matrix& A, int p) {
    if (p == 0) return getE(A.size());
    else if (p % 2 == 0) {
        auto ans = fastPow(A, p / 2);
        return mult(ans, ans);
    } else {
        auto ans = fastPow(A, p - 1);
        return mult(ans, A);
    }
}

