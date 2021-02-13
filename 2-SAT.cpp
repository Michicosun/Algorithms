#include<iostream>
#include<cmath>
#include<map>
#include<queue>
#include<set>
#include<cassert>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
#include<vector>

using namespace std;

int n, m;
vector<vector<int>> g;
vector<vector<int>> cg;
vector<int> top;
vector<bool> used;
vector<int> color;
vector<bool> ans;

void top_sort(int v){
    used[v] = true;
    for (auto i : g[v]){
        if (!used[i])top_sort(i);
    }
    top.push_back(v);
}

void dfs(int v, int col){
    color[v] = col;
    for (auto i : cg[v]){
        if (color[i] == -1){
            dfs(i, col);
        }
    }
}

void build_graph(){
    g.assign(2 * n, {});
    cg.assign(2 * n, {});
    for (int i = 0; i < m; i++){
        int i1, e1, i2, e2; cin >> i1 >> e1 >> i2 >> e2;
        g[(!e1) * n + i1].push_back(e2 * n + i2);
        g[(!e2) * n + i2].push_back(e1 * n + i1);
    }
    for (int i = 0; i < 2 * n; i++){
        for (auto to : g[i]){
            cg[to].push_back(i);
        }
    }
}

void get_top_sort(){
    top.clear();
    used.assign(2 * n, false);
    for (int i = 0; i < 2 * n; i++){
        if (!used[i])top_sort(i);
    }
    reverse(top.begin(), top.end());
}

void get_SCC(){
    color.assign(2 * n, -1);
    int col = 0;
    for (int i = 0; i < 2 * n; i++){
        if (color[top[i]] == -1){
            dfs(top[i], col);
            col++;
        }
    }
}

void solve(){
    ans.assign(n, 0);
    for (int i = 0; i < n; i++){
        ans[i] = (color[i] < color[i + n]);
    }
}

signed main(){
    freopen("2sat.in", "r", stdin);
    freopen("2sat.out", "w", stdout);
    while (cin >> n >> m){
        build_graph();
        get_top_sort();
        get_SCC();
        solve();
        for (auto i : ans)cout << i;
        cout << endl;
    }
    return 0;
}
