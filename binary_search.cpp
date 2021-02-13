#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int check(const vector<int> & a, int m){
    int ans = 0;
    for (int x : a) ans += x / m;
    return ans;
}

int bin_search(const vector<int> & a, int k){
    int l = 0, r = 1e9;
    while (r - l > 1){
        int m = (r + l) / 2;
        int ans = check(a, m);
        if (ans >= k)l = m;
        else r = m;
    }
    return l;
}

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> silk(n);
    for (int i = 0; i < n; i++)cin >> silk[i];
    cout << bin_search(silk, k);
    return 0;
}
