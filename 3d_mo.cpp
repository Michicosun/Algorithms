#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>
#include<cassert>
#include<sstream>
#include<set>

using namespace std;

const int maxSqrt = 790;

int d[maxSqrt];

void change(int ind, int x){
    if(ind == 0 || ind >= maxSqrt)return;
    d[ind] += x;
}

int get(){
    int i = 1;
    for(; i < maxSqrt && d[i] > 0; i++);
    return i;
}

int K;

struct query1{
    int ind, t, l, r;
    query1(int t = 0, int l = 0, int r = 0, int ind = 0){
        this->t = t;
        this->l = l;
        this->r = r;
        this->ind = ind;
    }
};

bool cmp(const query1 & a, const query1 & b){
    return a.t / K < b.t / K || (a.t / K == b.t / K && (a.l / K < b.l / K)) || (a.t / K == b.t / K && a.l / K == b.l / K && a.r < b.r);
}

struct query2{
    int ind, from, to;
    query2(int ind = 0, int from = 0, int to = 0){
        this->ind = ind;
        this->from = from;
        this->to = to;
    }
};

const int maxN = 1e5 + 10;
int n, m, tt, tl, tr, t, l, r;
query2 changes[maxN];
query1 queries[maxN];
int cnt[2 * maxN];
vector<int> coords;
int a[maxN], aa[maxN], ans[maxN];

bool in(int tl, int tr, query2 & q){
    return q.ind >= tl && q.ind <= tr;
}

void addChange(int t){
    if(t != 0){
        auto ch = changes[t];
        a[ch.ind] = ch.to;
        if(in(l, r, ch)){
            change(cnt[ch.from], -1);
            cnt[ch.from]--;
            change(cnt[ch.from], 1);
            change(cnt[ch.to], -1);
            cnt[ch.to]++;
            change(cnt[ch.to], 1);
        }
    }
}

void delChange(int t){
    if(t != 0){
        auto ch = changes[t];
        a[ch.ind] = ch.from;
        if(in(l, r, ch)){
            change(cnt[ch.to], -1);
            cnt[ch.to]--;
            change(cnt[ch.to], 1);
            change(cnt[ch.from], -1);
            cnt[ch.from]++;
            change(cnt[ch.from], 1);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    K = 800;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        coords.push_back(a[i]);
        aa[i] = a[i];
    }
    int timer = 1;
    int indQ = 0;
    for(int i = 0; i < m; i++){
        int act; cin >> act;
        if(act == 1){
            int l, r; cin >> l >> r; l--; r--;
            queries[indQ] = query1(timer - 1, l, r, indQ);
            indQ++;
        }else{
            int ind, x; cin >> ind >> x; ind--;
            changes[timer] = query2(ind, aa[ind], x);
            aa[ind] = x;
            coords.push_back(x);
            timer++;
        }
    }
    sort(queries, queries + indQ, cmp);
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    for(int i = 0; i < n; i++)a[i] = (int)(lower_bound(coords.begin(), coords.end(), a[i]) - coords.begin());
    for(int i = 1; i < timer; i++){
        changes[i].from = (int)(lower_bound(coords.begin(), coords.end(), changes[i].from) - coords.begin());
        changes[i].to = (int)(lower_bound(coords.begin(), coords.end(), changes[i].to) - coords.begin());
    }
    t = 0;
    l = 0;
    r = n - 1;
    for(int i = 0; i < n; i++){
        change(cnt[a[i]], -1);
        cnt[a[i]]++;
        change(cnt[a[i]], 1);
    }
    for(int i = 0; i < indQ; i++){
        auto q = queries[i];
        tt = q.t;
        tl = q.l;
        tr = q.r;
        while(t < tt)addChange(++t);
        while(t > tt)delChange(t--);
        while(r < tr){
            r++;
            change(cnt[a[r]], -1);
            cnt[a[r]]++;
            change(cnt[a[r]], 1);
        }
        while(l > tl){
            l--;
            change(cnt[a[l]], -1);
            cnt[a[l]]++;
            change(cnt[a[l]], 1);
        }
        while(r > tr){
            change(cnt[a[r]], -1);
            cnt[a[r]]--;
            change(cnt[a[r]], 1);
            r--;
        }
        while(l < tl){
            change(cnt[a[l]], -1);
            cnt[a[l]]--;
            change(cnt[a[l]], 1);
            l++;
        }
        ans[q.ind] = get();
    }
    for(int i = 0; i < indQ; i++)cout << ans[i] << "\n";
    return 0;
}
