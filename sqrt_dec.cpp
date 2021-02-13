#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

#define int long long int

signed main(){
    const int INF = 1e9;
    int n, k;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)cin >> a[i];
    int len = (int)sqrt(n + 0.0) + 1;
    vector<pair<int, int>> b(len, {-INF, -INF});
    for(int i = 0; i < n; i++){
        if(b[i / len].first < a[i]){
            b[i / len] = {a[i], i};
        }
    }
    cin >> k;
    for(int u = 0; u < k; u++){
        int l, r;
        cin >> l >> r;
        l--; r--;
        int ans = -INF;
        int ans_ind = -1;
        for(int i = l; i <= r;){
            if (i % len == 0 && i + len - 1 <= r) {
                if(b[i / len].first > ans){
                    ans = b[i / len].first;
                    ans_ind = b[i / len].second;
                }
                i += len;
            }
            else {
                if(a[i] > ans){
                    ans = a[i];
                    ans_ind = i;
                }
                ++i;
            }
        }
        cout << ans << " " << ans_ind + 1 << endl;
    }
    return 0;
}
