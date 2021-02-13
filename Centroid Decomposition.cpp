#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <set>
#include <stack>

using namespace std;

int n;
vector<int> sz;
vector<vector<pair<int, int>>> g;
vector<vector<int>> len;
vector<int> depth;
vector<int> pr;
vector<multiset<int>> cAns;
const int INF = 1e9;
const int maxlog = 30;

void dfs(int v, int p = -1){
    sz[v] = 1;
    for (auto t : g[v]){
        int to = t.first;
        if (to != p && depth[to] == -1){
            dfs(to, v);
            sz[v] += sz[to];
        }
    }
}

void getLen(int v, int p, int d, int l){
    len[v][d] = l;
    for (auto t : g[v]){
        int to = t.first;
        int w = t.second;
        if (to != p && depth[to] == -1){
            getLen(to, v, d, l + w);
        }
    }
}

int build(int v, int d){
    dfs(v);
    int s = sz[v];
    int prev = -1;
    while (true){
        int next = -1;
        for (auto t : g[v]){
            int to = t.first;
            if (sz[to] > s / 2 && depth[to] == -1 && prev != to){
                next = to;
            }
        }
        if (next == -1)break;
        prev = v;
        v = next;
    }
    depth[v] = d;
    getLen(v, -1, d, 0);
    for (auto t : g[v]){
        int to = t.first;
        if (depth[to] == -1){
            pr[build(to, d + 1)] = v;
        }
    }
    return v;
}

void init(){
    sz.resize(n);
    g.resize(n);
    pr.resize(n, -1);
    cAns.resize(n, {INF});
    depth.resize(n, -1);
    len.resize(n, vector<int>(maxlog, 1e9));
}

void add(int v){
    int c = v;
    int d = depth[v];
    while (c != -1){
        cAns[c].insert(len[v][d]);
        c = pr[c];
        d--;
    }
}

int get(int v){
    int c = v;
    int ans = 1e9;
    int d = depth[v];
    while (c != -1){
        int minC = (*cAns[c].begin());
        ans = min(ans, minC + len[v][d]);
        c = pr[c];
        d--;
    }
    return ans;
}

void del(int v){
    int c = v;
    int d = depth[v];
    while (c != -1){
        cAns[c].erase(cAns[c].find(len[v][d]));
        c = pr[c];
        d--;
    }
}

signed main(){
    cin >> n;
    init();
    for (int i = 1; i < n; i++){
        int u, v, l; cin >> u >> v >> l; u--; v--;
        g[u].push_back({v, l});
        g[v].push_back({u, l});
    }
    build(0, 0);
    int m; cin >> m;
    add(0);
    for (int i = 0; i < m; i++){
        char c;
        int v; cin >> c >> v; v--;
        if (c == '+')add(v);
        else if (c == '-')del(v);
        else cout << get(v) << endl;
    }
    return 0;
}
