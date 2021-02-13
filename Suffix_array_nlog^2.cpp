#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<random>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>
#include<ctime>
#include<cassert>
#include<sstream>
#include<set>

using namespace std;

#define int long long int

int now;
int n;
vector<int> c;

bool cmp(int a, int b){
    return c[a] < c[b] || (c[a] == c[b] && c[(a + now) % n] < c[(b + now) % n]);
}

bool cmp2(int a, int b){
    return c[a] < c[b];
}

vector<int> getSuffMass(string & s){
    s.push_back('$');
    n = (int)s.size();
    now = 1;
    vector<int> suf(n);
    c.resize(n);
    for(int i = 0; i < n; i++)suf[i] = i;
    for(int i = 0; i < n; i++)c[i] = s[i] - 'a';
    sort(suf.begin(), suf.end(), cmp2);
    for(int t = 1; t < n; t *= 2, now *= 2){
        vector<int> nc(n);
        sort(suf.begin(), suf.end(), cmp);
        nc[suf[0]] = 0;
        for(int i = 1; i < n; i++){
            int l1 = suf[i - 1];
            int r1 = (suf[i - 1] + now) % n;
            int l2 = suf[i];
            int r2 = (suf[i] + now) % n;
            if(c[l1] != c[l2] || c[r1] != c[r2]){
                nc[suf[i]] = nc[suf[i - 1]] + 1;
            }else{
                nc[suf[i]] = nc[suf[i - 1]];
            }
        }
        c = nc;
    }
    suf.erase(suf.begin());
    s.pop_back();
    n = (int)s.size();
    return suf;
}

vector<int> getOSuffMass(vector<int> & suf){
    vector<int> osuf(n);
    for(int i = 0; i < n; i++)osuf[suf[i]] = i;
    return osuf;
}

vector<int> getLcp(string & s, vector<int> & p, vector<int> & pos){
    vector<int> lcp(n);
    int k = 0;
    for(int i = 0; i < n; i++){
        if(pos[i] == n - 1){
            k = 0;
            continue;
        }
        int j = p[pos[i] + 1];
        while(s[i + k] == s[j + k]){
            k++;
        }
        lcp[pos[i]] = k;
        if(k > 0)k--;
    }
    return lcp;
}

void getStr(int st, int k, const string & s){
    for(int i = st; i < st + k; i++)cout << s[i];
}

signed main(){
    int k;
    string s; cin >> s >> k;
    vector<int> sa = getSuffMass(s);
    vector<int> osa = getOSuffMass(sa);
    vector<int> lcp = getLcp(s, sa, osa);
    if(n - sa[0] >= k){
        getStr(sa[0], k, s);
        return 0;
    }
    k -= (n - sa[0]);
    for(int i = 1; i < n; i++){
        int cnt = n - sa[i] - lcp[i - 1];
        if(cnt >= k){
            getStr(sa[i], lcp[i - 1] + k, s);
            return 0;
        }
        k -= cnt;
    }
    getStr(sa[n - 1], n - sa[n - 1], s);
    return 0;
}
