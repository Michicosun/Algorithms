#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<bitset>
#include<unordered_map>
#include<set>

using namespace std;

int n;

void getSuffArray(string & s, vector<int> & p){
    p.resize(n);
    vector<int> c(n), cnt(256, 0);
    for (int i = 0; i < n; i++)cnt[s[i]]++;
    for (int i = 1; i < 256; i++)cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++)p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int cl = 1;
    for (int i = 1; i < n; i++){
        if (s[p[i]] != s[p[i - 1]])cl++;
        c[p[i]] = cl - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; h++){
        for (int i = 0; i < n; i++){
            pn[i] = (p[i] - (1 << h) + n) % n;
        }
        cnt.assign(cl, 0);
        for (int i = 0; i < n; i++){
            cnt[c[pn[i]]]++;
        }
        for (int i = 1; i < cl; i++){
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--){
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        cl = 1;
        for (int i = 1; i < n; i++){
            int mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
            if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])cl++;
            cn[p[i]] = cl - 1;
        }
        swap(c, cn);
    }
}

void getLcp(string & s, vector<int> & p, vector<int> & lcp){
    lcp.resize(n + 1);
    vector<int> pos(n);
    for (int i = 1; i < n; i++){
        pos[p[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; i++){
        if (pos[i] == n - 1){
            k = 0;
            continue;
        }
        int j = p[pos[i] + 1];
        while (s[i + k] == s[j + k]){
            k++;
        }
        lcp[pos[i]] = k;
        if (k > 0)k--;
    }
}

void solve(string & s, vector<int> & p, int ind, int from, long long int k){
    for (int i = 0; i < from + k; i++){
        cout << s[p[ind] + i];
    }
};

signed main(){
    long long int k;
    string s; cin >> s >> k;
    s.push_back('$');
    n = (int)s.size();
    vector<int> p, lcp;
    getSuffArray(s, p);
    getLcp(s, p, lcp);
    if (n - 1 - p[1] >= k){
        solve(s, p, 1, 0, k);
    }else{
        k -= (n - 1 - p[1]);
        for (int i = 2; i < n; i++){
            int cnt = n - 1 - p[i] - lcp[i - 1];
            if (cnt >= k){
                solve(s, p, i, lcp[i - 1], k);
                k = 0;
                break;
            }
            k -= cnt;
        }
        if (k > 0){
            for (int i = p[n - 1]; i < n - 1; i++)cout << s[i];
        }
    }
    return 0;
}
